#include "dense.h"

DenseLayer::DenseLayer(int input_nodes, int output_nodes){
	this->input_nodes = input_nodes;
	this->output_nodes = output_nodes;
	w = MatrixXd::Random(input_nodes ,output_nodes);
	b = MatrixXd::Random(1 ,output_nodes);
}

MatrixXd DenseLayer::forward(MatrixXd X, NeuralNetworkConfig config){
	// ! Parallelized
	this->config = config;
	value = X;
	MatrixXd result = X*w + b;
	return result;
}


MatrixXd DenseLayer::backward(MatrixXd chain_error){
	// ! Parallelized
	MatrixXd result = chain_error*w.transpose();
	
	MatrixXd changed_w = w + ((value.transpose() * chain_error) * config.lr);
	MatrixXd changed_b = b + (chain_error.colwise().sum() * config.lr);
	
	w = config.inertia * changed_w + (1 - config.inertia) * w;
	b = config.inertia * changed_b + (1 - config.inertia) * b;
	return result;
}