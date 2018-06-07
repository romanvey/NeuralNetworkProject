#include <iostream>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    /*
    int commsize, rank, len;
    char procname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);

    vector<float> vec;
    unsigned long N = 3;
    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            vec.push_back(i * i * 2); // 0, 2, 8
        }
        MPI::COMM_WORLD.Send (&vec[0], N, MPI::FLOAT, 0, 0);
    } else {
        vec.resize (N);
        MPI::COMM_WORLD.Recv (&vec[0], N, MPI::FLOAT, 1, 0);
        cout << "KEK" << endl;
        for (int i = 0; i < N; ++i) {
            float* arr = vec.data();
            cout << arr[i] << endl;
        }
    }*/
    int N = 10;
    vector<float> vec;
    float x;
    cout << "true values: \n";
    for (int j = 0; j < N; ++j) {
        x = (j * j) / 97. * 100;
        cout << x << endl;
        vec.push_back(x);
    }
    cout << "vec values: \n";
    for (int i = 0; i < N; ++i) {
        float* arr = vec.data();
        cout << arr[i] << endl;
    }
}