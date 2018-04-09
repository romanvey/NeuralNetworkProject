#include "activation.h"

using Eigen::Matrix2d;

Matrix2d Activation::_sigmoid(Matrix2d X) {
    double sigmoid(double x) { return 1 / (1 + exp(-x)); }
    Matrix2d newX = X.unaryExpr(&sigmoid);
    return newX;
};

Matrix2d Activation::_derivative_sigmoid(Matrix2d X) {
    double derivative_sigmoid(double x) { return x * (1 - x); }
    double sigmoid(double x) { return 1 / (1 + exp(-x)); }

    Matrix2d newX = X.unaryExpr(&sigmoid);
    newX = newX.unaryExpr(&derivative_sigmoid);
    return newX;
};

Matrix2d Activation::backward(Matrix2d chain_error) {

};

Matrix2d Activation::forward(Matrix2d X, double lr) {};
