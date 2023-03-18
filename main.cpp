
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{

    std::vector<std::string> s = {"A'BCD", "A'BC'D'", "A'B'CD","ABCD","AB'CD","ABC'D'","ABC'D", "AB'C'D"};
    quineMcCluskey qm(&s);

    qm.start();

    return 0;
}