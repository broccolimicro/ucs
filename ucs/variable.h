#pragma once

#include <common/standard.h>
#include "type.h"

namespace ucs
{

struct instance
{
	instance();
	instance(string name, vector<int> slice);
	~instance();

	string name;
	vector<int> slice;

	string to_string() const;
};

bool operator<(const instance &i0, const instance &i1);
bool operator>(const instance &i0, const instance &i1);
bool operator<=(const instance &i0, const instance &i1);
bool operator>=(const instance &i0, const instance &i1);
bool operator==(const instance &i0, const instance &i1);
bool operator!=(const instance &i0, const instance &i1);

struct variable
{
	variable();
	variable(string name, int region = 0);
	~variable();

	vector<instance> name;
	int region;

	string to_string() const;
};

bool operator<(const variable &v0, const variable &v1);
bool operator>(const variable &v0, const variable &v1);
bool operator<=(const variable &v0, const variable &v1);
bool operator>=(const variable &v0, const variable &v1);
bool operator==(const variable &v0, const variable &v1);
bool operator!=(const variable &v0, const variable &v1);

struct parameter_instance
{
	int type;
	int id;
	string value;
};

struct module_instance
{
	string name;
	vector<int> types;
	vector<parameter_instance> parameters;
	vector<int> bounds;
};

struct variable_set
{
	variable_set();
	~variable_set();

	vector<variable> nodes;
	vector<module_instance> modules;

	int define(variable v);
	int find(variable v);
	int closest(variable v) const;
	vector<vector<int> > get_groups() const;
};

}

