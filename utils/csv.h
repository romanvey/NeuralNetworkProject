#ifndef NN_CSV_H
#define NN_CSV_H

#include <Eigen/Dense>
#include <vector>
#include <fstream>
#include <iostream>

using namespace Eigen;

template<typename M>
M load_csv (const std::string & path);

#endif //NN_CSV_H