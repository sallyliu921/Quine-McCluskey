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
	charKeyMatrix truthTableMatrix;
	std::set<char>* UniqueLiterals;
	normalizedString* Function;

public:
	truthTable();
	truthTable(std::set<char>* UniqueLiterals, normalizedString* function);

	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);

	void build_table(); //bin additon to 2^n
	void qm(); //big NP boss
};


#endif


