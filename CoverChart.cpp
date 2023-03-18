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
	for (int i = 0; i < bits; i++)
	{
		for (auto pi : _primeImplicants)
		{
			if ((pi.value & (~pi.coverIndexes)) == (i & (~pi.coverIndexes))) //bitmasks undashed bits and sees if they are contianed in a minterm
			{
				_chart[i] |= 1 << primeImplicantIndex; //sets bit corresponding to the bool value of the coveredBool in chart 
			}
			primeImplicantIndex++;
		}

		primeImplicantIndex = 0;
	}
}

std::vector<int> coverChart::get_essential_primes()
{
	return {};
}

void coverChart::reduce_chart()
{

}

void coverChart::print_chart(int bits)
{
	std::cout << std::right << std::setw(bits * 1.5 + 1) << " | ";

	for (int i = 0; i < bits; i++)
	{
		std::cout << i << "  ";
	}

	std::cout << "\n";

	for (int i = 0; i < bits*4 + 1; i++)
	{
		std::cout << "_";
	}

	std::cout << "\n";
	
	for (int i = 0; i < bits; i++)
	{
		std::cout << *coveredBool::coveredBool_to_binary(_primeImplicants[i], bits) << std::setw(bits * 1.5 - bits) << " | ";
		for (auto j : _chart)
		{
			if (j.second & 1 >> i)
			{
				std::cout << "X";
			}

		}
		std::cout << "\n";

	}


}