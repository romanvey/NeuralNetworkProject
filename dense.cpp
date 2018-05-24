#include "dense.h"

DenseLayer::DenseLayer(int input_nodes, int output_nodes){
	this->input_nodes = input_nodes;
	this->output_nodes = output_nodes;
	w = MatrixXd::Random(input_nodes ,output_nodes);
//	w = MatrixXd::Ones(input_nodes ,output_nodes);
	b = MatrixXd::Random(1 ,output_nodes);
//	b = MatrixXd::Zero(1 ,output_nodes);

}

MatrixXd DenseLayer::forward(MatrixXd X, NeuralNetworkConfig config){
	// * Parallelized
	if(config.verbose){
//		std::cout<<"Dense forward started"<<std::endl;
	}
	this->config = config;
	value = X;
	MatrixXd result = X*w;

	for(int i = 0; i < result.rows(); i++){
		result.row(i) += b;
	}

//    std::cout << "X*w is: \n" << std::endl;
//    std::cout << result << std::endl;

	if(config.verbose){
//		std::cout<<"Dense forward ended"<<std::endl;
	}

//    std::cout << "value is: \n" << std::endl;
//	std::cout << value << std::endl;
	return result;
}


MatrixXd DenseLayer::backward(MatrixXd chain_error){


	// * Parallelized
	if(config.verbose){
//		std::cout<<"Dense backward started"<<std::endl;
	}
	MatrixXd result = chain_error*w.transpose();
	
//	std::cout<<value.transpose() * chain_error<<std::endl; // ! remove it

	MatrixXd changed_w = w + ((value.transpose() * chain_error) * config.lr);
	MatrixXd changed_b = b + (chain_error.colwise().sum() * config.lr);
	
	w = config.inertia * changed_w + (1 - config.inertia) * w;
	b = config.inertia * changed_b + (1 - config.inertia) * b;
	if(config.verbose){
//		std::cout<<"Dense backward ended"<<std::endl;
	}

//    std::cout << "cost is : \n";
//    std::cout << chain_error << std::endl;
//    std::cout << "bias is : \n";
//    std::cout << b << std::endl;
//    std::cout << "weights are: \n";
//    std::cout << w << std::endl;

	return result;
}