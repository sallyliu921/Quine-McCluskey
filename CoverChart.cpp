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

std::vector<coveredBool> coverChart::get_essential_primes() //redesign
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

bool coverChart::reduce_chart(int bits) //redesign
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

bool coverChart::remove_chart_redundancy(int bits) //redesign
{
	bool temp = false;

	for (auto i : _chart) //iterations to check if there is a dominating column to remove
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

	return _chart == _chart;
}

bool coverChart::three_step_heuristic(int bits)
{
	bool temp = 0;

begin:

	if (reduce_chart(bits))
	{

		if (remove_chart_redundancy(bits))
		{
			print_chart(bits);
			return temp; //returns 0 if its not simplified (no change to chart)
		}
		temp = 1;

		goto begin; //if redundancy is resolved repeat the 3 step heuristic again
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