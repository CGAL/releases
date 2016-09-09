#include "tutorial.h"
#include <vector>
#include <iostream>

using std::vector;

int main()
{
    vector<float> fvec;
    fvec.push_back(3.14159265358979323846);
    fvec.push_back(2.7182818284590452354);
    vector<int> ivec(fvec.size());
    std::vector<int>::size_type i;
    for (i=0; i<ivec.size(); i++)
        ivec[i] = (int) fvec[i];
    std::cout << ivec[0] <<' '<< ivec[1] <<'\n';
    return 0;
}
