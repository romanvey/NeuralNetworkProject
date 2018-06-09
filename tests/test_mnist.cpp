#include "test_nn.h"

using Eigen::MatrixXd;
using namespace std;


int main() {
    // * DenseLayer Tests
//	std::cout << "DenseLayer Test started" << std::endl;
    DenseLayer dl(4, 5);
//	std::cout << dl.w << std::endl;
//	std::cout << dl.config.lr << std::endl;

    MatrixXd s(2, 4);
    s << 0.1, 0.2, 2.1, -0.5,
            0.1, 0.2, 2.1, -0.5;
//	std::cout << s.colwise().sum() << std::endl;
//	std::cout << "DenseLayer Test ended" << std::endl;


    // Dot product Tests
//	std::cout << "Dot product Test started" << std::endl;
    MatrixXd mat(2, 2);
    mat << 1, 2, 2, 4;
//	std::cout << mat << std::endl;
//	std::cout << (mat * mat) << std::endl;
//	std::cout << "Dot product Test ended" << std::endl;

    // Vector adding Tests
//	std::cout << "Vector adding Test started" << std::endl;
    MatrixXd t1(2, 4);
    t1 << 1, 2, 3, 4, 5, 6, 7, 8;

    MatrixXd t2(1, 4);
    t2 << 0, 1, 1, 0;


    for (int i = 0; i < t1.rows(); i++) {
        t1.row(i) += t2;
    }
    //	std::cout << t1 << std::endl;
    //	std::cout << "Vector adding Test ended" << std::endl;

    // NeuralNetwork tests

     auto A = csv2vector("../resources/mnist_test.csv", ',');
//
	cout<<"Readed"<<endl;
    shuffle_vector(A);
	cout<<"Shuffled"<<endl;	 
    auto key_map = one_hot_encode(A, 0);
	cout<<"Encoded"<<endl;     
	auto X = vector2matrix(A);
	cout<<"Transformed"<<endl;
	
//
    auto train_test = divide_matrix(X, 0.7);
    auto train = train_test.first;
    auto test = train_test.second;
	cout<<"Test/train divided"<<endl;
	 
//
     vector<int> y_cols(10);
     y_cols[0] = 0; y_cols[1] = 1; y_cols[2] = 2; y_cols[3] = 3; y_cols[4] = 4; 
	 y_cols[5] = 5; y_cols[6] = 6; y_cols[7] = 7; y_cols[8] = 8; y_cols[9] = 9; 
	 
//
     auto X_y_train = split_X_y(train, y_cols);
     auto X_train = X_y_train.first;
     auto y_train = X_y_train.second;
//
     auto X_y_test = split_X_y(test, y_cols);
     auto X_test = X_y_test.first;
     auto y_test = X_y_test.second;
	cout<<"X/y divided"<<endl;


    NeuralNetworkConfig conf;
    conf.epochs = 20;
    conf.lr = 0.01;
    conf.threads = 4;
	conf.verbose = true;
    NeuralNetwork nn(conf);

    nn.add(new DenseLayer(X_train.cols(), 512));
    nn.add(new ActivationLayer("relu"));
    nn.add(new DenseLayer(512, 10));
    nn.add(new ActivationLayer("sigmoid"));

	cout<<"Fitted"<<endl;
	nn.save_model("../resources/mnist_model.txt");
	cout<<"Saved"<<endl;

//     Test fitting/predicting
    nn.fit(X_train, y_train);
    cout << "Train score: " << nn.accuracy_classification(X_train, y_train) << endl;
    cout << "Test score: " << nn.accuracy_classification(X_test, y_test) << endl;
	cout<<"Predicted"<<endl;

//

}