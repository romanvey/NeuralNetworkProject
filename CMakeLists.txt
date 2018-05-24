cmake_minimum_required (VERSION 3.0)
project (NeuralNetworkProject)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(CMAKE_CXX_STANDARD 14)

file(GLOB src_files
    "src/*.h"
    "src/*.cpp"
)

# Example of usage of our library
add_executable(test_nn ${src_files})
#add_executable(read_csv "src/csv.cpp")
# add_executable (test_nn test.h neural_network.h neural_network_config.h dense.h layer.h activation.h test.cpp neural_network.cpp dense.cpp activation.cpp)

target_link_libraries (test_nn Eigen3::Eigen)
#target_link_libraries (read_csv Eigen3::Eigen)
