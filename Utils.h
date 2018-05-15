#ifndef MPI_COURSEWORK_UTILS_H
#define MPI_COURSEWORK_UTILS_H

#include </usr/include/mpich/mpi.h>
#include <stdio.h>
#include <iostream>
#include <sys/resource.h>

using namespace std;

const unsigned int N = 10;
const unsigned int P = 9;
const unsigned int H = N / P;
const unsigned int count = 11;

struct Vector {
    int A[N];
public:
    void fillBy(int a) {
        for (int i = 0; i < N; i++) {
            A[i] = a;
        }
    }

    int &operator[](unsigned int i) {
        return A[i];
    }

    Vector copy() {
        Vector B;
        for (int i = 0; i < N; i++) {
            B[i] = A[i];
        }
        return B;
    }

    void print() {
        if (N < count) {
            for (int i = 0; i < N; i++) {
                cout << A[i] << " ";
            }
            cout << endl;
        }
    }

};

struct Matrix {
    Vector A[N];
public:

    Vector &operator[](unsigned int i) {
        return A[i];
    }

    Matrix copy() {
        Matrix MA;
        for (unsigned int i = 0; i < N; i++) {
            Vector V = A[i];
            for (unsigned int j = 0; j < N; j++) {
                MA[i][j] = V[j];
            }
        }
        return MA;
    }

    void fillBy(int a) {
        for (unsigned int i = 0; i < N; i++) {
            for (unsigned int j = 0; j < N; j++) {
                A[i][j] = a;
            }
        }
    }

    void print() {
        if (N < count) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << A[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
};

Matrix multMatrixMatrixValue(Matrix MS, Matrix MXi, int di, int Hi, int Hip1) {
    Matrix MRi;
    int t = 0;
    for (int i = Hi; i < Hip1; i++) {
        for (int j = 0; j < N; j++) {
            t = 0;
            for (int k = 0; k < N; k++) {
                t += MS[i][k] * MXi[k][j];
            }
            MRi[i][j] = t * di;
        }
    }
    return MRi;
}

Matrix multMatrixMatrix(Matrix MA, Matrix MB, int Hi, int Hip1) {
    Matrix MR;
    int t = 0;
    for (int i = Hi; i < Hip1; i++) {
        for (int j = 0; j < N; j++) {
            t = 0;
            for (int k = 0; k < N; k++) {
                t += MA[i][k] * MB[k][j];
            }
            MR[i][j] = t;
        }
    }
    return MR;
}

Vector fillVectorBy(int value) {
    Vector A;
    for (int i = 0; i < N; i++) {
        A[i] = value;
    }
    return A;
}

void printVector(Vector A) {
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

Matrix fillMatrixBy(int value) {
    Matrix MA;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            MA[i][j] = value;
        }
    }
    return MA;
}

void printMatrix(Matrix MA) {
    if (N > 9)
        return;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << MA[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Vector multVectorMatrix(Vector A, Matrix MA, int Hi, int Hip1) {
    Vector D;
    for (int i = Hi; i < Hip1; i++) {
        D[i] = 0;
        for (int j = 0; j < N; j++) {
            D[i] += A[i] * MA[j][i];
        }
    }
    return D;
}

Matrix multValueMatrix(int a, Matrix MA, int Hi, int Hip1) {
    for (int i = Hi; i < Hip1; i++) {
        for (int j = 0; j < N; j++) {
            MA[i][j] *= a;
        }
    }
    return MA;
}

Matrix addMatrixMatrix(Matrix MA, Matrix MB, int Hi, int Hip1) {
    for (int i = Hi; i < Hip1; i++) {
        for (int j = 0; j < N; j++) {
            MA[i][j] += MB[i][j];
        }
    }
    return MA;

}

int multVectorMatrixAndMin(Vector Ei, Matrix MM, int Hi, int Hip1, int mi) {
    Vector Ki;
    for (int i = Hi; i < Hip1; i++) {
        Ki[i] = 0;
        for (int j = 0; j < N; j++) {
            Ki[i] += Ei[i] * MM[j][i];
        }
        if (Ki[i] < mi) {
            mi = Ki[i];
        }
    }
    return mi;
}

#endif //MPI_COURSEWORK_UTILS_H
