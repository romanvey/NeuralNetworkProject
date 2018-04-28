#include "test.h"

using Eigen::MatrixXd;

int main()
{
	// * ActivationLayer Tests
	ActivationLayer a("sigmoid");

	MatrixXd m(2, 2);
	m << 1, 0, 5, 6;

	MatrixXd test_m(2, 2);
	test_m = a._activ_function(m);
	std::cout << test_m << std::endl;

	// * DenseLayer Tests
	DenseLayer dl(4, 5);
	std::cout << dl.w << std::endl;
	std::cout << dl.config.lr << std::endl;

	MatrixXd s(2, 4);
	s << 0.1, 0.2, 2.1, -0.5,
		0.1, 0.2, 2.1, -0.5;
	std::cout << s.colwise().sum() << std::endl;

	// Dot product Tests
	MatrixXd mat(2, 2);
	mat << 1, 2, 2, 4;
	std::cout << mat << std::endl;
	std::cout << (mat * mat) << std::endl;

	// NeuralNetwork Tests
	NeuralNetworkConfig conf;
	NeuralNetwork nn(conf);
	nn.add(new DenseLayer(2, 6));
	nn.add(new ActivationLayer("sigmoid"));
	nn.add(new DenseLayer(6, 1));
	nn.add(new ActivationLayer("sigmoid"));	

	MatrixXd X(4, 2);
	X << 1, 1, 1, 0, 0, 1, 0, 0;
	std::cout<<X<<std::endl;

}