#include <iostream>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <mutex>
#include "threads_multiplication.h"

using std::mutex;
using std::vector;
using std::thread;
using std::ref;

int main(){
    Eigen::MatrixXd m1(10, 3);
    Eigen::MatrixXd m2(3, 3);
    Eigen::MatrixXd res;

    m1 << 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6;
    m2 << 1, 1, 1, 1, 1, 1, 1, 1, 1;


    res = mult_with_threads(3, m1, m2);

    std::cout << res;
}