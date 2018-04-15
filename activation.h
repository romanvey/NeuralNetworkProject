#ifndef NN_ACTIVATION_H
#define NN_ACTIVATION_H

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Activation {
public:

    MatrixXd _sigmoid(MatrixXd X); // TODO temporary public

    MatrixXd _derivative_sigmoid(MatrixXd X); // TODO temporary public

    MatrixXd backward(MatrixXd chain_error);

    MatrixXd forward(MatrixXd X, double lr);
};

#endif //NN_ACTIVATION_H