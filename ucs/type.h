/*
 * type.h
 *
 *  Created on: Jun 26, 2015
 *      Author: nbingham
 */

#include <common/standard.h>

#ifndef ucs_type_h
#define ucs_type_h

namespace ucs
{
struct parameter
{
	string type;
	string name;
};

struct declaration
{
	string name;
	vector<int> types;
	vector<string> bounds;
};

struct module
{
	string name;
	vector<int> types;
	vector<parameter> parameters;
	vector<declaration> members;
};

struct type_set
{
	vector<module> modules;
};

}

#endif
