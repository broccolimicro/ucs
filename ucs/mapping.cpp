#include "mapping.h"

#include <stdio.h>

using namespace std;

namespace ucs {

mapping::mapping() {
	isIdentity = true;
}

mapping::mapping(int num) {
	identity(num);
	isIdentity = false;
}

mapping::mapping(vector<int> nets) {
	this->nets = nets;
	isIdentity = false;
}

mapping::~mapping() {
}

int mapping::unmap(int net) const {
	if (isIdentity) {
		return net;
	}

	for (int i = 0; i < (int)nets.size(); i++) {
		if (nets[i] == net) {
			return i;
		}
	}
	return -1;
}

int mapping::map(int net) const {
	if (isIdentity) {
		return net;
	}

	if (net >= 0 and net < (int)nets.size()) {
		return nets[net];
	}
	return -1;
}

void mapping::identity(int num) {
	nets.clear();

	nets.reserve(num);
	for (int i = 0; i < num; i++) {
		nets.push_back(i);
	}
}

void mapping::apply(const mapping &m) {
	// this: current -> main
	// m: other -> current
	// want: other -> main

	vector<int> updated;
	updated.reserve(m.nets.size());
	for (int i = 0; i < (int)m.nets.size(); i++) {
		updated.push_back(map(m.map(i)));
	}
	nets = updated;
	isIdentity = isIdentity and m.isIdentity;
}

void mapping::set(int from, int to) {
	if (from >= nets.size()) {
		nets.resize(from+1, -1);
	}
	nets[from] = to;
	isIdentity = false;
}

void mapping::set(vector<int> from, int to) {
	int m = (int)nets.size()-1;
	for (int i = 0; i < (int)from.size(); i++) {
		if (from[i] > m) {
			m = from[i];
		}
	}
	nets.resize(m+1,-1);
	for (int i = 0; i < (int)from.size(); i++) {
		nets[from[i]] = to;
	}
	isIdentity = false;
}

bool mapping::has(int from) const {
	return from >= 0 and from < (int)nets.size() and nets[from] >= 0;
}

void mapping::print() const {
	printf("map{%s", isIdentity ? "identity" : "");
	for (int i = 0; i < (int)nets.size(); i++) {
		if (i != 0) {
			printf(", ");
		}
		printf("%d -> %d", i, nets[i]);
	}
	printf("}\n");
}

}
