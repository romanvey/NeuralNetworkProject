# Neural Networks library

CMake version: 3.0

Eigen version: 3.3

C++ 14

## Install Eigen
download archive http://bitbucket.org/eigen/eigen/get/3.3.4.tar.bz2 and follow the INSTALL instructions

## Compile library
```
mkdir cmake-build-release && cd cmake-build-release && cmake ../ && make && ./test
```

## Code examples
### Include header

```cpp
#include "../src/neural_network.h"
#include "../src/matrix_utils.h"
#include "../src/neural_network_config.h"
#include "../src/dense.h"
#include "../src/activation.h"
#include <fstream>
#include <iostream>
#include <utility>
```

### Code example
```cpp
// read .csv file
auto A = csv2vector("../resources/iris_old.csv", ',');
shuffle_vector(A);
auto key_map = one_hot_encode(A, 4);
auto X = vector2matrix(A);

// split test/train
auto train_test = divide_matrix(X, 0.7);
auto train = train_test.first;
auto test = train_test.second;

// mark the y columns
vector<int> y_cols(3);
y_cols[0] = 4;
y_cols[1] = 5;
y_cols[2] = 6;

// split X/y for train
auto X_y_train = split_X_y(train, y_cols);
auto X_train = X_y_train.first;
auto y_train = X_y_train.second;

// split X/y for test
auto X_y_test = split_X_y(test, y_cols);
auto X_test = X_y_test.first;
auto y_test = X_y_test.second;

// make a configuration class
NeuralNetworkConfig conf;
conf.epochs = 1200;
conf.lr = 0.001;
conf.threads = 4;

// make a neural network class
NeuralNetwork nn(conf);

// add some layers
nn.add(new DenseLayer(4, 6));
nn.add(new ActivationLayer("relu"));
nn.add(new DenseLayer(6, 6));
nn.add(new ActivationLayer("relu"));
nn.add(new DenseLayer(6, 3));
nn.add(new ActivationLayer("sigmoid"));

// test fitting/predicting
nn.fit(X_train, y_train);
cout << "Train score: " << nn.accuracy_classification(X_train, y_train) << endl;
cout << "Test score: " << nn.accuracy_classification(X_test, y_test) << endl;

// print predictions
cout << nn.predict(X_train.block(0, 0, 1, X_train.cols())) << endl;
cout << nn.predict_labled(X_train.block(0, 0, 1, X_train.cols()), key_map)[0] << endl;

// custom predictions with the original labels
MatrixXd to_predict(1, 4);
to_predict<<5 ,2.3, 3.4, 1;
cout << nn.predict_labled(to_predict, key_map)[0] << endl;

// save the model
nn.save_model("../resources/iris_model.txt");
```

### Load model 
```cpp
MatrixXd to_predict(1, 4);
to_predict<<5 ,2.3, 3.4, 1;

NeuralNetwork nn2;
nn2.load_model("../resources/iris_model.txt");
cout<<nn2.predict(to_predict)<<endl;
```

### Authors
[Roman Vey](https://www.facebook.com/roman.vey)

[Volodymyr Zabulskyi](https://www.facebook.com/zabulskyy)
