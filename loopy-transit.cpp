#include <iostream>
using std::endl;
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::binary_search;
using std::sort;
using std::any_of;
#include "pretty-print.h"

typedef vector<int> vec;
typedef vector<vec> vecvec;

template<typename T>
bool in(vector<T> path, const T id) {
	sort(path.begin(), path.end());
	return binary_search(path.begin(), path.end(), id);
}

void explore(const int starting_id, const int id, const vecvec &adjs, vecvec &paths, vec path={}, const int level=0) {
	path.push_back(id);

	// cout << string(2*level, ' ');
	// cout << "{explore: " << id << ", path: " << path << "}" << endl;

	for (const int &adj : adjs.at(id)) {
		if (!in(path, adj)) {
			explore(starting_id, adj, adjs, paths, path, level + 1);
		}
		else if (starting_id == adj) {
			paths.push_back(path);
		}
	}
}

bool checkPaths(const vec &path, const vec &to_check) {
	vecvec sequences_to_check;

	size_t size = to_check.size();
	sequences_to_check.resize(size);

	for (unsigned int i = 0; i < size; i++) {
		sequences_to_check.at(i).push_back(to_check.at(i));

		unsigned int j = (i + 1 < size) ? i + 1 : 0;
		while (j != i) {
			sequences_to_check.at(i).push_back(to_check.at(j));
			j = (j + 1 < size) ? j + 1 : 0;
		}
	}

	return any_of(sequences_to_check.begin(), sequences_to_check.end(), [path](vec seq) {
		return seq == path;
	});
}

int main() {
	vecvec adjList;

	size_t stationCount, connectionCount;
	cin >> stationCount >> connectionCount;
	adjList.resize(stationCount);

	int s, t;
	for (size_t i = 0; i < connectionCount; i++) {
		cin >> s >> t;
		adjList.at(s).push_back(t);
	}

	vecvec paths;
	for (int i = 0; i < (int)adjList.size(); i++) {
		const int starting_id = i;
		explore(starting_id, i, adjList, paths);
	}

	vecvec to_check;
	for (const vec &path : paths) {
		bool found = any_of(to_check.begin(), to_check.end(), [path](vec seq) {
			return checkPaths(path, seq);
		});

		if (!found) {
			to_check.push_back(path);
		}
	}

	cout << "Loops: " << to_check << endl;
	cout << "Count: " << to_check.size() << endl;
}
