
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
	_function = F;
	_functionBinary = {};
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
	//_functionBinary->resize(_uniqueLiterals->size());

	for (auto it = _function->begin(); it != _function->end(); it++)
	{
		_functionBinary->push_back(utils::minterm_to_binary(*it));

	}
	
}

void quineMcCluskey::build_char_table()
{
	int j = 0;

	for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++) //iterating on literals into map
	{
		_truthTableMatrix[*it] = new std::vector<int>({});
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
		}
		
		j = 0;
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

	std::cout << "\n";

	for (int i = 0; i < _uniqueLiterals->size()*4; i++)
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
	std::vector<std::vector<coveredBool>> ReturnMatrix(_uniqueLiterals->size());

	for (auto it = _functionBinary->begin(); it != _functionBinary->end(); it++)
	{
		Temp = utils::count_bits(*it);
		ReturnMatrix[Temp - 1].push_back({*it, 0, 0});
	}

	return ReturnMatrix;
}

coveredBool	quineMcCluskey::combine_minterms()
{
	return {0,0};
}

std::vector<std::vector<coveredBool>> quineMcCluskey::group_primes()
{
	return {};
}

int quineMcCluskey::coveredBool_bit_difference(coveredBool A, coveredBool B)
{
	if (A.coverIndexes == B.coverIndexes)
	{
		A.value |= 1 << A.coverIndexes;
		B.value |= 1 << B.coverIndexes; //sets bits in value according to the index so they are equalized on dashes
		
		return bit_difference(A.value, B.value); //dash equalized values are then compared normally to check for difference between other bits
	}

	return 0;
}

void quineMcCluskey::qm()
{
	std::vector<std::vector<coveredBool>> a = group_minterms_by_bits();
}

