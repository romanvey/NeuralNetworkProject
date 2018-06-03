#ifndef NN_ACTIVATION_H
#define NN_ACTIVATION_H

#include <Eigen/Dense>
#include "layer.h"
#include "neural_network_config.h"
#include <string.h>

using Eigen::MatrixXd;

class ActivationLayer: public Layer {
private:
	MatrixXd _sigmoid(MatrixXd X);
    MatrixXd _derivative_sigmoid(MatrixXd X);

	MatrixXd _relu(MatrixXd X);
    MatrixXd _derivative_relu(MatrixXd X);


	MatrixXd _activ_function(MatrixXd X);
	MatrixXd _deriv_function(MatrixXd X);

	std::string activation_name = "sigmoid";
	NeuralNetworkConfig config;
	MatrixXd value;

public:
	ActivationLayer(std::string activation_name);
	ActivationLayer();

    MatrixXd forward(MatrixXd X, NeuralNetworkConfig config) override;
    MatrixXd backward(MatrixXd chain_error) override;
	void save_layer(std::ofstream &to) override;
	void load_layer(std::ifstream &from) override;
};

#endif //NN_ACTIVATION_H