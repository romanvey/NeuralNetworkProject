#include "threads_utils.h"

void _mult(const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2, Eigen::MatrixXd &res, mutex &mux){
    Eigen::MatrixXd t = m1 * m2;
    mux.lock();
    res = t;
    mux.unlock();
}

Eigen::MatrixXd mult_with_threads(const int n, const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2) {
    long m1_height = m1.rows();
    long m1_width = m1.cols();
    thread threads[n];
    vector<Eigen::MatrixXd> results((unsigned long) n);
    vector<Eigen::MatrixXd> blocks((unsigned long) n);

    // multuply
    mutex mux;
    for (int i = 0; i < n - 1; ++i) {
        int from = (m1_height / n) * i;
        int to = (m1_height / n) * (i + 1) - from;
        blocks[i] = m1.block(from, 0, to, m1_width);
        threads[i] = thread(_mult, ref(blocks[i]), ref(m2), ref(results[i]), ref(mux));
    }

    // and the last one
    int from = (m1_height / n) * (n - 1);
    int to = m1_height - from;
    blocks[n - 1] = m1.block(from, 0, to, m1_width);
    threads[n - 1] = thread(_mult, ref(blocks[n - 1]), ref(m2), ref(results[(n - 1)]), ref(mux));

    for (int i = 0; i < n; ++i) {
        threads[i].join();
    }

    // merge blocks
    Eigen::MatrixXd res(m1.rows(), m2.cols());
    int block_h = results[0].rows();
    for (int j = 0; j < n; ++j) {
        res.block(j*block_h, 0, results[j].rows(), results[j].cols()) << results[j];
    }
    return res;
}
