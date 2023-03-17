﻿
#include "quineMcCluskey.h"

quineMcCluskey::quineMcCluskey() 
{
	_truthTableMatrix = {};
	_uniqueLiterals = NULL;
	_function = NULL;
	_functionBinary = NULL;
	_simplifiedFunction = NULL;

}

quineMcCluskey::quineMcCluskey(std::set<char>* Uls, normalizedString* F)
{
	_truthTableMatrix = {};
	_uniqueLiterals = Uls;
	set_function(F); //to set _functionBinary automatically
	_simplifiedFunction = NULL;
}

void quineMcCluskey::set_uliterals(std::set<char>* Uls)
{
	_uniqueLiterals = Uls;
}

void quineMcCluskey::set_function(normalizedString* F)
{
	_function = F;
	_functionBinary = new std::vector<int>;

	for (auto it = _function->begin(); it != _function->end(); it++)
	{
		_functionBinary->push_back(utils::minterm_to_binary(*it));

	}
}
void quineMcCluskey::set_function(std::vector<int> minterms)
{
	_functionBinary = new std::vector<int>;
	for (auto it = minterms.begin(); it != minterms.end(); it++)
	{
		_functionBinary->push_back(*it);
	}
}

void quineMcCluskey::build_char_table()
{
	int j = 0;

	for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++) //iterating on literals into map
	{
		_truthTableMatrix[*it] = new std::vector<int>({});
		_truthTableMatrix['f'] = new std::vector<int>({});
	}

	std::string* TempStr = new std::string;

	for (int i = 0; i < std::pow(2, _uniqueLiterals->size()); i++)
	{
		TempStr = utils::decimal_to_binary(i, _uniqueLiterals->size());

		for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
		{
			int x = (*TempStr)[j] - '0';
			_truthTableMatrix[*it]->push_back(x);
			j++;
			std::cout << *it;
		}
		(*_truthTableMatrix['f']).push_back(0);
		j = 0;
	}

	for (int i = 0; i < std::pow(2, _uniqueLiterals->size()); i++)
	{
		for (auto r : (*_functionBinary))
		{
			std::bitset<32> bits(r);
			int _index = bits.to_ulong();
			_truthTableMatrix['f']->at(_index) = 1;
		}
	}

}

void quineMcCluskey::print_table()
{
	for (int i = 0; i < _uniqueLiterals->size() * 4; i++)
	{
		std::cout << std::right << "―";
	}

	std::cout << "\n";

	for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
	{
		std::cout << std::right << std::setw(2) << *it << std::setw(2) << "|";
	}
	std::cout << std::right << std::setw(2) << 'f' << std::setw(2) << "|";
	std::cout << "\n";

	for (int i = 0; i < _uniqueLiterals->size()*4+4; i++)
	{
		std::cout << std::right << "―";
	}
	
	std::cout << "\n";

	for (int i = 0; i < std::pow(2, _uniqueLiterals->size()); i++)
	{
		for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
		{
			std::cout << std::right << std::setw(2) << (*(_truthTableMatrix[*it]))[i] << std::setw(2) << "|";
		}
		std::cout << std::right << std::setw(2) << (*(_truthTableMatrix['f']))[i] << std::setw(2) << "|";
		std::cout << "\n";
	}
}

int quineMcCluskey::bit_difference(int A, int B)
{
	int count = 0;
	for (int i = 0; i < 32; i++) //since int is a 32-bit number we are shifting 32 bits to compare them
	{
		if ((A & 1) != (B & 1)) //checking if LSB is different
		{
			count++;
		}

		A = A >> 1; //shifting 1 bit to LSB
		B = B >> 1;
	}

	return count;
}

std::vector<std::vector<coveredBool>> quineMcCluskey::group_minterms_by_bits()
{
	int Temp = -1;
	std::vector<std::vector<coveredBool>> ReturnMatrix(_uniqueLiterals->size()+1);

	for (auto it = _functionBinary->begin(); it != _functionBinary->end(); it++)
	{
		Temp = utils::count_bits(*it);
		ReturnMatrix[Temp].push_back({*it, 0, 0});
	}

	return ReturnMatrix;
}

coveredBool	quineMcCluskey::combine_minterms(coveredBool A, coveredBool B)
{
	coveredBool combinedMinterm = A;

	for (int i = 0; i < 32; i++) //looping over 32 bit int, i represents number of bits we shift
	{
		if ((A.value >> i & 1) != (B.value >> i & 1))
		{
			combinedMinterm.coverIndexes >>= i; //shifts different bit to LSB postion
			combinedMinterm.coverIndexes |= 1; //sets the bit
			combinedMinterm.coverIndexes <<= i; //shifts it back to its original position

			break; //breaks since function is exclusively called for 1 bit difference
		}
	}

	return combinedMinterm;
}

std::vector<std::vector<coveredBool>> quineMcCluskey::group_primes(std::vector<std::vector<coveredBool>> mintermGroups)
{
	std::vector<std::vector<coveredBool>> primeImplicants(_uniqueLiterals->size());


	for (int i = 0; i < mintermGroups.size() - 1; i++)
	{
		for (int j = 0; j < mintermGroups[i].size(); j++)
		{
			for (int k = 0; k < mintermGroups[i + 1].size(); k++)
			{
				int difference = coveredBool_bit_difference(mintermGroups[i][j], mintermGroups[i + 1][k]);

				if (difference == 1)
				{
					coveredBool combinedMinterm = combine_minterms(mintermGroups[i][j], mintermGroups[i + 1][k]);

					bool isDuplicate = false;

					for (auto it = primeImplicants[i].begin(); it != primeImplicants[i].end(); it++)
					{
						if (it->value == combinedMinterm.value && it->coverIndexes == combinedMinterm.coverIndexes)
						{
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate)
					{
						primeImplicants[i].push_back(combinedMinterm);
					}

					mintermGroups[i][j].isCovered = true;
					mintermGroups[i + 1][k].isCovered = true;
				}
			}
		}
	}

	return primeImplicants;
}

int quineMcCluskey::coveredBool_bit_difference(coveredBool A, coveredBool B)
{
	if (A.coverIndexes == 0) {
		return bit_difference(A.value, B.value);
	}else if (A.coverIndexes == B.coverIndexes)
	{
		A.value |= 1 << A.coverIndexes;
		B.value |= 1 << B.coverIndexes; //sets bits in value according to the index so they are equalized on dashes
		
		return bit_difference(A.value, B.value); //dash equalized values are then compared normally to check for difference between other bits
	}

	return -1;
}

void quineMcCluskey::start()
{
	coveredBool x = combine_minterms({0b000011,0b010000}, {0b000111, 0b010000});
	
}

