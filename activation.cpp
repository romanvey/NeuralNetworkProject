#include "activation.h"

using Eigen::Matrix2d;
double _sigmoid_function(double x) { return 1 / (1 + exp(-x)); }
Matrix2d Activation::_sigmoid(Matrix2d X) {
    Matrix2d newX = X.unaryExpr(&_sigmoid_function);
    return newX;
};

double _derivative_sigmoid_function(double x) { return x * (1 - x); }
Matrix2d Activation::_derivative_sigmoid(Matrix2d X) {
    Matrix2d newX = X.unaryExpr(&_derivative_sigmoid_function);
    newX = newX.unaryExpr(&_derivative_sigmoid_function);
    return newX;
};

Matrix2d Activation::backward(Matrix2d chain_error) {

};

Matrix2d Activation::forward(Matrix2d X, double lr) {};
