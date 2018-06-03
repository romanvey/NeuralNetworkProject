#ifndef NN_CSV_H
#define NN_CSV_H

#include <Eigen/Dense>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include <utility>

using namespace Eigen;

Eigen::MatrixXd csv2matrix(std::string file, char sep);
std::vector<std::vector<std::string> > csv2vector(std::string file, char sep);
Eigen::MatrixXd vector2matrix(std::vector<std::vector<std::string>> &M) ;
std::map<int, std::string > one_hot_encode(std::vector<std::vector<std::string>> &M, int idx);
void shuffle_vector(std::vector<std::vector<std::string>> &M);
std::pair <Eigen::MatrixXd, Eigen::MatrixXd> split_X_y(Eigen::MatrixXd &A, std::vector<int> y_ind);
std::pair <Eigen::MatrixXd, Eigen::MatrixXd> divide_matrix(const Eigen::MatrixXd  &M, double percentile);
Eigen::MatrixXd read_matrix(std::ifstream &from, int nrows, int ncols);
Eigen::MatrixXd read_matrix(std::ifstream &from);
void save_matrix(std::ofstream &to, Eigen::MatrixXd &A, bool with_header);

#endif //NN_CSV_H