#include "dense.h"

MatrixXd dot(MatrixXd a, MatrixXd b, NeuralNetworkConfig config){
	// TODO: implement more multiplications
	if (config.use_mpi){
	    // TODO: MPI
	}
	else if (config.threads == 0){
        return a * b;
	}
	else {
	    int _n = config.threads;
	    return mult_with_threads(_n, a, b);
	}
}




DenseLayer::DenseLayer(int input_nodes, int output_nodes){
	this->type = 0;
	this->input_nodes = input_nodes;
	this->output_nodes = output_nodes;
	w = MatrixXd::Random(input_nodes ,output_nodes);
	b = MatrixXd::Random(1 ,output_nodes);
//	w = MatrixXd::Ones(input_nodes ,output_nodes);
//	b = MatrixXd::Zero(1 ,output_nodes);

}

DenseLayer::DenseLayer(){
	this->type = 0;
}



MatrixXd DenseLayer::forward(MatrixXd X, NeuralNetworkConfig config){
	if(config.verbose){
		std::cout<<"Dense forward started"<<std::endl;
	}
	this->config = config;
	value = X;
	MatrixXd result = dot(X, w, config);

	for(int i = 0; i < result.rows(); i++){
		result.row(i) += b;
	}

//    std::cout << "X*w is: \n" << std::endl;
//    std::cout << result << std::endl;

	if(config.verbose){
		std::cout<<"Dense forward ended"<<std::endl;
	}

//    std::cout << "value is: \n" << std::endl;
//	std::cout << value << std::endl;
	return result;
}


MatrixXd DenseLayer::backward(MatrixXd chain_error){
	if(config.verbose){
		std::cout<<"Dense backward started"<<std::endl;
	}
	MatrixXd result = dot(chain_error, w.transpose(), config);

	MatrixXd changed_w = w + (dot(value.transpose(), chain_error, config) * config.lr);
	MatrixXd changed_b = b + (chain_error.colwise().sum() * config.lr);
	
	w = config.inertia * changed_w + (1 - config.inertia) * w;
	b = config.inertia * changed_b + (1 - config.inertia) * b;
	if(config.verbose){
		std::cout<<"Dense backward ended"<<std::endl;
	}

//    std::cout << "cost is : \n";
//    std::cout << chain_error << std::endl;
//    std::cout << "bias is : \n";
//    std::cout << b << std::endl;
//    std::cout << "weights are: \n";
//    std::cout << w << std::endl;

	return result;
}


void DenseLayer::save_layer(std::ofstream &to){
	save_matrix(to, w, 1);
	save_matrix(to, b, 1);
}

void DenseLayer::load_layer(std::ifstream &from){
	if(from.is_open()){
		int nrows, ncols;
		from >> nrows >> ncols;
		this->input_nodes = nrows;
		this->output_nodes = ncols;
		std::cout<<"Load layer"<<nrows<<" "<<ncols<<std::endl;
		w = read_matrix(from, nrows, ncols);
		b = read_matrix(from);	
	}
}