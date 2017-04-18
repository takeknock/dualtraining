#include <iostream>

#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\vector.hpp>
#include <boost\numeric\ublas\io.hpp>

#include "..\auto_differentiation\Variable.h"
#include "..\auto_differentiation\Constant.h"
#include "..\auto_differentiation\binary_expression.h"
#include "..\auto_differentiation\operators.h"
#include "..\auto_differentiation\evals.h"

int main()
{
    ad::Variable v = ad::Variable(1.0);
    ad::Variable v2 = ad::Variable(2.0);
    ad::Constant c1 = ad::Constant(1.0);
    //ad::binary_expression res = v + c1;

    ad::binary_expression<ad::add_op, ad::Variable, double> res = v + 2.0;
    ad::binary_expression<ad::sub_op, ad::Variable, ad::Variable> res2 = v - v2;
    auto y = res + res2;
    std::cout << typeid(res).name() << std::endl;
    std::cout << typeid(res2).name() << std::endl;
    std::cout << typeid(y).name() << std::endl;
    namespace ublas = boost::numeric::ublas;

    std::cout << ad::eval(y) << std::endl;



    //int n = 5;
    //int j = 1;
    //ublas::vector<double> in(n);
    ////ublas::matrix<double> in(n, n);

    //// initialize
    //for (int i = 0; i < n; ++i)
    //    in(i) = 0;

    //in(j) = 1;

    //ublas::matrix<double> calculationGraph(n, n);

    

    int a;
    std::cin >> a;
}