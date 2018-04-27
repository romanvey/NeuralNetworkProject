#include "test.h"

using Eigen::MatrixXd;

int main() {
	// * ActivationLayer Tests
    NeuralNetwork nn;
    ActivationLayer a;

    MatrixXd m(2,2);
    m << 1, 0, 5, 6;

    MatrixXd test_m(2,2);
    test_m = a._sigmoid(m);
    std::cout << test_m << std::endl;

	// * DenseLayer Tests
	NeuralNetworkConfig conf;
	DenseLayer dl(4, 5, conf);
	std::cout<<dl.w<<std::endl;
	std::cout<<dl.config.lr<<std::endl;
}