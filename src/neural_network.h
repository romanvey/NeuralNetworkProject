#ifndef NN_NN_H
#define NN_NN_H

#include "layer.h"
#include <map>
#include <iostream>
#include <vector>
#include "neural_network_config.h"

using Eigen::MatrixXd;
class NeuralNetwork {
private:
	std::vector<Layer*> layers;
	NeuralNetworkConfig config;
public:
	NeuralNetwork(NeuralNetworkConfig config);
	NeuralNetwork();
	void add(Layer* layer);
	void fit(MatrixXd X, MatrixXd y);
	MatrixXd predict(MatrixXd X);
	std::vector<std::string> predict_labled(MatrixXd X, std::map<int, std::string> m);
	double accuracy_classification(MatrixXd X, MatrixXd y);
	double accuracy_regression(MatrixXd X, MatrixXd y);
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