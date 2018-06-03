#ifndef NEURALNETWORKPROJECT_MATRIX_MULTIPLICATION_H
#define NEURALNETWORKPROJECT_MATRIX_MULTIPLICATION_H

#include <iostream>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <mutex>

using std::mutex;
using std::vector;
using std::thread;
using std::ref;

Eigen::MatrixXd mult_with_threads(int n, const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2);

#endif //NEURALNETWORKPROJECT_MATRIX_MULTIPLICATION_H
