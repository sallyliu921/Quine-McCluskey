#pragma once



#ifndef COVERCHART_H
#define COVERCHART_H

#include <algorithm>
#include "coveredBool.h"

class coverChart
{
private:
	std::vector<coveredBool> _primeImplicants;
	std::map<int, std::vector<int>> _chart; //each minterm inclusions are represented as a binary number (integer element) bit size == # of coveredBools


public:
	std::vector<coveredBool> _essentialPrimes;
	coverChart();
	coverChart(std::vector<coveredBool> coveredBools, std::map<int,int> chart);

	void set_primeImplicants(std::vector<coveredBool> coveredBools);
	void build_chart(int bits); //iterates on pis, bitmasks them and builds the map

	void reduce_from_essential_primes(int bits);
	void reduce_chart(int bits);
	void clear_chart_row(int index, int bits);
	void print_chart(int bits);
};

#endif 