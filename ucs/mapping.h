#pragma once

#include <vector>

using namespace std;

namespace ucs {

struct mapping {
	mapping();
	mapping(int num);
	mapping(vector<int> nets);
	~mapping();

	// list of nets from old subckt to include in new subckt
	vector<int> nets;
	bool isIdentity;

	int unmap(int net) const;	
	int map(int net) const;
	void identity(int num);
	void apply(const mapping &m);

	void set(int from, int to);
	void set(vector<int> from, int to);
	bool has(int from) const;

	void print() const;
};

}
