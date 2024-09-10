/*
 * variable.cpp
 *
 *  Created on: Feb 5, 2015
 *      Author: nbingham
 */

#include "variable.h"
#include <common/text.h>

namespace ucs
{
instance::instance()
{

}

instance::instance(string name, vector<int> slice)
{
	this->name = name;
	this->slice = slice;
}

instance::~instance()
{

}

string instance::to_string() const
{
	string result = name;
	for (int i = 0; i < (int)slice.size(); i++)
		result += "[" + ::to_string(slice[i]) + "]";
	return result;
}

bool operator<(const instance &i0, const instance &i1)
{
	return (i0.name < i1.name) ||
		   (i0.name == i1.name && i0.slice < i1.slice);
}

bool operator>(const instance &i0, const instance &i1)
{
	return (i0.name > i1.name) ||
		   (i0.name == i1.name && i0.slice > i1.slice);
}

bool operator<=(const instance &i0, const instance &i1)
{
	return (i0.name < i1.name) ||
		   (i0.name == i1.name && i0.slice <= i1.slice);
}

bool operator>=(const instance &i0, const instance &i1)
{
	return (i0.name > i1.name) ||
		   (i0.name == i1.name && i0.slice >= i1.slice);
}

bool operator==(const instance &i0, const instance &i1)
{
	return i0.name == i1.name && i0.slice == i1.slice;
}

bool operator!=(const instance &i0, const instance &i1)
{
	return i0.name != i1.name || i0.slice != i1.slice;
}

variable::variable()
{
	region = 0;
}

variable::variable(string name, int region) {
	this->name.push_back(instance(name, vector<int>()));
	this->region = region;
}

variable::~variable()
{

}

bool variable::isnode() const {
	if (name.size() != 1 or name[0].name.size() <= 1 or name[0].name[0] != '_') {
		return false;
	}
	for (auto c = name[0].name.begin()+1; c != name[0].name.end(); c++) {
		if (*c < '0' or *c > '9') {
			return false;
		}
	}
	return true;
}

string variable::to_string() const
{
	string result = "";
	for (int i = 0; i < (int)name.size(); i++)
	{
		if (i != 0)
			result += ".";

		result += name[i].to_string();
	}

	if (region != 0)
		result += "'" + ::to_string(region);

	return result;
}

bool operator<(const variable &v0, const variable &v1)
{
	return (v0.name < v1.name) ||
		   (v0.name == v1.name && v0.region < v1.region);
}

bool operator>(const variable &v0, const variable &v1)
{
	return (v0.name > v1.name) ||
		   (v0.name == v1.name && v0.region > v1.region);
}

bool operator<=(const variable &v0, const variable &v1)
{
	return (v0.name < v1.name) ||
		   (v0.name == v1.name && v0.region <= v1.region);
}

bool operator>=(const variable &v0, const variable &v1)
{
	return (v0.name > v1.name) ||
		   (v0.name == v1.name && v0.region >= v1.region);
}

bool operator==(const variable &v0, const variable &v1)
{
	return (v0.name == v1.name && v0.region == v1.region);
}

bool operator!=(const variable &v0, const variable &v1)
{
	return (v0.name != v1.name || v0.region != v1.region);
}

variable_set::variable_set()
{

}

variable_set::~variable_set()
{

}

int variable_set::define(variable v)
{
	for (int i = 0; i < (int)nodes.size(); i++)
		if (nodes[i] == v)
			return -1;

	nodes.push_back(v);
	return (int)nodes.size()-1;
}

int variable_set::find(variable v)
{
	bool exists = false;
	for (int i = 0; i < (int)nodes.size(); i++)
		if (nodes[i].name == v.name)
		{
			exists = true;
			if (nodes[i].region == v.region)
				return i;
		}

	if (exists)
		return define(v);

	return -1;
}

int variable_set::closest(variable v) const
{
	int index = 0;
	int min = edit_distance(v.to_string(), nodes[0].to_string());

	for (int i = 1; i < (int)nodes.size(); i++)
	{
		int dist = edit_distance(v.to_string(), nodes[i].to_string());
		if (dist < min)
		{
			min = dist;
			index = i;
		}
	}

	return index;
}

vector<vector<int> > variable_set::get_groups() const
{
	vector<vector<int> > groups;

	for (int i = 0; i < (int)nodes.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < (int)groups.size() && !found; j++)
		{
			if (nodes[groups[j][0]].name == nodes[i].name)
			{
				groups[j].push_back(i);
				found = true;
			}
		}

		if (!found)
			groups.push_back(vector<int>(1, i));
	}

	return groups;
}

}
