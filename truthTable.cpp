

#include "truthTable.h"

truthTable::truthTable() 
{
	_truthTableMatrix = {};
	_uniqueLiterals = NULL;
	_function = NULL;

}

truthTable::truthTable(std::set<char>* Uls, normalizedString* F)
{
	_truthTableMatrix = {};
	_uniqueLiterals = Uls;
	_function = F;
}

void truthTable::set_uliterals(std::set<char>* Uls)
{
	_uniqueLiterals = Uls;
}

void truthTable::set_function(normalizedString* F)
{
	_function = F;
}

void truthTable::build_table()
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

void truthTable::print_table()
{
	for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
	{
		std::cout << std::right << std::setw(2) << *it << std::setw(2) << "┃";
	}
	
	std::cout << "\n";

	for (int i = 0; i < std::pow(2, _uniqueLiterals->size()); i++)
	{
		for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
		{
			std::cout << std::right << std::setw(2) << (*(_truthTableMatrix[*it]))[i] << std::setw(2) << "┃";
		}																								
		std::cout << "\n";
	}
}

void truthTable::qm()
{

}

