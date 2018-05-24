#ifndef NN_DENSE_H
#define NN_DENSE_H

#include<random>
#include <Eigen/Dense>
#include "layer.h"
#include "neural_network_config.h"
#include <cmath>

using Eigen::MatrixXd;

class DenseLayer: public Layer {
public:
	NeuralNetworkConfig config;
	int input_nodes, output_nodes;
	MatrixXd w, b, value;
	DenseLayer(int input_nodes, int output_nodes);
    MatrixXd forward(MatrixXd X, NeuralNetworkConfig config) override;
    MatrixXd backward(MatrixXd chain_error) override;
};


#endif //NN_DENSE_H