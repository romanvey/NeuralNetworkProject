#ifndef NN_LAYER_H
#define NN_LAYER_H

#include <Eigen/Dense>
#include <iostream>

using Eigen::Matrix2d;

class Layer
{
    public:
        virtual Matrix2d forward(Matrix2d X, double lr) = 0;
        virtual Matrix2d backward(Matrix2d chain_error) = 0;
};


#endif //NN_LAYER_H