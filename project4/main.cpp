
#include "binomialengine.hpp"
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/time/calendars/nullcalendar.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <iomanip>
#include <iostream>
#include <ctime>

using namespace QuantLib;

int main() {

    // market data
    Real S = 100.0;
    Rate r = 0.03;
    Rate q = 0.0;
    Volatility sigma = 0.20;

    Date today = Settings::instance().evaluationDate();
    std::cout<<today<<std::endl;
    // option data
    //Date exerciseDate = today + 12*Month;
    Date exerciseDate(2, Mar, 2021);
    std::cout<<exerciseDate<<std::endl;
    Real k = 110.0;
    Option::Type type = Option::Put;

    Handle<Quote> U(ext::make_shared<SimpleQuote>(S));
    Handle<YieldTermStructure> R(ext::make_shared<FlatForward>(today, r, Actual365Fixed()));
    Handle<YieldTermStructure> Q(ext::make_shared<FlatForward>(today, q, Actual365Fixed()));
    Handle<BlackVolTermStructure> Sigma(ext::make_shared<BlackConstantVol>(today, NullCalendar(), sigma, Actual365Fixed()));

    ext::shared_ptr<GeneralizedBlackScholesProcess> process =
        ext::make_shared<GeneralizedBlackScholesProcess>(U, Q, R, Sigma);

    ext::shared_ptr<Exercise> exercise = ext::make_shared<AmericanExercise>(today, exerciseDate);
    ext::shared_ptr<PlainVanillaPayoff> payoff = ext::make_shared<PlainVanillaPayoff>(type, k);

    VanillaOption option(payoff, exercise);

    std::cout << "CoxRossRubinstein" << std::endl;

    std::cout << "with oscillation" << std::endl;
    std::cout << std::setprecision(10);
    bool no_osc_flag= false;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }
    std::cout << "without oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= true;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }

    std::cout << "JarrowRudd" << std::endl;

    std::cout << "with oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= false;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<JarrowRudd> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }
    std::cout << "without oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= true;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<JarrowRudd> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }

        std::cout << "Tian" << std::endl;

    std::cout << "with oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= false;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<Tian> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }
    std::cout << "without oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= true;
    for (Size timeSteps = 360; timeSteps < 370; ++timeSteps) {
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<Tian> >(process, timeSteps,no_osc_flag));

        std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    }
            std::cout << "Number of timeSetps to reach 0.0001 of precision:" << std::endl;
            std::cout << "CoxRossRubinstein" << std::endl;

    std::cout << "with oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= false;
    Size timeSteps=10;
    Real price1=0;
    Real price2=1;
    while ((price2-price1)*(price2-price1)>0.000000001 && timeSteps<1000) {
        timeSteps=timeSteps+1;
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));
        price1=price2;
        price2=option.NPV();
    }
    std::cout << timeSteps << std::endl;

    std::cout << "without oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= true;
    timeSteps=10;
    price1=0;
    price2=1;
    while ((price2-price1)*(price2-price1)>0.000000001 && timeSteps<1000) {
        timeSteps=timeSteps+1;
        option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));
        price1=price2;
        price2=option.NPV();
    }
    std::cout << timeSteps << std::endl;


    std::cout << "Running Time Evaluation" << std::endl;
    clock_t t1;
    clock_t t2;
    std::cout << "CoxRossRubinstein" << std::endl;
    timeSteps=10000;
    std::cout << "with oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= false;
    //start timer
    t1=clock();
    option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));
    //end timer
    t2=clock();
    std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    std::cout << (float)(t2-t1)/CLOCKS_PER_SEC << " seconds to process" << std::endl;

    std::cout << "without oscillation" << std::endl;
    std::cout << std::setprecision(10);
    no_osc_flag= true;
    //start timer
    t1=clock();
    option.setPricingEngine(ext::make_shared<BinomialVanillaEngine_2<CoxRossRubinstein> >(process, timeSteps,no_osc_flag));
    //end timer
    t2=clock();
    std::cout << timeSteps << "\t" << option.NPV() << std::endl;
    std::cout << (float)(t2-t1)/CLOCKS_PER_SEC << " seconds to process" << std::endl;

}

