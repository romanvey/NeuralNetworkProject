#ifndef NN_NN_CONFIG_H
#define NN_NN_CONFIG_H

#include <fstream>
#include <iostream>

class NeuralNetworkConfig
{
    public:
		bool verbose = false;
		int epochs = 10000;
        double lr = 0.1;
		double inertia = 1; // w = inertia * (changed_w) + (1 - inertia) * (prev_w)
		int threads = 0;
		void save_conf(std::ofstream &to);
		void load_conf(std::ifstream &from);
};


#endif //NN_NN_CONFIG_H