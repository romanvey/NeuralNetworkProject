#include "test_utils.h"

using namespace std;


// int main(){
// 	vector< vector<string> > A = csv2vector("../resources/iris_old.csv", ',');

// 	// for(int i = 0; i < 100; i++){
// 	// 	for(int j = 0; j < A[0].size(); j++){
// 	// 		std::cout<<A[i][j]<<" "; 
// 	// 	}
// 	// 	std::cout<<std::endl;
// 	// }
// 	map<int, string > Y_labels = one_hot_encode(A, 4);
// 	// label : class 

	
// 	shuffle_vector(A);	
// 	Eigen::MatrixXd m = vector2matrix(A);


// 	pair<Eigen::MatrixXd, Eigen::MatrixXd> p;
// 	vector<int> y_ind(3);
// 	y_ind[0] = 4; y_ind[1] = 5; y_ind[2] = 6;

// 	p =  split_X_Y(m, y_ind);
// 	cout<<"Train:"<<endl;
// 	cout<<p.first<<endl;
// 	cout<<"Test:"<<endl;
// 	cout<<p.second<<endl;
// 	// pair<Eigen::MatrixXd, Eigen::MatrixXd> p;
// 	// p = divide_matrix(m, 0.1);
// }
