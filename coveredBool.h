#pragma once

#ifndef COVEREDBOOL_H
#define COVEREDBOOL_H

#include "utils.h"

/// <summary>
/// coveredBool type
/// To resolve issue of representing dashes this type groups two integer values
/// The first is the actual value of the integer representing the minterm
/// The second is an integer that its bits act like a flag, the corresponding bit in the value 
/// in the same position is considered a dashed (covered literal)
/// 
/// This is done for efficiency over character arrays for representation
/// </summary>
typedef struct coveredBool
{
	int value;
	int coverIndexes; //each bit acts as a flag for its corresponding dashed (covered) bit in value
	bool isCovered; //flag to check if coveredBool is combined (might remove for redundancy as any uncombined implicants will be pushed into a container)


	static std::string* coveredBool_to_binary(coveredBool a, int bits)
	{
		std::string* s = new std::string;

		for (int i = 0; i < bits; i++)
		{
			if (a.coverIndexes & 1 << i)
			{
				*s = '_' + *s;
			}
			else 
			{
				if (a.value & 1 << i)
				{
					*s = '1' + *s;

				}
				else
				{
					*s = '0' + *s;
				}

			}

		}

		return s;
	};


};

#endif 