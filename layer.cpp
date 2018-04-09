#include "layer.h"

class Layer {
public:
	virtual void backward(MatrixXd X) = 0;
	virtual void forward() = 0;
};