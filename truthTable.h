#pragma once

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include "utils.h"

typedef struct coveredBool
{
	int value;
	int coverIndexes; //each bit acts as a flag for its corresponding dashed (covered) bit in value
};

class truthTable 
{
private:
	charKeyMatrix _truthTableMatrix; //for printing

	std::set<char>* _uniqueLiterals;
	normalizedString* _function;
	int* _functionBinary; //function representation as minterm in binary
	normalizedString* _simplifiedFunction;

public:
	truthTable();
	truthTable(std::set<char>* _uniqueLiterals, normalizedString* function);

	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);

	void build_char_table(); //bin additon to 2^n for printing
	void print_table();

	///Qm methods///

	coveredBool*	group_minterms_by_ones();
	coveredBool		combine_minterms();
	coveredBool*	group_primes();
	int coveredBool_bit_difference(coveredBool A, coveredBool B);

	int bit_difference(int A, int B); 
	void qm(); //big NP boss


};


#endif


