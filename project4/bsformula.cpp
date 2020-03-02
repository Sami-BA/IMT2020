
#include "bsformula.hpp"
#include <ql/math/distributions/normaldistribution.hpp>
#include <cmath>

using std::sqrt;
using std::exp;
using std::log;
namespace {
    QuantLib::CumulativeNormalDistribution N;
    QuantLib::NormalDistribution n;
}

double bsformula(double S, double K, double T,
                    double r, double sigma, bool call, double q) {
    double d1 = (1/(sigma*sqrt(T))) * (log(S/K) + (r-q+sigma*sigma/2)*T);
    double d2 = d1 - sigma*sqrt(T);

    double result;
    if (call) {
        result = N(d1)*S*exp(-q*T) - N(d2)*K*exp(-r*T);
    } else {
        result = N(-d2)*K*exp(-r*T) -N(-d1)*S*exp(-q*T);
    }
    return result;
}

