#include <iostream>
#include <map>
#include "matheval.hpp"

void first()
{
    std::cout << matheval::parse<double>("1+1",{}) << '\n';
}

void second()
{
    std::map<std::string,double> symtab;
    symtab.emplace(std::make_pair("x",  2));
    symtab.emplace(std::make_pair("y", -1));
    std::cout << matheval::parse<double>("cbrt(x/2 + sqrt(x**2/4 + y**3/24))",symtab) << '\n';
}

int main()
{
    first();
    second();
}
