#pragma once

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include "utils.h"



//struct keyIterator : public
//{
//
//};


class truthTable 
{
private:
	charKeyMatrix _truthTableMatrix;
	std::set<char>* _uniqueLiterals;
	normalizedString* _function;

public:
	truthTable();
	truthTable(std::set<char>* _uniqueLiterals, normalizedString* function);

	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);

	void build_table(); //bin additon to 2^n
	void print_table();
	void qm(); //big NP boss
};


#endif


