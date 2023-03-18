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
	for (int i = 0; i < 2 << bits - 1; i++) //loops on undashed terms
	{
		_chart[i].resize(2 << bits - 1);
		for (auto pi : _primeImplicants) //loops on primeimplicants (rows)
		{
			if ((pi.value & (~pi.coverIndexes)) == (i & (~pi.coverIndexes))) //bitmasks undashed bits and sees if they are contianed in an implicant
			{
				(_chart[i])[primeImplicantIndex] = 1; //sets bit corresponding to the bool value of the coveredBool in chart 
			}
			primeImplicantIndex++;
		}

		primeImplicantIndex = 0;
	}
}

void coverChart::reduce_from_essential_primes(int bits)
{
	for (int i = 0; i < _chart.size(); i++)
	{
		int temp = std::count(_chart[i].begin(), _chart[i].end(), 1);
		if (temp == 1) 
		{
			//_essentialPrimes.insert(_primeImplicants[std::find(_chart[i].begin(), _chart[i].end(), 1) - _chart[i].begin()]);
			_chart[i][std::find(_chart[i].begin(), _chart[i].end(), 1) - _chart[i].begin()] = 0;
		}
	}
}

void coverChart::reduce_chart(int bits)
{
begin:

	int rowBitCount = 0;
	int maxRowBitCount = 0;
	int maxIndex = 0;
	int tempIndex = 0;
	auto temp = _chart;
	bool isUnique = false;

	for(int i = 0; i < _primeImplicants.size(); i++)
	{
		for (auto j : _chart) //iterates on cols
		{
			for (int k = 0; k < _chart.size(); k++)
			{
				if (std::count(_chart[k].begin(), _chart[k].end(), 1) == 1)
				{
					print_chart(bits);
					goto mid;
				}
			}
			if (j.second[i])
			{
				rowBitCount++;
			}
		}

		if (rowBitCount > maxRowBitCount)
		{
			maxRowBitCount = rowBitCount;
			maxIndex = i;
		}

		rowBitCount = 0;

	}
	_essentialPrimes.insert(_primeImplicants[maxIndex]);
	isUnique = _essentialPrimes.find(_primeImplicants[maxIndex]) != _essentialPrimes.end();


	clear_chart_row(maxIndex, bits); //clears rows
	print_chart(bits);

	if (isUnique)
	{
		print_chart(bits);
		isUnique = false;
	}


mid:
	reduce_from_essential_primes(bits);


	if (temp != _chart)
	{
		goto begin;
	}

}

void coverChart::clear_chart_row(int index, int bits)
{
	for (int i = 0; i <_chart.size(); i++)
	{
		_chart[i][index] = 0;
	}

}

void coverChart::print_chart(int bits)
{


	std::cout << std::right << std::setw(bits * 1.5 + 2) << " | ";

	for (auto i : _chart)
	{
		std::cout << i.first << "  ";
	}

	std::cout << "\n";

	for (int i = 0; i < _chart.size()*4 + 1; i++)
	{
		std::cout << "_";
	}

	std::cout << "\n";
	
	for (int i = 0; i < _primeImplicants.size(); i++)
	{
		std::cout << *coveredBool::coveredBool_to_binary(_primeImplicants[i], bits) << std::setw(bits * 1.5 - bits) << " | ";
		for (auto j : _chart)
		{
			if (j.second[i] == 1)
			{
				std::cout << "X" << std::setw(bits * 1.5 + std::to_string(j.first).length() - bits);
			}
			else
			{
				std::cout << " " << std::setw(bits * 1.5 + std::to_string(j.first).length() - bits);
			}
		}
		std::cout << "\n";
	}


}