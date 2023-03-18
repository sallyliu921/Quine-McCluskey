#pragma once

#ifndef QUINEMCCLUSKEY_H
#define QUINEMCCLUSKEY_H

#include "utils.h"
#include "coveredBool.h"


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
	quineMcCluskey(normalizedString* function);
	quineMcCluskey(std::set<char>* _uniqueLiterals, std::vector<int>* function); //for quick debugging/testing
	
	///setters///
	
	void set_uliterals(std::set<char>* Uls);
	void set_function(normalizedString* f);
	void set_function(std::vector<int> minterms);
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
	std::vector<std::vector<coveredBool>> group_minterms_by_bits();

	/// <summary>
	/// groups prime implicants, is iterated upon by start();
	/// </summary>
	/// <returns>vector of coveredBool type</returns>
	std::vector<std::vector<coveredBool>> group_primes(std::vector<std::vector<coveredBool>>& mintermGroups);

	/// <summary>
	/// combines minterms together, is used in group_primes();
	/// </summary>
	/// <param name="A">minterm A</param>
	/// <param name="B">minterm B</param>
	/// <returns>resultant coveredBool</returns>
	coveredBool	combine_minterms(coveredBool A, coveredBool B);

	///QM utilities///

	std::vector<std::string> get_pos();

	/// <summary>
	/// for printing, converts binary terms to their minterm equivalent
	/// </summary>
	/// <param name="Minterm"></param>
	/// <returns></returns>
	std::string* coveredBool_to_minterm(coveredBool cb);

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


