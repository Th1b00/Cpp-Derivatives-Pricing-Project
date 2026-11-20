#include "MT.h"

MT::MT() : _generator(std::random_device{}()) {}

MT& MT::instance() {
    static MT unique;
    return unique;
}

double MT::rand_unif() {
    static std::uniform_real_distribution<double> unif(0.0, 1.0);
    return unif(instance()._generator);
}

double MT::rand_norm() {
    static std::normal_distribution<double> norm(0.0, 1.0);
    return norm(instance()._generator);
}
