#include <cstring>
#include <vector>
#include </usr/include/mpich/mpi.h>
#include <stdio.h>
#include <iostream>
#include <sys/resource.h>
#include <cstdlib>

using namespace std;

const unsigned int N = 20000;
const unsigned int P = 4;
const unsigned int H = N / P;

/**
 * Course Work _ 2
 * Author : Uliana Stefanishyna
 * Group : IO-52
 * Task : MA = MB * min(E * MM) + MO * (MS * MX) * d
 */
const static int COUNT = 10;

void fillMatrix(int MA[N][N], int value);

void fillVector(int A[N], int value);

void printMatrix(int MA[N][N], int begin, int end);

int main(int argc, char **argv) {

    int MS[N][N], MM[N][N], MB[N][N], MO[N][N], MX[N][N];
    int E[N];
    int d;

    int size, rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);    // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double half = (double) size / 2.0;

//    int a = 5;
//    if (((rank + 1) < (int) half) || (((rank + 1) == (int) half) && ((int) half != half))) {
    if (rank < (P / 2)) {
        if (rank == 0) {
//        cout << "process #" << rank << endl;

            fillMatrix(MS, 1);
            fillMatrix(MM, 1);
            fillVector(E, 1);
            d = 1;

            for (int i = N / 2; i < N; i++) {
                MPI_Send(&MS[i], N / 2, MPI_INT, (size - 1), (size - 1), MPI_COMM_WORLD);
                MPI_Send(&MM[i], N / 2, MPI_INT, (size - 1), (size - 1), MPI_COMM_WORLD);
            }
            MPI_Send(E, N, MPI_INT, (size - 1), (size - 1), MPI_COMM_WORLD);
            MPI_Send(&d, 1, MPI_INT, (size - 1), (size - 1), MPI_COMM_WORLD);

            for (int i = (rank + 1) * H; i < N; i++) {
                MPI_Send(&MS[i], N - (rank + 1) * H, MPI_INT, rank + 1, (rank + 1), MPI_COMM_WORLD);
                MPI_Send(&MM[i], N - (rank + 1) * H, MPI_INT, rank + 1, (rank + 1), MPI_COMM_WORLD);
            }
            MPI_Send(&E, N, MPI_INT, rank + 1, (rank + 1), MPI_COMM_WORLD);
            MPI_Send(&d, 1, MPI_INT, (size - 1), (size - 1), MPI_COMM_WORLD);

//        cout << "finished process #" << rank << endl;
        }
    } else if (rank > P / 2) {
        if (rank == (size - 1)) {
//        cout << "process #" << rank << endl;

            fillMatrix(MB, 1);
            fillMatrix(MO, 1);
            fillMatrix(MX, 1);

            for (int i = N / 2; i < N; i++) {
                MPI_Recv(&MS[i], N / 2, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
                MPI_Recv(&MM[i], N / 2, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
            }
            MPI_Recv(E, N, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
            MPI_Recv(&d, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);

//        cout << "H = " << H << "  N = " << N << endl;

//        printMatrix(MS, 0, N);
//        cout << "finished process #" << rank << endl;
        } else {
//        cout << "process #" << rank << endl;

            for (int i = rank * H; i < N; i++) {
                MPI_Recv(&MS[i], N - (rank) * H, MPI_INT, (rank - 1), (rank), MPI_COMM_WORLD, &status);
            }
//        printMatrix(MS, rank * H, N);
            for (int i = (rank + 1) * H; i < N; i++) {
                MPI_Send(&MS[i], N - (rank + 1) * H, MPI_INT, rank + 1, (rank + 1), MPI_COMM_WORLD);
            }
//        cout << "finished process #" << rank << endl;

        }
    }
    MPI_Finalize();
}

void fillMatrix(int MA[N][N], int value) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            MA[i][j] = value;
        }
    }
}

void fillVector(int A[N], int value) {
    for (int i = 0; i < N; i++) {
        A[i] = value;
    }
}

void printMatrix(int MA[N][N], int begin, int end) {
    if (N <= COUNT) {
        for (int i = begin; i < end; i++) {
            for (int j = 0; j < N; j++) {
                cout << MA[i][j] << " ";
            }
            cout << endl;
        }
    }
}

