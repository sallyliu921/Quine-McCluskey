#include "coverChart.h"

coverChart::coverChart()
{

}

coverChart::coverChart(std::vector<coveredBool> coveredBools, std::map<int, int> chart)
{
	
}

void coverChart::set_primeImplicants(std::vector<coveredBool> coveredBools)
{
	_primeImplicants = coveredBools;
}

void coverChart::build_chart(int bits)
{
	int primeImplicantIndex = 0;
	for (int i = 0; i < 2 << bits; i++) //loops on undashed terms
	{
		for (auto pi : _primeImplicants) //loops on primeimplicants (rows)
		{
			if ((pi.value & (~pi.coverIndexes)) == (i & (~pi.coverIndexes))) //bitmasks undashed bits and sees if they are contianed in an implicant
			{
				_chart[i] |= 1 << primeImplicantIndex; //sets bit corresponding to the bool value of the coveredBool in chart 
			}
			primeImplicantIndex++;
		}

		primeImplicantIndex = 0;
	}
}

std::vector<coveredBool> coverChart::get_essential_primes()
{
	std::vector<coveredBool> temp;
	int count = 0;
	for (auto i : _chart)
	{
		if (utils::count_bits(i.second) == 1) 
		{
			temp.push_back(_primeImplicants[count]);
		}
		count++;
	}

	return temp;
}

bool coverChart::reduce_chart(int bits)
{
	auto temp = _chart;
	int count = 0;
	for (auto i : _chart)
	{
		if (i.second == 1)
		{
			for (auto j : _chart)
			{
				j.second &= 0; //clears bits in the rows and columns covered by EPI
			}
		}
		count++;
	}

	return _chart == temp;
}

void coverChart::remove_chart_redundancy(int bits)
{
	bool temp = false;

	for (auto i : _chart)
	{
		for (auto j : _chart)
		{
			temp = i.second & j.second; 
		}
		
		if (!temp)
		{
			i.second &= 0; //clears column
		}

		temp = false;
	}

	int row = 0;
	int comparisonRow = 0;

	for (int i = 0; i < bits-1; i++)
	{
		for (int j = 0; j < _chart.size(); j++)
		{
			row |= (_chart[i] & j) << j;
			comparisonRow |= (_chart[i%j] & j) << j;

			if (row & comparisonRow)
			{
				for (int k = 0; k < bits; k++)
				{
					_chart[k] &= 0 << k; //clears bits in row
				}
			}

		}
	}
}

void coverChart::print_chart(int bits)
{
	std::vector<int> IncludedMinterms;
	for(auto i : _chart)
	{
		if (i.second > 1)
		{
			IncludedMinterms.push_back(i.first);
		}
	}

	std::cout << std::right << std::setw(bits * 1.5 + 1) << " | ";

	for (auto i : IncludedMinterms)
	{
		std::cout << i << "  ";
	}

	std::cout << "\n";

	for (int i = 0; i < IncludedMinterms.size()*4 + 1; i++)
	{
		std::cout << "_";
	}

	std::cout << "\n";
	
	for (int i = 0; i < _primeImplicants.size(); i++)
	{
		std::cout << *coveredBool::coveredBool_to_binary(_primeImplicants[i], bits) << std::setw(bits * 1.5 - bits) << " | ";
		for (auto j : IncludedMinterms)
		{
			if (_chart[j] >> i & 1)
			{
				std::cout << "X" << std::setw(bits * 1.5 + std::to_string(j).length() - bits);
			}
			else
			{
				std::cout << " " << std::setw(bits * 1.5 + std::to_string(j).length() - bits);
			}
		}
		std::cout << "\n";
	}


}