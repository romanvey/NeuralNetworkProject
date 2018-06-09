#include "neural_network_config.h"

void NeuralNetworkConfig::save_conf(std::ofstream &to){
    if (to.is_open()){
        to << verbose << std::endl;
        to << epochs << std::endl;
        to << lr << std::endl;
        to << inertia << std::endl;
        to << threads << std::endl;
    }
}

void NeuralNetworkConfig::load_conf(std::ifstream &from){
    if (from.is_open()){
        from >> this->verbose;
        from >> this->epochs;
        from >> this->lr;
        from >> this->inertia;
        from >> this->threads;
    }
}