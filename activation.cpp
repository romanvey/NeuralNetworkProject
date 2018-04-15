#include "activation.h"

using Eigen::MatrixXd;

double _sigmoid_function(double x) { return 1 / (1 + exp(-x)); }

MatrixXd Activation::_sigmoid(MatrixXd X) {
    MatrixXd newX = X.unaryExpr(&_sigmoid_function);
    return newX;
};

double _derivative_sigmoid_function(double x) { return x * (1 - x); }

MatrixXd Activation::_derivative_sigmoid(MatrixXd X) {
    MatrixXd newX = X.unaryExpr(&_derivative_sigmoid_function);
    newX = newX.unaryExpr(&_derivative_sigmoid_function);
    return newX;
};

MatrixXd Activation::backward(MatrixXd chain_error) {

};

MatrixXd Activation::forward(MatrixXd X, double lr) {};
