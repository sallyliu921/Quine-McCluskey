#pragma once

#ifndef QUINEMCCLUSKEY_H
#define QUINEMCCLUSKEY_H

#include "utils.h"

/// <summary>
/// coveredBool type
/// To resolve issue of representing dashes this type groups two integer values
/// The first is the actual value of the integer representing the minterm
/// The second is an integer that its bits act like a flag, the corresponding bit in the value 
/// in the same position is considered a dashed (covered literal)
/// 
/// This is done for efficiency over character arrays for representation
/// </summary>
typedef struct coveredBool
{
	int value;
	int coverIndexes; //each bit acts as a flag for its corresponding dashed (covered) bit in value
	bool isCovered; //flag to check if coveredBool is combined (might remove for redundancy as any uncombined implicants will be pushed into a container)
};

class quineMcCluskey 
{
private:
	charKeyMatrix _truthTableMatrix; //for printing
	

	std::set<char>* _uniqueLiterals;

	normalizedString* _function;
	std::vector<int>* _functionBinary; //function representation as minterm in binary
	normalizedString* _simplifiedFunction;

public:
	quineMcCluskey();
	quineMcCluskey(std::set<char>* _uniqueLiterals, normalizedString* function);
	
	///setters///
	
	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);

	/// <summary>
	/// builds truthtable, used after expression is given from user 
	/// </summary>
	void build_char_table(); 
	/// <summary>
	/// prints truth table
	/// </summary>
	void print_table();

	///Qm methods///

	/// <summary>
	/// groups minterms by their number of bits is only called once to initiate start();
	/// </summary>
	/// <returns>vector of coveredBool type</returns>
	std::vector<std::vector<coveredBool>>	group_minterms_by_bits();

	/// <summary>
	/// groups prime implicants, is iterated upon by start();
	/// </summary>
	/// <returns>vector of coveredBool type</returns>
	std::vector<std::vector<coveredBool>>	group_primes();

	/// <summary>
	/// combines minterms together, is used in group_primes();
	/// </summary>
	/// <param name="A">minterm A</param>
	/// <param name="B">minterm B</param>
	/// <returns>resultant coveredBool</returns>
	coveredBool	combine_minterms(coveredBool A, coveredBool B);

	/// <summary>
	/// gets the difference bit difference between two coveredBools
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns>difference</returns>
	int coveredBool_bit_difference(coveredBool A, coveredBool B);

	/// <summary>
	/// returns bit difference between two numbers
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns></returns>
	int bit_difference(int A, int B); 
	void start(); //big NP boss


};


#endif


