#include "neural_network.h"

NeuralNetwork::NeuralNetwork(NeuralNetworkConfig config)
{
	this->config = config;
}

NeuralNetwork::NeuralNetwork()
{
	NeuralNetworkConfig config;
	this->config = config;
}

void NeuralNetwork::add(Layer *layer)
{
	layers.push_back(layer);
};

void NeuralNetwork::fit(MatrixXd X, MatrixXd y)
{
	for (int epoch = 0; epoch < config.epochs; epoch++)
	{
		// * Forward propagation
		if(config.verbose){
			std::cout<<"Epoch " << epoch << std:: endl; 
			std::cout << "Forward propagation started" << std::endl;
		}
		MatrixXd curr = X;
		for (int i = 0; i < layers.size(); i++)
		{
			curr = layers[i]->forward(curr, config);
		}

		// * Cost function
//        std::cout << "first chain error is : \n";
        MatrixXd chain_error = y - curr;
//        std::cout << chain_error << std::endl;

		// * Back propagation
		if(config.verbose){
			std::cout << "Forward propagation ended" << std::endl;
			std::cout << "Backward propagation started" << std::endl;
		}
		for (int i = layers.size() - 1; i >= 0; i--)
		{
			chain_error = layers[i]->backward(chain_error);
//            std::cout << "in loop chain error is : \n";
//            std::cout << chain_error << std::endl;
		}
		if(config.verbose){
			std::cout << "Backward propagation ended" << std::endl;
		}
	}
}

MatrixXd NeuralNetwork::predict(MatrixXd X)
{
	MatrixXd curr = X;
	for (int i = 0; i < layers.size(); i++)
	{
		curr = layers[i]->forward(curr, config);
	}
	return curr;
}

int _get_max_ind(MatrixXd A, int row){
	int maxi=0;
	double maxv=0;
	for(int col=0; col<A.cols(); ++col){
		if (A(row, col) > maxv){
			maxv = A(row, col);
			maxi = col;
		}
	}
	return maxi;
}


double NeuralNetwork::accuracy_regression(MatrixXd X, MatrixXd y){
	MatrixXd res = predict(X);
	res -= y;
	res = res.cwiseProduct(res);
	return res.sum();
}

double NeuralNetwork::accuracy_classification(MatrixXd X, MatrixXd y){
	MatrixXd res = predict(X);
	double corr = 0;
	for(int i = 0; i < res.rows(); i++){
		if(_get_max_ind(res, i) == _get_max_ind(y, i)){
			corr++;
		}
	}
	return corr / res.rows();

}

std::vector<std::string> NeuralNetwork::predict_labled(MatrixXd X, std::map<int, std::string> m){
	MatrixXd res = predict(X);
	std::vector<std::string> pred;
	int key;
	for(int i = 0; i < res.rows(); i++){
		key = _get_max_ind(res, i);
		pred.push_back(m.at(key));
	}
	return pred;
}

	
