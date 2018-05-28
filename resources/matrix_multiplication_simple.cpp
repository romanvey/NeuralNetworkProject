#include <iostream>


#include <fstream>

#include <algorithm>
#include <functional>
#include <chrono>
#include <atomic>

#include <thread>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using Eigen::MatrixXd;


#define MAX_VAL 1000
#define MIN_VAL 1

using std::string;
using std::vector;
using string = std::string;
using std::cout;
using std::endl;
using std::pair;
using std::ref;


void block_mult(const  MatrixXd &a,const MatrixXd &b, MatrixXd &c, int size_block_col_a, int size_block_row_a, int size_block_col_b,
               int mult_block_col_a, int mult_block_row_a, int mult_block_col_b, int i, int j, int k) ;

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

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


double max_size(long a) {
    vector<double> v = {2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0};
    double m = 5000, prev = 1, maybe_m, prev_mm = m;
    int i = 0;
    while (m > 1 && i < v.size() && abs(prev - m) > 0.01) {
        prev = m;
        maybe_m = a / v[i];
        if (maybe_m >= 1.5 && v[i] + maybe_m < prev_mm) {
            m = maybe_m;
            prev_mm = v[i] + maybe_m;
        }
        ++i;


    }
    if (m >= 1) {
        return m;
    }
    if (prev - 1.1 < 0.01)
        return 1;
    return prev;
}


void small_matrix_mult(const MatrixXd& a, vector<int> data_a, const MatrixXd &b, vector<int> data_b, MatrixXd &c) {
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

void matrix_mult(const MatrixXd &a, const MatrixXd &b, MatrixXd &c) {
    if (a.cols() != b.rows())
        return;
    int size_block_col_a, size_block_row_a, size_block_col_b;

    size_block_col_a = (int) floor(max_size(a.cols()));
    size_block_row_a = (int) floor(max_size(a.rows()));
    size_block_col_b = (int) floor(max_size(b.cols()));
    cout << "block col a " << size_block_col_a << ", block col b  " << size_block_col_b << ", block row a "
         << size_block_row_a << endl;
    long remainder_i, remainder_j, remainder_k;
    int i = 0, j, k;
    vector<int> data_a, data_b;
    while (a.cols() - (i + 1) * size_block_col_a > 0) {
        j = 0;
        while (a.rows() - (j + 1) * size_block_row_a > 0) {
            block_mult(a, b, ref(c), size_block_col_a, size_block_row_a, size_block_col_b, size_block_col_a,
                      size_block_row_a, size_block_col_b, i, j, k);
            ++j;
        }
        remainder_j = a.rows() - j * size_block_row_a;

        block_mult(a, b, ref(c), size_block_col_a, size_block_row_a, size_block_col_b, size_block_col_a,
                  (int) remainder_j, size_block_col_b, i, j, k);

        ++i;
    }

    remainder_i = a.cols() - i * size_block_col_a;
    j = 0;
    while (a.rows() - (j + 1) * size_block_row_a > 0) {
        block_mult(a, b, ref(c), size_block_col_a, size_block_row_a, size_block_col_b, (int)remainder_i,
                  size_block_row_a, size_block_col_b, i, j, k);
        ++j;
    }
    remainder_j = a.rows() - j * size_block_row_a;

    block_mult(a, b, ref(c), size_block_col_a, size_block_row_a, size_block_col_b, (int) remainder_i, (int) remainder_j,
              size_block_col_b, i, j, k);


}


int main() {
    //MatrixXd m = randomSquareMatrix(5, 7);
    MatrixXd mat1(2, 2), mat2(2, 3), res(100, 90);

    vector<int> data_mat1 = {0, 0, 2, 2}, data_mat2 = {0, 0, 2, 3};
    //small_matrix_mult(mat1, data_mat1, mat2, data_mat2, ref(res));

    MatrixXd a(100, 100), b(100, 90);
    a = randomSquareMatrix(100, 100);
    cout<< a.rows() <<"x"<<a.cols()<<endl;
    b = randomSquareMatrix(100, 90);
    auto start_time = get_current_time_fenced();
    matrix_mult(a, b, ref(res));
    auto finish_time = get_current_time_fenced();

    cout <<"My result: " <<res.block(0,0,2,5) << endl;

    cout <<"Time :  " << to_us(finish_time - start_time) << endl;
    start_time = get_current_time_fenced();
    res = a * b;
    finish_time = get_current_time_fenced();
    cout << "Try result: " << res.block(0, 0, 2, 5) << endl;

    cout << "Eigen Time :  " << to_us(finish_time - start_time) << endl;
    return 0;
}

void block_mult(const MatrixXd &a,const MatrixXd &b, MatrixXd &c, int size_block_col_a, int size_block_row_a,
                int size_block_col_b, int mult_block_col_a, int mult_block_row_a, int mult_block_col_b, int i, int j,
                int k) {
    vector<int> data_a, data_b;
    k = 0;
    data_a = {j * size_block_row_a, i * size_block_col_a};
    data_b = {i * size_block_col_a, 0};
    while (b.cols() - (k + 1) * size_block_col_b > 0) {

        data_b[1] = k * size_block_col_b;

        small_matrix_mult(a.block(data_a[0], data_a[1], mult_block_row_a, mult_block_col_a), data_a,
                          b.block(data_b[0], data_b[1], mult_block_col_a, mult_block_col_b), data_b, ref(c));
        ++k;
    }

    long remainder_k = b.cols() - k * size_block_col_b;
    data_b[1] = k * size_block_col_b;
    small_matrix_mult(a.block(data_a[0], data_a[1], mult_block_row_a, mult_block_col_a), data_a,
                      b.block(data_b[0], data_b[1], mult_block_col_a, remainder_k), data_b, ref(c));

}