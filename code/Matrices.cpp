#include "Matrices.h"

namespace Matrices
{
Matrix::Matrix(int _rows,int _cols){
    rows = _rows;
    cols = _cols;
    a.resize(_rows);
    for(int i = 0; i < rows; i++){
        a[i].resize(_cols);
    }
}
Matrix operator+(const Matrix& a, const Matrix& b){
    if(a.getCols() == b.getCols() && a.getRows() == b.getRows()){
        Matrix c = Matrix(a.getRows(), b.getCols());
        for (int i = 0; i < a.getRows(); i++){
            for (int j = 0; j < a.getCols(); j++){
                c(i,j) = a(i,j) + b(i,j);
            }
        }
        return c;
    }
    else {
        throw runtime_error("Error: dimensions must agree");
    }
}
///A(i,j) * B(j,k) = C(i,k)

/* check that A columns = B rows
 for i in A:
 for k in B:
 c(i,k) = 0;
 for j in (A's columns or B's rows)
 c(i,k) += a(i,j) * b(j,k);
 */
Matrix operator*(const Matrix& a, const Matrix& b){
    if( a.getCols() != b.getRows()){
        throw runtime_error(" * Error: dimensions must agree");
    }
    else{
        Matrix c = Matrix(a.getRows(), b.getCols());
        for(int k = 0; k < b.getCols(); k++){
            for(int i = 0; i < a.getRows(); i++){
                double sum = 0;
                for(int j = 0; j < b.getRows(); j++){
                    sum += a(i,j) * b(j,k);
                }
                c(i,k) = sum;
                sum = 0;
            }
        }
        return c;
    }
}

bool operator==(const Matrix& a, const Matrix& b){
    bool flag = false;
    if(a.getCols() != b.getCols() && a.getRows() != b.getRows()){
        return flag;
    }
    else{
        for (int i = 0; i < a.getRows(); i++){
            for (int j = 0; j < a.getCols(); j++){
                if(abs(a(i,j) - b(i,j)) < 0.001) flag = true;
                else{
                    flag = false;
                    return flag;
                }
            }
        }
        return flag;
    }
}
bool operator!=(const Matrix& a, const Matrix& b){
    bool flag = true;
    if(a.getCols() != b.getCols() && a.getRows() != b.getRows()){
        return flag;
    }
    else{
        for (int i = 0; i < a.getRows(); i++){
            for (int j = 0; j < a.getCols(); j++){
                if(abs(a(i,j) - b(i,j)) < 0.001) flag = false;
                else{
                    flag = true;
                    return flag;
                }
            }
        }
        return flag;
    }
}
ostream& operator<<(ostream& os, const Matrix& a){
    for(int i = 0; i < a.getRows(); i++){
        os << setw(10) << endl;
        for(int j = 0; j < a.getCols(); j++){
            os << setw(10) << a(i,j) << " ";
        }
    }
    os << endl;
    return os;
}
///Call the parent constructor to create a 2x2 matrix
///Then assign each element as follows:
/*
cos(theta)  -sin(theta)
sin(theta)   cos(theta)
*/
///theta represents the angle of rotation in radians, counter-clockwise
RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2){
    this->operator()(0, 0) = cos(theta);
    this->operator()(0, 1) = -sin(theta);
    this->operator()(1, 0) = sin(theta);
    this->operator()(1, 1) = cos(theta);
}
///Call the parent constructor to create a 2x2 matrix
///Then assign each element as follows:
/*
scale   0
0       scale
*/
///scale represents the size multiplier
ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2){
    this->operator()(0, 0) = scale;
    this->operator()(1, 1) = scale;
    this->operator()(0, 1) = 0;
    this->operator()(1, 0) = 0;
}
///2D Translation matrix
///usage:  A = T + A will shift all coordinates of A by (xShift, yShift)
TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2,nCols){
    for(int i = 0; i < nCols; i++){
        this->operator()(0, i) = xShift;
        this->operator()(1, i) = yShift;
    }
}
}
