
#include "quineMcCluskey.h"


quineMcCluskey::quineMcCluskey() 
{
	_truthTableMatrix = {};
	_uniqueLiterals = NULL;
	_function = NULL;
	_functionBinary = NULL;
	_simplifiedFunction = NULL;

}

quineMcCluskey::quineMcCluskey(normalizedString* F)
{
	_uniqueLiterals = utils::unique_literals(&((*F)[0]));
	set_function(F); //to set _functionBinary automatically
	build_char_table();
	_simplifiedFunction = NULL;
}

quineMcCluskey::quineMcCluskey(std::set<char>* Uls, std::vector<int>* F)
{
	_uniqueLiterals = Uls;
	_functionBinary = F; //to set _functionBinary automatically
	build_char_table();
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

	for (int i = 0; i <  2 << _uniqueLiterals->size() - 1; i++)
	{
		TempStr = utils::decimal_to_binary(i, _uniqueLiterals->size());

		for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
		{
			int x = (*TempStr)[j] - '0';
			_truthTableMatrix[*it]->push_back(x);
			j++;
		}
		(*_truthTableMatrix['f']).push_back(0);
		j = 0;
	}

	for (int i = 0; i < 2 << _uniqueLiterals->size() - 1; i++)
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
	for (int i = 0; i < _uniqueLiterals->size() * 4 + 4; i++)
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

	for (int i = 0; i < 2 << _uniqueLiterals->size() - 1; i++)
	{
		for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
		{
			std::cout << std::right << std::setw(2) << (*(_truthTableMatrix[*it]))[i] << std::setw(2) << "|";
		}
		std::cout << std::right << std::setw(2) << (*(_truthTableMatrix['f']))[i] << std::setw(2) << "|";
		std::cout << "\n";
	}

	for (int i = 0; i < _uniqueLiterals->size() * 4 + 4; i++)
	{
		std::cout << std::right << "―";
	}

	std::cout << "\n";
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
	coveredBool combinedMinterm;
	combinedMinterm.value = A.value;
	combinedMinterm.coverIndexes = A.coverIndexes;
	combinedMinterm.isCombined = 0;

	for (int i = 0; i < 32; i++) //looping over 32 bit int, i represents number of bits we shift
	{
		if ((A.value >> i & 1) != (B.value >> i & 1))
		{
			combinedMinterm.coverIndexes |= 1 << i; //sets bit at which bit difference is at

			break; //breaks since function is exclusively called for 1 bit difference
		}
	}

	return combinedMinterm;
}

std::vector<std::vector<coveredBool>> quineMcCluskey::group_implicants(std::vector<std::vector<coveredBool>>& mintermGroups)
{
	std::vector<std::vector<coveredBool>> implicants(_uniqueLiterals->size());

	for (int i = 0; i < mintermGroups.size() - 1; i++) //columns
	{
		for (int j = 0; j < mintermGroups[i].size(); j++) //minterms of a group
		{
			for (int k = 0; k < mintermGroups[i + 1].size(); k++) //minterms of the group adjacent to it
			{
				int difference = coveredBool_bit_difference(mintermGroups[i][j], mintermGroups[i + 1][k]);

				if (difference == 1)
				{
					coveredBool combinedMinterm = combine_minterms(mintermGroups[i][j], mintermGroups[i + 1][k]);

					bool isDuplicate = false;

					for (auto it = implicants[i].begin(); it != implicants[i].end(); it++)
					{
						if (it->value == combinedMinterm.value && it->coverIndexes == combinedMinterm.coverIndexes)
						{
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate)
					{
						implicants[i].push_back(combinedMinterm);
					}

					mintermGroups[i][j].isCombined = true;
					mintermGroups[i + 1][k].isCombined = true;

				}
			}
		}
	}

	return implicants;
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

std::string* quineMcCluskey::coveredBool_to_minterm(coveredBool cb)
{
	std::string* s = new std::string;
	int count = 0;

	for (auto it = _uniqueLiterals->rbegin(); it != _uniqueLiterals->rend(); it++)
	{
		if (cb.coverIndexes >> count & 1)
		{
			count++;
			continue;
		}
		else if (cb.value >> count & 1)
		{
			*s = *it + *s;
		}
		else
		{
			*s = std::string(1, *it) + std::string(1, '\'') + *s;
		}

		count++;
	}

	return s;
}

std::vector<std::string> quineMcCluskey::get_pos()
{
	std::vector<std::string> returnVector = {};
	std::string temp;
	int count = 0;
	for (int i = 0; i < 2 << _uniqueLiterals->size() - 1; i++)
	{
		if (!(*_truthTableMatrix['f'])[i])
		{
			for (auto it = _uniqueLiterals->begin(); it != _uniqueLiterals->end(); it++)
			{
				if ((*_truthTableMatrix[*it])[i] == 0)
				{
					temp += std::string(1, *it) + "\'";
				}
				else
				{
					temp += std::string(1, *it);
				}

				if (count < _uniqueLiterals->size() - 1)
				{
					temp += "+";
				}

				count++;
			}
			returnVector.push_back(temp);
			count = 0;
			temp = "";
		}
	}

	return returnVector;

}

void quineMcCluskey::start()
{

	std::vector<std::vector<std::vector<coveredBool>>> columnArray;
	columnArray.push_back(group_minterms_by_bits());

	for (int i = 0; i < _uniqueLiterals->size() - 1; i++)
	{
		columnArray.push_back(group_implicants(columnArray[i]));
	}

	std::cout << "SoP expression: ";

	int count = 0;

	for (auto i : *_function)
	{
		std::cout << i;
		if (count != _function->size() - 1)
		{
			std::cout << " + ";
		}
		count++;
	}

	std::cout << "\nPos expression: ";
	for (auto i : get_pos())
	{
		std::cout << " (" << i;
		if (count != _function->size() - 1)
		{
			std::cout << ") ";
		}
		count++;
	}

	std::cout << "\n\nTruth table: \n";

	print_table();

	std::cout << "Prime Implicants: \n";
	std::vector<coveredBool> primeImplicants; //container to store PIs to set coverChart's PIs

	for (int i = 0; i < _uniqueLiterals->size() - 1; i++) //cols
	{
		for (auto j : columnArray[i]) //groups
		{
			for (auto k : j) //minterms
			{
				if (!k.isCombined)
				{
					primeImplicants.push_back(k);
					std::cout << *coveredBool::coveredBool_to_binary(k, _uniqueLiterals->size()) << "\n";
					std::cout << *coveredBool_to_minterm(k) << "\n\n";
				}
			}
		}
	}

	std::cout << "Cover Chart Reduction: \n\n";
	_coverChart.set_primeImplicants(primeImplicants);
	_coverChart.build_chart(_uniqueLiterals->size());
	_coverChart.reduce_chart(_uniqueLiterals->size());
	
	std::cout << "\nEssentials: \n";
	for (auto i : _coverChart._essentialPrimes)
	{
		std::cout << * coveredBool::coveredBool_to_binary(i, _uniqueLiterals->size()) << "\n";
		std::cout << *coveredBool_to_minterm(i) << "\n\n";

	}

	std::cout << "\nSimplified Expression: ";

	int count2 = 0;
	for (auto it = _coverChart._essentialPrimes.begin(); it !=_coverChart._essentialPrimes.end(); it++)
	{
		count2++;
		std::cout << *coveredBool_to_minterm(*it);
		if (count2 == _coverChart._essentialPrimes.size())
		{
			break;
		}
		else
			std::cout << " + ";
	}

}



