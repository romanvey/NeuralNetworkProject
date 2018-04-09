#ifndef NN_ACTIVATION_H
#define NN_ACTIVATION_H

#include <Eigen/Dense>

class Activation {
        private:
        Matrix2d _sigmoid(Matrix2d X);
        Matrix2d _derivative_sigmoid(Matrix2d X);
        public:
        Matrix2d backward(Matrix2d chain_error);
        Matrix2d forward(Matrix2d X, double lr);
};

#endif //NN_ACTIVATION_H