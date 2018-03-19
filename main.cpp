#include<iostream>
#include <fstream>

using namespace std;

class Matrix {
private:
    int K;
    int M;
    int **square;
public:
/**
 * Without parameters create matrix 3 x 3
 */
    Matrix() : K(3), M(3) {
        square = new int *[K];
        for (int i = 0; i < K; i++) {
            square[i] = new int[M];
        }
    }
/**
 * With parameters create matrix K x M
 * @param k high
 * @param m width
 */
    Matrix(int k, int m) : K(k), M(m) {
        square = new int *[K];
        for (int i = 0; i < K; i++) {
            square[i] = new int[M];
        }
    }
/**
 * clear memory
 */
    ~Matrix() {
        for (int i = 0; i < K; i++) {
            delete[] square[i];
        }
        delete[] square;
        square = nullptr;
    }
/**
 * read matrix from file (matrix with the right size should be created before reading)
 */
    void read() {
        ifstream Fin("Matrix_to_read.txt");

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < M; j++) {
                Fin >> square[i][j];
            }
        }
        Fin.close();
    }
/**
 * set needed value to the specific element of matrix
 */
    void set(int value, int high, int width) {
        square[high][width] = value;
    }

    int get(int h, int w) {

        return square[h][w];
    }
/**
 * transpose matrix
 */
    void transpose() {
        int tmp = 0;

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < M; j++) {
                tmp = square[i][j];
                square[i][j] = square[j][i];
                square[j][i] = tmp;
            }
        }
    }
/**
 * clear memory
 */
    void clear() {
        for (int i = 0; i < K; i++) {
            delete[] square[i];
        }
        delete[] square;
        square = nullptr;
    }
/**
 * operator overloading
 */
    Matrix &operator=(const Matrix &right) {
        if (this == &right) {
            return *this;
        }
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < M; j++) {
                square[i][j] = right.square[i][j];
            }
        }
        return *this;
    }

    friend const Matrix operator+(const Matrix &left, const Matrix &right);

    friend const Matrix operator-(const Matrix &left, const Matrix &right);

    friend const Matrix operator*(const Matrix &left, const Matrix &right);

    friend Matrix &operator+=(Matrix &left, const Matrix &right);

    friend Matrix &operator-=(Matrix &left, const Matrix &right);

    friend Matrix &operator*=(Matrix &left, const Matrix &right);

    friend Matrix &operator>>(Matrix &left, int quantity);

    friend Matrix &operator<<(Matrix &left, int quantity);

};

const Matrix operator+(const Matrix &left, const Matrix &right) {

    Matrix Answer(right.K, right.M);

    for (int i = 0; i < right.K; i++) {
        for (int j = 0; j < right.M; j++) {
            Answer.square[i][j] = left.square[i][j] + right.square[i][j];
        }
    }

    return Answer;
}

const Matrix operator-(const Matrix &left, const Matrix &right) {

    Matrix Answer(right.K, right.M);

    for (int i = 0; i < right.K; i++) {
        for (int j = 0; j < right.M; j++) {
            Answer.square[i][j] = left.square[i][j] - right.square[i][j];
        }
    }

    return Answer;
}

const Matrix operator*(const Matrix &left, const Matrix &right) {

    Matrix Answer(left.K, right.M);

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < right.M; j++) {
            Answer.square[i][j] = 0;
            for (int k = 0; k < left.M; k++) {
                Answer.square[i][j] += left.square[i][k] * right.square[k][j];
            }
        }
    }

    return Answer;
}

Matrix &operator+=(Matrix &left, const Matrix &right) {

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < left.M; j++) {
            left.square[i][j] += right.square[i][j];
        }
    }

    return left;
}

Matrix &operator-=(Matrix &left, const Matrix &right) {

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < left.M; j++) {
            left.square[i][j] -= right.square[i][j];
        }
    }

    return left;
}

Matrix &operator*=(Matrix &left, const Matrix &right) {

    Matrix Answer(left.K, right.M);

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < right.M; j++) {
            Answer.square[i][j] = 0;
            for (int k = 0; k < left.M; k++) {
                Answer.square[i][j] += left.square[i][k] * right.square[k][j];
            }
        }
    }

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < right.M; j++) {
            left.square[i][j] = Answer.square[i][j];
        }
    }

    for (int i = 0; i < left.K; i++) {
        for (int j = left.M; j > right.M; j--) {
            delete &left.square[i][j];
            left.M--;
        }
    }

    return left;
}

Matrix &operator>>(Matrix &left, int quantity) {

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < left.M; j++) {
            left.square[i][j] >>= quantity;
        }
    }

    return left;
}

Matrix &operator<<(Matrix &left, int quantity) {

    for (int i = 0; i < left.K; i++) {
        for (int j = 0; j < left.M; j++) {
            left.square[i][j] <<= quantity;
        }
    }

    return left;
}

int main() {

    Matrix obj1(2, 3);
    Matrix obj2(3, 2);
    Matrix obj3;

    obj1.read();
    obj2.read();

    obj1 *= obj2;

    int k = obj1.get(0, 0);

    cout << k << endl;

    return 0;
}