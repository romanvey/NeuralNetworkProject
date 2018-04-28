#ifndef NN_NN_H
#define NN_NN_H

#include "layer.h"
#include <iostream>
#include <vector>
#include "neural_network_config.h"

using Eigen::MatrixXd;
class NeuralNetwork {
public:
	NeuralNetwork(NeuralNetworkConfig config);
	NeuralNetwork();
	void add(Layer* layer);
	void fit(MatrixXd X, MatrixXd y);
	MatrixXd predict(MatrixXd X);

	std::vector<Layer*> layers;
	NeuralNetworkConfig config;
};

#endif //NN_NN_H


// class A2DD
// {
//   int gx;
//   int gy;

// public:
//   A2DD(int x,int y);
//   int getSum();

// };