#pragma once

#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include "utils.h"


class truth_table 
{
private:
	
	charKeyMatrix truthTableMatrix;
	int UniqueLiterals;
	std::vector<std::string>* Function;

public:
	truth_table();
	truth_table(int NUL, normalizedString* function);

	void set_number_of_uliterals(int UL);
	void set_function(normalizedString* f);

	
	void build_table();
	void qm();
};


#endif


