
#include "extendedbinomialtree.hpp"
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/experimental/lattices/extendedbinomialtree.hpp>
#include <iostream>

using namespace QuantLib;

int main() {

    try {

        // add your code here

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

