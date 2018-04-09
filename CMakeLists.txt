cmake_minimum_required (VERSION 3.0)
project (NeuralNetworkProject)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable (NeuralNetwork neural_network.h dense.h layer.h activation.h neural_network.cpp dense.cpp activation.cpp)
target_link_libraries (NeuralNetwork Eigen3::Eigen)



# For test
add_executable (test test.h neural_network.h dense.h layer.h activation.h test.cpp neural_network.cpp dense.cpp activation.cpp)
target_link_libraries (test Eigen3::Eigen)
