#include "test_mnist.h"

using Eigen::MatrixXd;
using namespace std;

int main() {
	MatrixXd X(4, 2);
	MatrixXd y(4, 1);
	
	X<<1, 1, 0, 0, 0, 1, 1, 0;
	y<<0, 0, 1, 1;

	NeuralNetworkConfig config;
	config.epochs = 800;
	config.lr = 0.2;
	NeuralNetwork nn(config);
	nn.add(new DenseLayer(2, 6));
	nn.add(new ActivationLayer("relu"));
	nn.add(new DenseLayer(6, 1));
	nn.add(new ActivationLayer("sigmoid"));

	nn.fit(X, y);

	cout<<nn.accuracy_classification(X, y)<<endl;

	MatrixXd to_predict(1, 2);
	to_predict<<0, 0;
	cout<<nn.predict(to_predict)<<endl;

	nn.save_model("../resources/xor_model.txt");

	NeuralNetwork nn2;
	nn2.load_model("../resources/xor_model.txt");
	cout<<nn2.predict(to_predict)<<endl;


}