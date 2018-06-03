#include "matrix_utils.h"

using std::vector;
using std::string;
using std::set;
using std::map;
using std::pair;


void _remove_row(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

void _remove_column(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
}

void _fill_zeros(vector<string> &v, int len){
    while (v.size() != len){
        v.push_back("0");
    }
}

void _encode(vector<string> &v, int idx, int len){
    v.clear();
    _fill_zeros(v, len);
    v[idx] = "1";
}

map<int, string > one_hot_encode(vector<vector<string>> &M, int idx){
	map<int, string > final_result;
    set <string> uniques;
    unsigned long M_width = M.size();
    
    for (int j = 0; j < M_width; ++j){
        uniques.insert(M[j][idx]);
    }

    unsigned long amount = uniques.size(); 
    int _k = 0;
    vector<string> hot_code;
    vector<vector<string> > hot_codes;

    map<string, int> m_uniques;
    for (auto const &elem : uniques){
        _encode(hot_code, _k, amount);
        hot_codes.push_back(hot_code);
		final_result[_k]=elem;
        m_uniques[elem]=_k;
        _k++;

    }


    for (int i=0; i < M.size(); ++i){
      string to_replace = M[i][idx];
      M[i].erase(M[i].begin() + idx);
      vector<string>::iterator it = M[i].begin();
      vector<string> to_put = hot_codes[m_uniques[to_replace]];
      M[i].insert (it+idx,to_put.begin(),to_put.end());
    }
	return final_result;
	
  }

void shuffle_vector(vector<vector<string>> &M){
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(M), std::end(M), rng);
}

pair <Eigen::MatrixXd, Eigen::MatrixXd> divide_matrix(const Eigen::MatrixXd  &M, double percentile){
	int rows = M.rows();
	int cols = M.cols();
	int idx = rows * percentile;
	Eigen::MatrixXd _first = M.block(0, 0, idx, cols);
	Eigen::MatrixXd _second = M.block(idx, 0, rows-idx, cols);
	pair <Eigen::MatrixXd, Eigen::MatrixXd> p(_first, _second);
	return p;
}

Eigen::MatrixXd csv2matrix(std::string file, char sep) {

	std::ifstream in(file);
	
	std::string line;

	int row = 0;
	int col = 0;

	
	int rows=0;
	std::ifstream fl(file);
	std::string ln;
	while (getline(fl, ln))
	    rows++;

    int cols=1;
    for (int i=0; i<ln.length(); ++i){
        if (ln[i] == sep){
            cols++;
        }
    }
	fl.close();
	Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);
	if (in.is_open()) {

		while (std::getline(in, line)) {

			char *ptr = (char *) line.c_str();
			int len = line.length();

			col = 0;

			char *start = ptr;
			for (int i = 0; i < len; i++) {
				if (ptr[i] == sep) {
				res(row, col++) = atof(start);
					start = ptr + i + 1;
				}
			}
			res(row, col) = atof(start);

			row++;
		}

		in.close();
	}
	return res;
}


vector<vector<string> > csv2vector(std::string file, char sep) {

	std::ifstream in(file);
	
	std::string line;

	int row = 0;
	int col = 0;

	
	vector<vector<string> >X;
	
	string tmp_str = "";
	
	if (in.is_open()) {

		while (std::getline(in, line)) {
			int len = line.length();

			col = 0;
			vector<string> tmp_vct;
			for (int i = 0; i < len; i++) {
				if (line[i] == sep) {
					tmp_vct.push_back(tmp_str);
					tmp_str = "";
					col++;
				} else{
					tmp_str += line[i];
				}
			}
			tmp_vct.push_back(tmp_str);
			tmp_str = "";
			X.push_back(std::move(tmp_vct));
			row++;
		}

		in.close();
	}
	return X;
}



Eigen::MatrixXd vector2matrix(vector<vector<string>> &M) {
	int rows = M.size();
	int cols = M[0].size();

	Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			res(i, j) = stof(M[i][j]);
		}
	}
	return res;
}


pair <Eigen::MatrixXd, Eigen::MatrixXd> split_X_y(Eigen::MatrixXd &A, std::vector<int> y_ind)
{
	Eigen::MatrixXd y = Eigen::MatrixXd(A.rows(), y_ind.size());
	for(int i = 0; i < y.cols(); i++){
		y.col(i) = A.col(y_ind[i]);
	}
	for(int i = 0; i < y.cols(); i++){
		_remove_column(A, y_ind[i]);
	}
	pair <Eigen::MatrixXd, Eigen::MatrixXd> p(A, y);
	return p;
}

Eigen::MatrixXd read_matrix(std::ifstream &from, int nrows, int ncols){
    Eigen::MatrixXd X = Eigen::MatrixXd::Zero(nrows,ncols);
    if (from.is_open())
    {
        for (int row = 0; row < nrows; row++)
            for (int col = 0; col < ncols; col++)
            {
                float item = 0.0;
                from >> item;
                X(row, col) = item;
            }
    }
    return X;
}


Eigen::MatrixXd read_matrix(std::ifstream &from){
    Eigen::MatrixXd X;
	if (from.is_open())
    {
		int nrows, ncols;
		from >> nrows >> ncols;
		X = Eigen::MatrixXd::Zero(nrows,ncols);
        for (int row = 0; row < nrows; row++)
            for (int col = 0; col < ncols; col++)
            {
                float item = 0.0;
                from >> item;
                X(row, col) = item;
            }
    }
    return X;
}


void save_matrix(std::ofstream &to, Eigen::MatrixXd &A, int with_header){
	Eigen::IOFormat CommaInitFmt(StreamPrecision, DontAlignCols, " ", "\n", "", "", "", "");
    if (to.is_open())
    {
		if (with_header){
			to << A.rows() << " " << A.cols() << std::endl;
		}
        to << A.format(CommaInitFmt);
    }
}
