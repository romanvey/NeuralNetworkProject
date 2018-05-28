#include <iostream>


#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include "tsafe_queue.h"

using Eigen::MatrixXd;
using std::thread;
using std::pair;
using std::make_pair;

#define MAX_VAL 100
#define MIN_VAL -100


class data4que {

public:
    MatrixXd a, b;
    vector<int> data_a, data_b;
    data4que(MatrixXd &a, MatrixXd &b, vector<int> data_a, vector<int> data_b);
    data4que();
    void clean(){a(0); b(0); data_a ={0}; data_b= {0};};
};

data4que::data4que(MatrixXd &a, MatrixXd &b, vector<int> data_a, vector<int> data_b) {
    a = a;
    b = b;
    data_a = data_a;
    data_b = data_b;
}

data4que::data4que() {
    a = MatrixXd::Zero(1,1);
    b = MatrixXd::Zero(1,1);
    data_a = {0};
    data_b = {0};
}


//struct data4que {
//    MatrixXd a, b;
//    vector<int> data_a, data_b;
//};

struct matrix_data {
    MatrixXd mat;
    int num_cols, num_rows, num_rows2mult, num_cols2mult;
};


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
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


double max_size(long a) {
    vector<double> v = {2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0};
    double m = a, prev = 1, maybe_m, prev_mm = m;
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


void small_matrix_mult(MatrixXd &c, tsafe_queue<data4que> &data_queue, mutex &mux) {
    // y - down, x - right
    // vector<int> data_a  int st_a_y, int st_a_x
    // a, b matrix to multiply
    data4que d;
    if (!data_queue.try_pop(d)) {
        data_queue.wait_and_pop(d);
        // here can be pill
    }
    if (d.a.cols() != d.b.rows())
        return;
    MatrixXd res = d.a * d.b;
    std::unique_lock<std::mutex> lock(mux);
    c.block(d.data_a[0], d.data_b[1], d.a.rows(), d.b.cols()) += res;

}


void real_data2que_pusher(const MatrixXd &a, const MatrixXd &b, int size_block_col_a, int size_block_row_a,
                          int size_block_col_b, int mult_block_row_a, int mult_block_col_a, int mult_block_col_b, int i,
                          int j, int k, tsafe_queue<data4que> &data_queue) {
    vector<int> data_a, data_b;

    data4que temp_data2que;

    k = 0;
    data_a = {j * size_block_row_a, i * size_block_col_a};
    data_b = {i * size_block_col_a, 0};

    while (b.cols() - (k + 1) * size_block_col_b > 0) {

        data_b[1] = k * size_block_col_b;
        cout << "  data_a[0], data_a[1], mult_row_a, col_a  " << data_a[0]<<" "<< data_a[1] <<" "<< mult_block_row_a<<" "<< mult_block_col_a<<  endl;
        temp_data2que.data_a = data_a;
        temp_data2que.a = a.block(data_a[0], data_a[1], mult_block_row_a, mult_block_col_a);

        temp_data2que.b = b.block(data_b[0], data_b[1], mult_block_col_a, mult_block_col_b);
        temp_data2que.data_b = data_b;
        data_queue.push(temp_data2que);
        ++k;
        temp_data2que.clean();
    }

    long remainder_k = b.cols() - k * size_block_col_b;
    data_b[1] = k * size_block_col_b;
//    small_matrix_mult(a.block(data_a[0], data_a[1], mult_block_row_a, mult_block_col_a), data_a,
//                      b.block(data_b[0], data_b[1], mult_block_col_a, remainder_k), data_b, ref(c));
    temp_data2que.b = b.block(data_b[0], data_b[1], mult_block_col_a, remainder_k);

    temp_data2que.data_a = data_a;
    temp_data2que.a = a.block(data_a[0], data_a[1], mult_block_row_a, mult_block_col_a);

    temp_data2que.data_b = data_b;
    data_queue.push(temp_data2que);
    temp_data2que.clean();
}



void main_pusher(const MatrixXd &a, const MatrixXd &b, int size_block_col_a, int size_block_row_a,
                 int size_block_col_b, tsafe_queue<data4que> &data_queue) {

    long remainder_i, remainder_j;
    vector<int> temp_data;
    int i = 0, j = 0, k = 0;

    while (a.cols() - (i + 1) * size_block_col_a > 0) {
        j = 0;


        while (a.rows() - (j + 1) * size_block_row_a > 0) {
            /*
             *
void real_data2que_pusher(a, b, block_col_a, block_row_a,
                          iblock_col_b, mult_block_row_a,mult_block_col_a, mult_block_col_b, int i,
                          int j, int k, tsafe_queue<data4que> &data_queue) {

             */
            real_data2que_pusher(a, b, size_block_col_a, size_block_row_a, size_block_col_b, size_block_row_a,
                                 size_block_col_a, size_block_col_b, i, j, k, ref(data_queue));

            ++j;
        }
        remainder_j = a.rows() - j * size_block_row_a;
        real_data2que_pusher(a, b, size_block_col_a, size_block_row_a, size_block_col_b, (int) remainder_j,
                             size_block_col_a, size_block_col_b, i, j, k, ref(data_queue));


        ++i;
    }
    // in mult row_a, col_a, col_b
    remainder_i = a.cols() - i * size_block_col_a;
    j = 0;
    while (a.rows() - (j + 1) * size_block_row_a > 0) {

        real_data2que_pusher(a, b, size_block_col_a, size_block_row_a, size_block_col_b, size_block_row_a,
                             (int) remainder_i, size_block_col_b, i, j, k, ref(data_queue));

        ++j;
    }
    remainder_j = a.rows() - j * size_block_row_a;
    real_data2que_pusher(a, b, size_block_col_a, size_block_row_a, size_block_col_b, (int) remainder_j,
                         (int)remainder_i, size_block_col_b, i, j, k, ref(data_queue));

}

void matrix_mult(const MatrixXd &a, const MatrixXd &b, MatrixXd &c) {
    if (a.cols() != b.rows())
        return;

    int num_threads = 5;
    int size_block_col_a, size_block_row_a, size_block_col_b;
    size_block_col_a = (int) floor(max_size(a.cols()));
    size_block_row_a = (int) floor(max_size(a.rows()));
    size_block_col_b = (int) floor(max_size(b.cols()));
    cout << "block col a " << size_block_col_a << ", block col b  " << size_block_col_b << ", block row a "
         << size_block_row_a << endl;

    tsafe_queue<data4que> data_queue;

    mutex mux;
    //void main_pusher(const MatrixXd &a, const MatrixXd &b, int size_block_col_a, int size_block_row_a,
    //               int size_block_col_b, tsafe_queue<data4que> &data_queue) {

    thread main_thread = thread(main_pusher, a, b, size_block_col_a, size_block_row_a, size_block_col_b,
                                ref(data_queue));

    vector<thread> vects;
    for (int i = 0; i < num_threads - 1; i++) {
        // multiplication

        //small_matrix_mult(MatrixXd &c, tsafe_queue<data4que> &data_queue, mutex &mux) {

            vects.emplace_back(small_matrix_mult, ref(c), ref(data_queue), ref(mux));
    }


}


void matrix_mult(const MatrixXd &a, const MatrixXd &b, MatrixXd &c, const int &num_threads) {
    if (a.cols() != b.rows())
        return;


    int size_block_col_a, size_block_row_a, size_block_col_b;
    size_block_col_a = (int) floor(max_size(a.cols()));
    size_block_row_a = (int) floor(max_size(a.rows()));
    size_block_col_b = (int) floor(max_size(b.cols()));
    cout << "block col a " << size_block_col_a << ", block col b  " << size_block_col_b << ", block row a "
         << size_block_row_a << endl;

    tsafe_queue<data4que> data_queue;
    /*
     *
void main_pusher(const MatrixXd &a, const MatrixXd &b, int size_block_col_a, int size_block_row_a,
                 int size_block_col_b, tsafe_queue<data4que> &data_queue) {
     */

    vector<thread> vects;
    vects.emplace_back(main_pusher, a, b, size_block_col_a, size_block_row_a, size_block_col_b,
                                ref(data_queue));

    mutex mux;

    for (int i = 0; i < num_threads - 1; i++) {
        // multiplication
        vects.emplace_back(small_matrix_mult, ref(c), ref(data_queue), ref(mux));
    }

    for(int i = 0; i< num_threads; ++i){
        vects[i].join();
    }

}




int main(int argc, char *argv[]) {
    //MatrixXd m = randomSquareMatrix(5, 7);
    MatrixXd mat1(2, 2), mat2(2, 3);
    mat1 << 1, 0,
            0, 1;
    mat2 << 1, 2, 3,
            0, 3, 0;
    vector<int> data_mat1 = {0, 0, 2, 2}, data_mat2 = {0, 0, 2, 3};
    //small_matrix_mult(mat1, data_mat1, mat2, data_mat2, ref(res));

    MatrixXd a(100, 100), b(100, 90), res(100,90);
    a = randomSquareMatrix(100, 100);
    //cout << a.rows() << "x" << a.cols() << endl;
    b = randomSquareMatrix(100, 90);


    int num_threads = 5;

    if (argc == 2) {
        num_threads = atoi(argv[1]);
    }


    auto start_time = get_current_time_fenced();
    matrix_mult(a, b, ref(res), num_threads);

    auto finish_time = get_current_time_fenced();

    cout << "My result: " << res.block(1, 1, 1, 5) << endl;

    cout << "My Time :  " << to_us(finish_time - start_time) << endl;
    start_time = get_current_time_fenced();
    res = a * b;
    finish_time = get_current_time_fenced();
    cout << "Try result: " << res.block(1, 1, 1, 5) << endl;

    cout << "Eigen Time :  " << to_us(finish_time - start_time) << endl;
    return 0;
}
