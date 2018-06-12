#include "test_nn.h"

using Eigen::MatrixXd;
using namespace std;


int main() {


     auto A = csv2vector("../resources/iris_old.csv", ',');
//
     shuffle_vector(A);
     auto key_map = one_hot_encode(A, 4);
     auto X = vector2matrix(A);
//
     auto train_test = divide_matrix(X, 0.7);
     auto train = train_test.first;
     auto test = train_test.second;
//
     vector<int> y_cols(3);
     y_cols[0] = 4;
     y_cols[1] = 5;
     y_cols[2] = 6;
//
     auto X_y_train = split_X_y(train, y_cols);
     auto X_train = X_y_train.first;
     auto y_train = X_y_train.second;
//
     auto X_y_test = split_X_y(test, y_cols);
     auto X_test = X_y_test.first;
     auto y_test = X_y_test.second;


    NeuralNetworkConfig conf;
    conf.epochs = 1200;
    conf.lr = 0.001;
    conf.threads = 4;
    NeuralNetwork nn(conf);

    nn.add(new DenseLayer(4, 6));
    nn.add(new ActivationLayer("relu"));
    nn.add(new DenseLayer(6, 6));
    nn.add(new ActivationLayer("relu"));
    nn.add(new DenseLayer(6, 3));
    nn.add(new ActivationLayer("sigmoid"));



//     Test fitting/predicting
    nn.fit(X_train, y_train);
    cout << "Train score: " << nn.accuracy_classification(X_train, y_train) << endl;
    cout << "Test score: " << nn.accuracy_classification(X_test, y_test) << endl;


	
    cout << nn.predict(X_train.block(0, 0, 1, X_train.cols())) << endl;
    cout << nn.predict_labled(X_train.block(0, 0, 1, X_train.cols()), key_map)[0] << endl;
	
	MatrixXd to_predict(1, 4);
	to_predict<<5 ,2.3, 3.4, 1;
	cout << nn.predict_labled(to_predict, key_map)[0] << endl;
	 

	nn.save_model("../resources/iris_model.txt");


}