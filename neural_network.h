#ifndef NN_NN_H
#define NN_NN_H

#include "layer.h"
#include <iostream>
#include <vector>


class NeuralNetwork {
private:
	std::vector<Layer*> layers;

public:
	void add(Layer* layer);
};

#endif //NN_NN_H


// class A2DD
// {
//   int gx;
//   int gy;

// public:
//   A2DD(int x,int y);
//   int getSum();

// };