

#include "truthTable.h"

truthTable::truthTable() 
{
	truthTableMatrix = {};
	UniqueLiterals = NULL;
	Function = NULL;

}

truthTable::truthTable(std::set<char>* Uls, normalizedString* F)
{
	UniqueLiterals = Uls;
	Function = F;
}

void truthTable::set_uliterals(std::set<char>* Uls)
{
	UniqueLiterals = Uls;
}

void truthTable::set_function(normalizedString* F)
{
	Function = F;
}

void truthTable::build_table()
{

	for (auto it = UniqueLiterals->begin(); it != UniqueLiterals->end(); it++) //iterating on literals into map
	{
		truthTableMatrix[*it];
	}

	for (int i = 0; i < std::pow(2, UniqueLiterals->size()); i++)
	{
		//change decimal to bin and insert into map
	}

}

void truthTable::qm()
{

}

