#ifndef NN_LAYER_H
#define NN_LAYER_H

#include <Eigen/Dense>
#include <iostream>
#include "neural_network_config.h"

using Eigen::MatrixXd;

class Layer
{
    public:
        virtual MatrixXd forward(MatrixXd X, NeuralNetworkConfig config) = 0;
        virtual MatrixXd backward(MatrixXd chain_error) = 0;
};


#endif //NN_LAYER_H