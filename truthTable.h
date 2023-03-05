#pragma once

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include "utils.h"

class truthTable 
{
private:
	charKeyMatrix _truthTableMatrix;
	std::set<char>* _uniqueLiterals;
	normalizedString* _function;
	normalizedString* _simplifiedFunction;

public:
	truthTable();
	truthTable(std::set<char>* _uniqueLiterals, normalizedString* function);

	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);

	void build_char_table(); //bin additon to 2^n
	void print_table();

	///Qm methods///


	int bit_difference(int A, int B);
	void qm(); //big NP boss
};


#endif


