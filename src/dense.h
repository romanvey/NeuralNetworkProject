#ifndef NN_DENSE_H
#define NN_DENSE_H

#include<random>
#include <Eigen/Dense>
#include "layer.h"
#include "matrix_utils.h"
#include "neural_network_config.h"
#include "../thread/threads_utils.h"
#include <cmath>

using Eigen::MatrixXd;

class DenseLayer: public Layer {
private:
	NeuralNetworkConfig config;
	int input_nodes, output_nodes;
	MatrixXd w, b, value;
public:
	DenseLayer(int input_nodes, int output_nodes);
	DenseLayer();
    MatrixXd forward(MatrixXd X, NeuralNetworkConfig config) override;
    MatrixXd backward(MatrixXd chain_error) override;
	void save_layer(std::ofstream &to) override;
	void load_layer(std::ifstream &from) override;
};


#endif //NN_DENSE_H