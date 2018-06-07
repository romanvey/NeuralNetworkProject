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

    // NeuralNetwork test

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
     // ! tihs is ugly
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
    conf.epochs = 800;
    conf.lr = 0.005;
    conf.threads = 10;
    NeuralNetwork nn(conf);

    nn.add(new DenseLayer(4, 6));
    nn.add(new ActivationLayer("relu"));
    nn.add(new DenseLayer(6, 6));
    nn.add(new ActivationLayer("relu"));
    nn.add(new DenseLayer(6, 3));
    nn.add(new ActivationLayer("sigmoid"));


    // Test saving/loading
    nn.save_model("../resources/model.txt");
    NeuralNetwork nn2;
    nn2.load_model("../resources/model.txt");
    nn2.save_model("../resources/model2.txt");


//     Test fitting/predicting
     nn.fit(X_train, y_train);
     cout << "Train score: " << nn.accuracy_classification(X_train, y_train) << endl;
     cout << "Test score: " << nn.accuracy_classification(X_test, y_test) << endl;


     cout << nn.predict(X_train.block(0, 0, 1, X_train.cols())) << endl;
     cout << nn.predict_labled(X_train.block(0, 0, 1, X_train.cols()), key_map)[0] << endl;
//
//
//
     ifstream fin ("../resources/data.txt");
     MatrixXd myX = read_matrix(fin);
     MatrixXd myY = read_matrix(fin);
     fin.close();
     cout << "X = " << endl << myX << endl;
     cout << "Y = " << endl << myY << endl;
//
     std::ofstream fout("../resources/result.txt");
     save_matrix(fout, myY, 1);
     fout.close();


}