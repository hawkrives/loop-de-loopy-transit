CXX := g++
CXXFLAGS := -Wall -g -std=c++11

all: sample1 sample2 sample3

sample1: loopy-transit.out
	./$< < $@.txt

sample2: loopy-transit.out
	./$< < $@.txt

sample3: loopy-transit.out
	./$< < $@.txt

loopy-transit.out: loopy-transit.cpp pretty-print.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.{o,out}

.PHONY: clean all sample1 sample2 sample3
