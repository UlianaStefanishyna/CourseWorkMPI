#include <cstring>
#include "Utils.h"

//const int N = 100;
//const int P = 5;
//const int H = N / P;

/**
 * Course Work _ 2
 * Author : Uliana Stefanishyna
 * Group : IO-52
 * Task : MA = MB * min(E * MM) + MO * (MS * MX) * d
 */

int main(int argc, char **argv) {
memcpy()
//    const rlim_t kStackSize = 256 * 1024 * 1024;   // min stack size = 256 MB
//    struct rlimit rl;
//    int result;
//    result = getrlimit(RLIMIT_STACK, &rl);
//    if (result == 0) {
//        if (rl.rlim_cur < kStackSize) {
//            rl.rlim_cur = kStackSize;
//            result = setrlimit(RLIMIT_STACK, &rl);
//            if (result != 0) {
//                fprintf(s btderr, "setrlimit returned result = %d\n", result);
//            }
//        }
//    }
//    cout << "result = " << result << endl;
    int name_len, size, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    double x[10];

    MPI_Status status;
    MPI_Init(NULL, NULL);    // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double half = (double) size / 2.0;
    int a = 5;
    Matrix MB, MO, MX;
    Matrix MM;
    Vector E;
    int d;
    int MS[N][N];
    int *data = (int *) malloc(N * N * sizeof(int));
    int **array = (int **) malloc(N * sizeof(int *));

    if (((rank + 1) < (int) half) || (((rank + 1) == (int) half) && ((int) half != half))) {

        if (rank == 0) {
            cout << "process #" << rank << endl;
//            MS.fillBy(1);
            MM.fillBy(1);
//            E.fillBy(1);
//            d = 1;
//            MS.print();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    MS[i][j] = 1;
                }
                cout << *MS[i] << " ";
            }
//            for (int i = 0; i < N; i++) {


            for (int i = 0; i < N; i++)
                array[i] = &(data[N * i]);

            MPI_Send(&(array[0][0]), N * N, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
//            }

            for (int i = 0; i < 9; i++) {
                x[i] = 0.1 * i;
            }
//            printf("Hello world from rank %d, out of %d processors\n", rank, size);

        } else {
//            MPI_Recv(x, 9, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
//            printf("Hello world from rank %d, out of %d processors\n", rank, size);
//            MPI_Send((x + rank + 1), 9 - rank, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
//            if (rank == 3) {
//                for (int i = 0; i < 9; i++)
//                    cout << x[i] << " ";
//                cout << endl;
//                cout << endl;
//            }
        }


    } else if ((rank - 2) > (int) half) {

        if (rank == size - 1) {
            cout << "process #" << rank << endl;
            MPI_Recv(&(array[0][0]), N * N, MPI_INT, 0, 666, MPI_COMM_WORLD, &status);
        } else {

        }

    }

//    if (rank == 0) {
//        for (int i = 0; i < 10; i++)
//            x[i] = 0.1 * i;
//        MPI_Send(x, 5, MPI_DOUBLE, 1, 666, MPI_COMM_WORLD);
//    } else if (rank == 1) {
//        MPI_Recv(x, 5, MPI_DOUBLE, 0, 666, MPI_COMM_WORLD, &status);
//    }
//
//    if (rank == 0) {
//
//        for (int i = 0; i < 10; i++)
//            cout << x[i] << " ";
//        cout << endl;
//        cout << endl;
//    } else {
//        for (int i = 0; i < 10; i++)
//            cout << x[i] << " ";
//        cout << endl;
//        cout << endl;
//    }
//
////    MPI_Get_processor_name(processor_name, &name_len);
////
////    printf("Hello world from processor %s, rank %d"
////           " out of %d processors\n",
////           processor_name, rank, size);
//
    MPI_Finalize();

}
