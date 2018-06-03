#ifndef NN_NN_H
#define NN_NN_H

#include "layer.h"
#include "dense.h"
#include "activation.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "neural_network_config.h"

using Eigen::MatrixXd;
class NeuralNetwork {
private:
	std::vector<Layer*> layers;
public:
	NeuralNetworkConfig config;
	NeuralNetwork(NeuralNetworkConfig config);
	NeuralNetwork();
	void add(Layer* layer);
	void fit(MatrixXd X, MatrixXd y);
	MatrixXd predict(MatrixXd X);
	std::vector<std::string> predict_labled(MatrixXd X, std::map<int, std::string> m);
	double accuracy_classification(MatrixXd X, MatrixXd y);
	double accuracy_regression(MatrixXd X, MatrixXd y);
	void save_model(std::string name);
	void load_model(std::string name);
};

#endif //NN_NN_H