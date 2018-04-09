#ifndef NN_LAYER_H
#define NN_LAYER_H

#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;

class Layer
{
    public:
        virtual MatrixXd forward(MatrixXd X, double lr) = 0;
        virtual MatrixXd backward(MatrixXd chain_error) = 0;
};


#endif //NN_LAYER_H