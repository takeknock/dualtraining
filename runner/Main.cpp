#include <iostream>
#include "..\auto_differentiation\Variable.h"

int main()
{
    std::cout << "Hello world!!" << std::endl;
    ad::Variable v = ad::Variable(1.0);
    ad::Variable v2 = ad::Variable(2.0);
    
    std::cout << typeid(v).name() << std::endl;
    int a;
    std::cin >> a;
}