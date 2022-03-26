#pragma once
#include <vector>
#include <ctime>
#include <fstream>
class Matrix {
public:
 Matrix(int n_,int max_value);
 Matrix(int n_);
 int GetSize() const;
 double GetElem(int i, int j) const;
 void SetElem(double elem, int i, int j);
 friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
private:
 std::vector<std::vector<double>> matrix;
 int n;
};

Matrix::Matrix(int n_):matrix(n_, std::vector<double>(n_)) {
 n = n_;
}
double Matrix::GetElem(int i, int j) const {
 return matrix[i][j];
}
void Matrix::SetElem(double elem, int i, int j) {
 matrix[i][j] = elem;
}
Matrix::Matrix(int n_,int max_value) {
 n = n_;
 srand(time(0));
 matrix.resize(n_);
 for (int i = 0; i < n_; ++i)
 {
	for (int j = 0; j < n_; ++j)
	{
	 matrix[i].push_back(rand()%max_value);
	}
 }
}

int Matrix::GetSize() const {
 return n;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix_) {
 for (int i = 0; i < matrix_.GetSize(); i++)
 {
	for (int j = 0; j < matrix_.GetSize(); j++)
	{
	 out << matrix_.GetElem(i,j) << " ";
	}
	out << std::endl;
 }
 return out;
}