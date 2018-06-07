#ifndef NEURALNETWORKPROJECT_MPI_UTILS_H
#define NEURALNETWORKPROJECT_MPI_UTILS_H
#include <iostream>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <mutex>

using std::mutex;
using std::vector;
using std::thread;
using std::ref;

Eigen::MatrixXd mult_with_mpi(const int n, const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2);

#endif //NEURALNETWORKPROJECT_MPI_UTILS_H
