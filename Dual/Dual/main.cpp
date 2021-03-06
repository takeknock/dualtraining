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

    ublas::vector<double> discountFactor(16);
    discountFactor[0] = 0.9999; // O/N
    discountFactor[1] = 0.9988; // T/N
    discountFactor[2] = 0.9912; // 1W 
    discountFactor[3] = 0.9891; // 1M
    discountFactor[4] = 0.98; // 6M 
    discountFactor[5] = 0.96; // 1Y 
    discountFactor[6] = 0.94; // 1Y6M
    discountFactor[7] = 0.93; // 2Y
    discountFactor[8] = 0.92; // 2Y6M
    discountFactor[9] = 0.91; // 3Y 
    discountFactor[10] = 0.90; // 3Y6M
    discountFactor[11] = 0.89; // 4Y
    discountFactor[12] = 0.889; // 5Y6M
    discountFactor[13] = 0.88; // 6Y
    discountFactor[14] = 0.87; // 6Y6M
    discountFactor[15] = 0.86; // 7Y

    ublas::vector<double> forwardLibor(9);
    // Let day count convention be ACT360, 
    // without thinking target date is whether business day or not.
    
    // today to O/N
    forwardLibor[0] = 1.0 / 360.0 * (1.0 / discountFactor[0] - 1.0);
    //// O/N to T/N
    forwardLibor[1] = 1.0 / 360.0 * (discountFactor[0] / discountFactor[1] - 1.0);
    //// T/N to 1W
    forwardLibor[2] = 5.0 / 360.0 * (discountFactor[1] / discountFactor[2] - 1.0);
    //// 1W to 1M
    forwardLibor[3] = 180.0 / 360.0 * (discountFactor[2] / discountFactor[3] - 1.0);
    //// 1M to 6M
    forwardLibor[4] = 180.0 / 360.0 * (discountFactor[3] / discountFactor[4] - 1.0);
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
    const double strike = 1;
    const double volatility6M = 0.2;
	const double forwardLiborValue6M = 180.0 / 360.0
		* (discountFactor[3] / discountFactor[4] - 1.0);
    const cp::Dual<double> forwardLibor6M(forwardLiborValue6M, 1.0);

    const cp::Dual<double> d1 = (log(forwardLibor6M / strike) 
		+ 0.5 * volatility6M * volatility6M * 180.0 / 360.0)
        / (volatility6M * std::sqrt(180.0 / 360.0));

	std::cout << "6M d1_derivative:" << d1._derivative << std::endl;
    const cp::Dual<double> d2 = (log(forwardLibor6M / strike)
            - 0.5 * volatility6M * volatility6M * 180.0 / 360.0) 
                / (volatility6M * std::sqrt(180.0 / 360.0));

	std::cout << "6M d2_derivative:" << d2._derivative << std::endl;

    const cp::Dual<double> capletPrice6M = 180.0 / 360.0 * discountFactor[4] 
		* (forwardLibor6M * cdfOfStandardNormalDistribution(d1) 
			- strike * cdfOfStandardNormalDistribution(d2));

	std::cout << "capletPrice6m:" << capletPrice6M._value << std::endl;
	std::cout << "capletPrice6m derivative:" << capletPrice6M._derivative << std::endl;

	// calculate 1Y caplet
	const double volatility1Y = 0.5;
	const double forwardLiborValue1Y = 180.0 / 360.0
		* (discountFactor[4] / discountFactor[5] - 1.0);
	const cp::Dual<double> forwardLibor1Y(forwardLiborValue1Y, 0.0);

	const cp::Dual<double> d11Y = (log(forwardLibor1Y / strike) 
		+ 0.5 * volatility1Y * volatility1Y * 180.0 / 360.0)
		/ (volatility1Y * std::sqrt(180.0 / 360.0));

	std::cout << "1Y d1_derivative:" << d11Y._derivative << std::endl;
	const cp::Dual<double> d21Y = (log(forwardLibor1Y / strike)
		- 0.5 * volatility1Y * volatility1Y * 180.0 / 360.0)
		/ (volatility1Y * std::sqrt(180.0 / 360.0));

	std::cout << "1Y d2_derivative:" << d21Y._derivative << std::endl;

	const cp::Dual<double> capletPrice1Y = 180.0 / 360.0 * discountFactor[5]
		* (forwardLibor1Y * cdfOfStandardNormalDistribution(d11Y)
			- strike * cdfOfStandardNormalDistribution(d21Y));

	std::cout << "capletPrice1Y:" << capletPrice1Y._value << std::endl;
	std::cout << "capletPrice1Y derivative:" << capletPrice1Y._derivative << std::endl;

	const cp::Dual<double> cap1Y = capletPrice6M + capletPrice1Y;

	std::cout << "cap1Y :" << cap1Y._value << std::endl;
	std::cout << "derivative of cap1Y with forwardLibor6M :" << cap1Y._derivative << std::endl;


	// main flow plan	
	//Underlying underlying(value);
	//Caplet caplet(strike, maturity, underlying);
	//Black black(volatility);
	//const Dual<double> capletPrice = caplet.calculatePrice(model); //model.volatility, underlying.tenor
	//const Dual<double> capPrice = sum(capletPrice);

	//result
	//6M d1_derivative : 1523
	//6M d2_derivative : 1523
	//capletPrice6m : 2.36436e-12
	//capletPrice6m derivative : 1.14953e-08
	//1Y d1_derivative : 0
	//1Y d2_derivative : 0
	//capletPrice1Y : 0.000792079
	//capletPrice1Y derivative : -0.226536
	//cap1Y : 0.000792079
	//derivative of cap1Y with forwardLibor6M : -0.226536

   // ATM Cap Volatilities quoted in market
    ublas::vector<double> capVolatilities(7);
    capVolatilities[0] = 1.86;// 1Y
    capVolatilities[1] = 1.38;// 2Y
    capVolatilities[2] = 1.05;// 3Y
    capVolatilities[3] = 0.84;// 4Y
    capVolatilities[4] = 0.71;// 5Y
    capVolatilities[5] = 0.55;// 7Y
    capVolatilities[6] = 0.43;// 10Y

    boost::math::normal norm(0, 1);
    const double capRate = 0.1;

    //// from cap vol to cap price
    //// 1Y
    //
    //
    //const double libor1Y = 1.0 * (1.0 / discountFactor[5] - 1.0);

    //
    //const double cap1Yd1 = 
    //    (log(libor1Y / capRate) + 0.5 * capVolatilities[0] * capVolatilities[0] * 1.0)
    //    / (capVolatilities[0] * 1.0);
    //const double cap1Yd2 =
    //    (log(libor1Y / capRate) - 0.5 * capVolatilities[0] * capVolatilities[0] * 1.0)
    //    / (capVolatilities[0] * 1.0);

    //const double capPrice1Y = 1.0 * discountFactor[5] * (libor1Y * cdf(norm, cap1Yd1) - capRate * cdf(norm, cap1Yd2));
    //std::cout << "cap volatility 1Y :" << capVolatilities[0] << std::endl;
    //std::cout << "capPrice1Y :" << capPrice1Y << std::endl;

    //// 2Y
    //const double libor2Y = 2.0 * (1.0 / discountFactor[7] - 1.0);

    //const double cap2Yd1 =
    //    (std::log(libor2Y / capRate) + 0.5 * capVolatilities[1] * capVolatilities[1] * 2.0)
    //    / (capVolatilities[1] * std::sqrt(2.0));
    //const double cap2Yd2 =
    //    (std::log(libor2Y / capRate) - 0.5 * capVolatilities[1] * capVolatilities[1] * 2.0)
    //    / (capVolatilities[1] * std::sqrt(2.0));

    //const double capPrice2Y = 2.0 * discountFactor[7] * (libor2Y * cdf(norm, cap2Yd1) - capRate * cdf(norm, cap2Yd2));
    //std::cout << "cap volatility 2Y :" << capVolatilities[1] << std::endl;
    //std::cout << "capPrice2Y :" << capPrice2Y << std::endl;

    //// 3Y
    //const double libor3Y = 3.0 * (1.0 / discountFactor[9] - 1.0);

    //const double cap3Yd1 =
    //    (std::log(libor3Y / capRate) + 0.5 * capVolatilities[2] * capVolatilities[2] * 3.0)
    //    / (capVolatilities[2] * std::sqrt(3.0));
    //const double cap3Yd2 =
    //    (std::log(libor3Y / capRate) - 0.5 * capVolatilities[2] * capVolatilities[2] * 3.0)
    //    / (capVolatilities[2] * std::sqrt(3.0));

    //const double capPrice3Y = 3.0 * discountFactor[9] * (libor3Y * cdf(norm, cap3Yd1) - capRate * cdf(norm, cap3Yd2));
    //std::cout << "cap volatility 3Y :" << capVolatilities[2] << std::endl;
    //std::cout << "capPrice3Y :" << capPrice3Y << std::endl;

    // assume piecewise constant volatility
    ublas::vector<double> capletVolatilities(4);
    capletVolatilities[0] = capVolatilities[0]; // 6M
    capletVolatilities[1] = capVolatilities[0]; // 1Y
    
    // use 2Y cap volatility for 1Y6M cap pricing
    const double libor1Y6M = 1.5 * (1.0 / discountFactor[6] - 1.0);
    const double cap1Y6Md1 = 
        (std::log(libor1Y6M / capRate) + 0.5 * capVolatilities[1] * capVolatilities[1] * 1.5)
        / (capVolatilities[1] * std::sqrt(1.5));

    const double cap1Y6Md2 =
        (std::log(libor1Y6M / capRate) - 0.5 * capVolatilities[1] * capVolatilities[1] * 1.5)
        / (capVolatilities[1] * std::sqrt(1.5));

    const double capPrice1Y6M = 1.5 * discountFactor[6] * (libor1Y6M * cdf(norm, cap1Y6Md1) - capRate * cdf(norm, cap1Y6Md2));
    std::cout << "cap volatility 1Y6M :" << capVolatilities[1] << std::endl;
    std::cout << "capPrice1Y6M :" << capPrice1Y6M << std::endl;

    // black(price) = implied vol
    for (std::size_t i = 0; i < 20; ++i) {
        break;
    }

    //def newtonRap(cp, price, s, k, t, rf) :
    //    v = sqrt(2 * pi / t)*price / s
    //    print "initial volatility: ", v
    //    for i in range(1, 100) :
    //        d1 = (log(s / k) + (rf + 0.5*pow(v, 2))*t) / (v*sqrt(t))
    //        d2 = d1 - v*sqrt(t)
    //        vega = s*norm.pdf(d1)*sqrt(t)
    //        price0 = cp*s*norm.cdf(cp*d1) - cp*k*exp(-rf*t)*norm.cdf(cp*d2)
    //        v = v - (price0 - price) / vega
    //        print "price, vega, volatility\n", (price0, vega, v)
    //        if abs(price0 - price) < 1e-25 :
    //break
    //    return v


    double ddd;
    std::cin >> ddd;

    return 0;
}
