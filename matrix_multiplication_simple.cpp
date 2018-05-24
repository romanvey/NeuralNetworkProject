#include <iostream>


#include <fstream>

#include <algorithm>
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>
#include <Eigen/Dense>
#include <vector>
#include <math.h>

using Eigen::MatrixXd;


#define MAX_VAL 1000
#define MIN_VAL 1

int max(long i, long i1, long i2);

using std::string;
using std::vector;
using string = std::string;
using std::cout;
using std::endl;
using std::pair;
using std::ref;


inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

MatrixXd randomSquareMatrix(int dimension, int dimension_long) {
    /*
        Generate 2 dimensional random matrix.
    */

    MatrixXd matrix(dimension, dimension_long);


    srandom(time(0) + clock() + random());

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension_long; j++) {
            matrix(i, j) = rand() % MAX_VAL + MIN_VAL;
        }
    }

    return matrix;
}

double max_size(long a) {
    vector<double> v = {2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0};
    double m = 1.1, prev = 1;
    int i =0;
    while( m > 1 && i < v.size() && abs(prev - m) > 0.01){
        prev = m;
        if (m < a / v[i])
            m = a / v[i];

        ++i;


    }
    if (m >= 1){
        return m;
    }
    if (prev - 1.1 < 0.01)
        return 1;
    return prev;
}


void small_matrix_mult(MatrixXd a, vector<int> data_a, MatrixXd b, vector<int> data_b, MatrixXd &c) {
    // y - down, x - right
    // vector<int> data_a  int st_a_y, int st_a_x
    // a, b matrix to multiply
    if (data_a.size() < 2 || data_b.size() < 2)
        return;
    if (a.cols() != b.rows())
        return;
    MatrixXd res = a * b;
    c.block(data_a[0], data_b[1], a.rows(), b.cols()) += res;
}

void matrix_mult(MatrixXd a, MatrixXd b, MatrixXd &c) {
    if (a.cols() != b.rows())
        return;
    int size_block_col_a, size_block_row_a, size_block_col_b;

    size_block_col_a = (int) round(max_size(a.cols()));
    size_block_row_a = (int) round(max_size(a.rows()));
    size_block_col_b = (int) round(max_size(b.cols()));
    cout <<"block col a " << size_block_col_a << ", block col b  "<< size_block_col_b<< ", block row a " << size_block_row_a<<endl;

    int i = 0, j, k;
    vector<int> data_a, data_b;
    while (a.cols() - (i ) * size_block_col_a > 0) {
        j = 0;
        while (a.rows() - (j ) * size_block_row_a > 0) {
            k = 0;
            while (b.cols() - (k ) * size_block_col_b > 0) {
                data_a = {j * size_block_row_a, i * size_block_col_a};
                data_b = {i * size_block_col_a, k * size_block_col_b};
                small_matrix_mult(a.block(data_a[0], data_a[1], size_block_row_a, size_block_col_a), data_a,
                                  b.block(data_b[0], data_b[1], size_block_col_a, size_block_col_b), data_b, ref(c));
                ++k;
            }

            ++j;
        }
        ++i;
    }
    long remainder_i = a.cols() - i * size_block_col_a;
    long remainder_j = a.rows() - j * size_block_row_a;
    long remainder_k = b.cols() - k * size_block_col_b;
//    int size_rem_col_a = (int) round(max_size(a.cols())), size_rem_row_a = (int) round(max_size(a.rows())),
//            size_rem_col_b = (int) round(max_size(b.cols()));
    // TODO divide by smaller blocks
    if(remainder_i != 0 || remainder_j != 0 || remainder_k != 0) {
        data_a = {j * size_block_row_a, 0};
        data_b = {0, k * size_block_col_b};
        small_matrix_mult(a.block(data_a[0], data_a[1], remainder_j, a.cols()), data_a,
                          b.block(data_b[0], data_b[1], b.rows(), remainder_k), data_b, ref(c));
        data_a = {0, i * size_block_col_a};
        data_b = {i * size_block_col_a, 0};
        small_matrix_mult(a.block(data_a[0], data_a[1], a.rows() - remainder_j, remainder_i), data_a,
                          b.block(data_b[0], data_b[1], remainder_j, b.cols() - remainder_k), data_b, ref(c));

    }


}


int main() {
    //MatrixXd m = randomSquareMatrix(5, 7);
    MatrixXd mat1(2, 2), mat2(2, 3), res(4,4);
    mat1 << 1, 0,
            0, 1;
    mat2 << 1, 2, 3,
            0, 3, 0;
    vector<int> data_mat1 = {0, 0, 2, 2}, data_mat2 = {0, 0, 2, 3};
    //small_matrix_mult(mat1, data_mat1, mat2, data_mat2, ref(res));

    MatrixXd a(4,4), b(4,4);
    a << 2, 1, 5, 3,
         0, 7, 1, 6,
         9, 2, 4, 4,
         3, 6, 7, 2;
    b << 6, 1, 2, 3,
         4, 5, 6, 5,
         1, 9, 8, -8,
         4, 0, -8, 5;
    matrix_mult(a, b, ref(res));

    cout << res << endl;
    return 0;
}