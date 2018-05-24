#include "activation.h"

using Eigen::MatrixXd;

double _sigmoid_function(double x) { return 1 / (1 + exp(-x)); }
double _derivative_sigmoid_function(double x) { double _x = _sigmoid_function(x); return _x * (1 - _x); }

MatrixXd ActivationLayer::_sigmoid(MatrixXd X) {
    MatrixXd newX = X.unaryExpr(&_sigmoid_function);
    return newX;
};

MatrixXd ActivationLayer::_derivative_sigmoid(MatrixXd X) {
    MatrixXd newX = X.unaryExpr(&_derivative_sigmoid_function);
    return newX;
};



MatrixXd ActivationLayer::_activ_function(MatrixXd X){
	if(activation_name == "sigmoid"){
		return _sigmoid(X);
	}
	else{
		return _sigmoid(X);
	}
}


MatrixXd ActivationLayer::_deriv_function(MatrixXd X){
	if(activation_name == "sigmoid"){
		return _derivative_sigmoid(X);
	}
	else{
		return _derivative_sigmoid(X);
	}
}


ActivationLayer::ActivationLayer(std::string activation_name){
	this->activation_name = activation_name;
}
ActivationLayer::ActivationLayer(){}





MatrixXd ActivationLayer::forward(MatrixXd X, NeuralNetworkConfig config){
	if(config.verbose){
		std::cout<<"Activation forward started"<<std::endl;
	}
	this->config = config;
	value = _activ_function(X);
	if(config.verbose){
		std::cout<<"Activation forward ended"<<std::endl;
	}
	return value;

};

MatrixXd ActivationLayer::backward(MatrixXd chain_error){
	if(config.verbose){
		std::cout<<"Activation backward started"<<std::endl;
	}
	MatrixXd t = _deriv_function(value);
	if(config.verbose){
		std::cout<<"Activation backward ended"<<std::endl;
	}
    return t.cwiseProduct(chain_error);
};

