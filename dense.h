#ifndef NN_DENSE_H
#define NN_DENSE_H

#include<random>
#include <Eigen/Dense>
#include "neural_network_config.h"

using Eigen::MatrixXd;

class DenseLayer {
public:
	NeuralNetworkConfig config;
	int input_nodes, output_nodes;
	MatrixXd w, b;
	DenseLayer(int input_nodes, int output_nodes, NeuralNetworkConfig config);
    MatrixXd backward(MatrixXd chain_error);
    MatrixXd forward(MatrixXd X);
};


#endif //NN_DENSE_H