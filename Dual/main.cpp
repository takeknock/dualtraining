#include <iostream>
#include <cmath>

#include <boost/math/distributions/normal.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/math/constants/constants.hpp>

//#include <cppunit/brieftestprogresslistener.h>
//#include <cppunit/compileroutputter.h>
//#include <cppunit/extensions/testfactoryregistry.h>
//#include <cppunit/testresult.h>
//#include <cppunit/testresultcollector.h>
//#include <cppunit/testrunner.h>

#include "Dual.h"
//#include "dual_expression.h"


int main()
{
//    CPPUNIT_NS::TestResult controller;
//    CPPUNIT_NS::TestResultCollector result;
//    controller.addListener(&result);
//    CPPUNIT_NS::BriefTestProgressListener progress;
//    controller.addListener(&progress);
//    CPPUNIT_NS::TestRunner runner;
//    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
//    runner.run(controller);
//    CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
//    outputter.write();
//
    namespace ublas = boost::numeric::ublas;
    //const double strike = 1.0;
    //const double maturity = 10.0;
    //const double volatility = 0.2;
    //const double forwardRate = 0.1;
    //// check equation
    //const double dayCountFraction = 20 / 360;

    ublas::vector<double> discountFactor(9);
    discountFactor[0] = 0.9999; // O/N
    discountFactor[1] = 0.9988; // T/N
    discountFactor[2] = 0.9912; // 1W 
    discountFactor[3] = 0.9891; // 1M
    discountFactor[4] = 0.98; // 6M 
    discountFactor[5] = 0.96; // 1Y 
    discountFactor[6] = 0.94; // 1Y6M
    discountFactor[7] = 0.93; // 2Y
    discountFactor[8] = 0.92; // 2Y6M


    // ublas::vector<cp::Dual<double> > forwardLibor(9);
    // Let day count convention be ACT360, 
    // without thinking target date is whether business day or not.
    
    // today to O/N
    //forwardLibor[0] = 
    //    cp::Dual<double>(1.0 / 360.0 * (1.0 / discountFactor[0] - 1.0));
    //// O/N to T/N
    //forwardLibor[1] =
    //    cp::Dual<double>(1.0 / 360.0 * (discountFactor[0] / discountFactor[1] - 1.0));
    //// T/N to 1W
    //forwardLibor[2] =
    //    cp::Dual<double>(5.0 / 360.0 * (discountFactor[1] / discountFactor[2] - 1.0));
    //// 1W to 1M
    //forwardLibor[3] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[2] / discountFactor[3] - 1.0));
    //// 1M to 6M
    //forwardLibor[4] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[3] / discountFactor[4] - 1.0));
    //// 6M to 1Y 
    //forwardLibor[5] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[4] / discountFactor[5] - 1.0)); 
    //// 1Y to 1Y6M
    //forwardLibor[6] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[5] / discountFactor[6] - 1.0)); 
    //// 1Y6M to 2Y
    //forwardLibor[7] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[6] / discountFactor[7] - 1.0)); 
    //// 2Y to 2Y6M
    //forwardLibor[8] =
    //    cp::Dual<double>(180.0 / 360.0 * (discountFactor[7] / discountFactor[8] - 1.0)); 


    // example: calculate 6M caplet
    boost::math::normal norm(0,1);

    const double strike = 0.01;
    const double volatility = 0.2;
	const double value = 180.0 / 360.0
		* (discountFactor[3] / discountFactor[4] - 1.0);
    const cp::Dual<double> forwardLibor(value);

	const cp::Dual<double> fs = forwardLibor / strike;
	const cp::Dual<double> assetOrNothing = log(fs);
	const double cashOrNothing = 0.5 * volatility * volatility * 30.0 / 360.0;
    const cp::Dual<double> d1 = (assetOrNothing + cashOrNothing) 
                / (volatility * std::sqrt(30.0 / 360.0));

	std::cout << "d1_derivative:" << d1._derivative << std::endl;
    const cp::Dual<double> d2 = (log(forwardLibor / strike)
            - 0.5 * volatility * volatility * 30.0 / 360.0) 
                / (volatility * std::sqrt(30.0 / 360.0));

	std::cout << "d2_derivative:" << d2._derivative << std::endl;

    const cp::Dual<double> capletPrice6m = 180.0 / 360.0 * discountFactor[4] 
		* (forwardLibor * cdfOfNormalDistribution(d1) 
			- strike * cdfOfNormalDistribution(d2));

	std::cout << "capletPrice6m:" << capletPrice6m._value << std::endl;
    //cp::black<double, double, double, double, double> f;
    //double price = f(strike, maturity, volatility, forwardRate, dayCountFraction);
    //std::cout << price << std::endl;

    // TODO: be able to input other type as template arguments 

    // for Dual test
    const double a = 2.0;
    const cp::Dual<double> b(10.0);
    
    cp::Dual<double> p = a + b;
    cp::Dual<double> mi = a - b;
    cp::Dual<double> mu = a * b;
    cp::Dual<double> div = a / b;

	double z;
    std::cout << p._derivative << std::endl;
    std::cout << mi._derivative << std::endl;
    std::cout << mu._derivative << std::endl;
    std::cout << div._derivative << std::endl;
	std::cin >> z;
    return 0;
}
