#include "test.h"

using Eigen::MatrixXd;

int main()
{

	// * ActivationLayer Tests
//	std::cout << "ActivationLayer Test started" << std::endl;
	ActivationLayer a("sigmoid");

	MatrixXd m(2, 2);
	m << 1, 0, 5, 6;

//    std::cout << "!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//	std::cout << m.cwiseProduct(m) << std::endl;

	MatrixXd test_m(2, 2);
	test_m = a._derivative_sigmoid(m);
//	std::cout << "m: \n" << test_m << std::endl;
//	std::cout << test_m << std::endl;
//	std::cout << "ActivationLayer Test ended" << std::endl;


	// * DenseLayer Tests
//	std::cout << "DenseLayer Test started" << std::endl;
	DenseLayer dl(4, 5);
//	std::cout << dl.w << std::endl;
//	std::cout << dl.config.lr << std::endl;

	MatrixXd s(2, 4);
	s << 0.1, 0.2, 2.1, -0.5,
		0.1, 0.2, 2.1, -0.5;
//	std::cout << s.colwise().sum() << std::endl;
//	std::cout << "DenseLayer Test ended" << std::endl;


	// Dot product Tests
//	std::cout << "Dot product Test started" << std::endl;
	MatrixXd mat(2, 2);
	mat << 1, 2, 2, 4;
//	std::cout << mat << std::endl;
//	std::cout << (mat * mat) << std::endl;
//	std::cout << "Dot product Test ended" << std::endl;

	// Vector adding Tests
//	std::cout << "Vector adding Test started" << std::endl;
	MatrixXd t1(2, 4);
	t1 << 1, 2, 3, 4, 5, 6, 7, 8;
	
	MatrixXd t2(1, 4);
	t2 << 0, 1, 1, 0;


	for(int i = 0; i < t1.rows(); i++){
		t1.row(i) += t2;
	}
//	std::cout << t1 << std::endl;
//	std::cout << "Vector adding Test ended" << std::endl;


	// NeuralNetwork Tests
	NeuralNetworkConfig conf;

	conf.epochs = 20000;
	conf.lr = 0.4;
	NeuralNetwork nn(conf);
	nn.add(new DenseLayer(2, 6));
	nn.add(new ActivationLayer("sigmoid"));
	nn.add(new DenseLayer(6, 1));
	nn.add(new ActivationLayer("sigmoid"));


	MatrixXd X(4, 2);
	X << 1, 1, 1, 0, 0, 1, 0, 0;
	
	MatrixXd y(4, 1);
	y << 0, 1, 1, 0;


	std::cout<<"fit"<<std::endl;
	nn.fit(X, y);
	std::cout<<"predict"<<std::endl;
	MatrixXd predictions = nn.predict(X);
	std::cout<<"result"<<std::endl;
	std::cout<<predictions<<std::endl;

}