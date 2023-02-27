#pragma once

#ifndef TRUTH_TABLE.H
#define TRUTH_TABLE.H

#include "utils.h"
#include "truth_table_node.h"

class truth_table 
{
private:
	truth_table_node Node;
	int NumberOfUniqueLiterals;
	std::vector<bool> function;

public:
	truth_table();
	truth_table(std::set<char>* Literals);
};


#endif


