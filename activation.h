#ifndef NN_ACTIVATION_H
#define NN_ACTIVATION_H

#include <Eigen/Dense>
#include "layer.h"
#include "neural_network_config.h"
#include <string.h>

using Eigen::MatrixXd;

class ActivationLayer: public Layer {
public:
	ActivationLayer(std::string activation_name);
	ActivationLayer();

    MatrixXd _sigmoid(MatrixXd X);
    MatrixXd _derivative_sigmoid(MatrixXd X);

	MatrixXd _activ_function(MatrixXd X);
	MatrixXd _deriv_function(MatrixXd X);

    MatrixXd forward(MatrixXd X, NeuralNetworkConfig config);
    MatrixXd backward(MatrixXd chain_error);

	std::string activation_name = "sigmoid";
	NeuralNetworkConfig config;
	MatrixXd value;
};

#endif //NN_ACTIVATION_H