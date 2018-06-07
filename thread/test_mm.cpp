#include <iostream>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <mutex>
#include "threads_utils.h"
#include <chrono>

using std::mutex;
using std::vector;
using std::thread;
using std::ref;

int test(){
    Eigen::MatrixXd m1 = Eigen::MatrixXd::Ones(5000,300);
    Eigen::MatrixXd m2 = Eigen::MatrixXd::Ones(300,5000);
    Eigen::MatrixXd res;

    for (int i = 1; i < 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        res = mult_with_threads(i, m1, m2);
        auto current_time = std::chrono::high_resolution_clock::now();
        std::cout << i << ": " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << std::endl;
    }
}