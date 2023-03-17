
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{
    std::set<char>* Uls = new std::set<char>({ 'a', 'b','c', 'd'});
    normalizedString* f = new normalizedString({});

    quineMcCluskey T1(Uls, f);

    printf("Bits: %i", utils::count_bits(-5));
    std::cout << std::endl;

    std::string* s = new std::string;
    *s = "ABCD+A'BCD+A'B'CD+A'B'C'D";
    normalizedString* a = utils::parse_string(s);
    T1.set_function(a);
    // Define the truth table
       // Define the variables needed to represent the function
    std::vector<std::string> function = { "a'bc", "ab'c", "abc'", "abc" };
    std::set<char> uniqueLiterals = { 'a', 'b', 'c', 'd'};

    // Create a Quine-McCluskey object and set its variables
    quineMcCluskey qm;
    qm.set_function({0,2,5,6,7,8,10,12,13,14,15});
    qm.set_uliterals(&uniqueLiterals);
    std::cout << "1";
    qm.build_char_table();
    std::cout << "2";
    qm.print_table();
        for (int i = 0; i < (qm.group_minterms_by_bits()).size(); i++)
    {
        std::cout << "Prime implicants with " << i << " bits: ";
        for (int j = 0; j < qm.group_minterms_by_bits()[i].size(); j++)
        {
            std::cout << qm.group_minterms_by_bits()[i][j].value << " "<< qm.group_minterms_by_bits()[i][j].coverIndexes<<" ,";
        }
        std::cout << std::endl;
    }
    // Compute the prime implicants and print them
    std::vector<std::vector<coveredBool>> primeImplicants = qm.group_primes(qm.group_minterms_by_bits());
    for (int i = 0; i < primeImplicants.size(); i++)
    {
        std::cout << "Prime implicants with " << i << " bits: ";
        for (auto it = primeImplicants[i].begin(); it != primeImplicants[i].end(); it++)
        {
            std::cout << *coveredBool::coveredBool_to_binary(*it, 4) << "  ";
        }
        std::cout << std::endl;
    }


    qm.start();

    return 0;
}