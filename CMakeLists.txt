cmake_minimum_required (VERSION 3.0)
project (NeuralNetworkProject)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable (NeuralNetwork neural_network.cpp dense.cpp layer.cpp activation.cpp)
target_link_libraries (NeuralNetwork Eigen3::Eigen)
