#include <iostream>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <mutex>
#include "../threads/threads_utils.h"
#include <chrono>

using std::mutex;
using std::vector;
using std::thread;
using std::ref;

int main(){
    Eigen::MatrixXd m1 = Eigen::MatrixXd::Random(10,3);
    Eigen::MatrixXd m2 = Eigen::MatrixXd::Random(3,10);
    Eigen::MatrixXd res;

    for (int i = 1; i < 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        res = mult_with_threads(i, m1, m2);
        auto current_time = std::chrono::high_resolution_clock::now();
        std::cout << i << ": " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << std::endl;
        std::cout << res << std::endl;
    }
}