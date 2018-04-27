#include "dense.h"

DenseLayer::DenseLayer(int input_nodes, int output_nodes, NeuralNetworkConfig config){
	this->input_nodes = input_nodes;
	this->output_nodes = output_nodes;
	this->config = config;
	w = MatrixXd::Random(input_nodes ,output_nodes);
	this->b = MatrixXd::Random(input_nodes ,output_nodes);
}