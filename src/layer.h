#ifndef NN_LAYER_H
#define NN_LAYER_H

#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "neural_network_config.h"

using Eigen::MatrixXd;

class Layer
{
    public:
        int type;
        virtual MatrixXd forward(MatrixXd X, NeuralNetworkConfig config) = 0;
        virtual MatrixXd backward(MatrixXd chain_error) = 0;
        virtual void save_layer(std::ofstream &to) = 0;
        virtual void load_layer(std::ifstream &from) = 0;
};


#endif //NN_LAYER_H