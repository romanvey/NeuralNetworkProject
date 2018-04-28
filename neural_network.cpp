#include "neural_network.h"

NeuralNetwork::NeuralNetwork(NeuralNetworkConfig config)
{
	this->config = config;
}

NeuralNetwork::NeuralNetwork()
{
	NeuralNetworkConfig config;
	this->config = config;
}

void NeuralNetwork::add(Layer *layer)
{
	layers.push_back(layer);
};

void NeuralNetwork::fit(MatrixXd X, MatrixXd y)
{
	for (int epoch = 0; epoch < config.epochs; epoch++)
	{
		// * Forward propagation
		if(config.verbose){
			std::cout<<"Epoch " << epoch << std:: endl; 
			std::cout << "Forward propagation started" << std::endl;
		}
		MatrixXd curr = X;
		for (int i = 0; i < layers.size(); i++)
		{
			curr = layers[i]->forward(curr, config);
		}

		// * Cost function
		MatrixXd chain_error = y - curr;	

		// * Back propagation
		if(config.verbose){
			std::cout << "Forward propagation ended" << std::endl;
			std::cout << "Backward propagation started" << std::endl;
		}
		for (int i = layers.size() - 1; i >= 0; i--)
		{
			chain_error = layers[i]->backward(chain_error);
		}
		if(config.verbose){
			std::cout << "Backward propagation ended" << std::endl;
		}
	}
}

MatrixXd NeuralNetwork::predict(MatrixXd X)
{
	MatrixXd curr = X;
	for (int i = 0; i < layers.size(); i++)
	{
		curr = layers[i]->forward(curr, config);
	}
	return curr;
}