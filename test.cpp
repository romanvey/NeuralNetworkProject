#include "test.h"

using Eigen::MatrixXd;

int main() {
    NeuralNetwork nn;
    Activation a;

    MatrixXd m(2,2);
    m << 1, 0,
            5, 6;

    MatrixXd test_m(2,2);
    test_m = a._sigmoid(m);
    std::cout << test_m;


}