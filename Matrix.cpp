#include "Matrix.h"

Matrix::Matrix(size_t _rows, size_t _cols, std::vector<std::vector<float>> vals) {
	rows = _rows;
	cols = _cols;

	mat.resize(rows);
	for (int i = 0; i < rows; i++) {
		mat[i].resize(cols);
		for (int j = 0; j < cols; j++)
			mat[i][j] = vals[i][j];
	}
}

Matrix::Matrix(std::vector<std::vector<float>> vals) {
	rows = vals.size();
	cols = vals[0].size();

	mat.resize(rows);
	for (int i = 0; i < rows; i++) {
		mat[i].resize(cols);
		for (int j = 0; j < cols; j++)
			mat[i][j] = vals[i][j];
	}
}

Matrix::Matrix(size_t _rows, size_t _cols, bool random) {
	rows = _rows;
	cols = _cols;

	mat.resize(_rows);
	for (int i = 0; i < mat.size(); i++)
		mat[i].resize(_cols, 0);

	if (random) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				mat[i][j] = getRandom();
	}
}

float& Matrix::operator()(const size_t& row, const size_t& col) {
	return this->mat[row][col];
}

const float& Matrix::operator()(const size_t& row, const size_t& col) const {
	return this->mat[row][col];
}

Matrix Matrix::operator*(const Matrix& rhs) {
	Matrix newMat(rows, rhs.cols);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rhs.cols; j++) {
			for (size_t k = 0; k < rhs.rows; k++) {
				newMat(i, j) += this->mat[i][k] * rhs(k, j);
			}
		}
	}
	return newMat;
}

Matrix Matrix::transpose() {
	Matrix newMat(cols, rows);

	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			newMat(i, j) = mat[j][i];

	return newMat;
}

std::ostream& operator<< (std::ostream& stream, Matrix& mat) {
	for (int i = 0; i < mat.getRows(); i++) {
		for (int j = 0; j < mat.getCols(); j++) {
			stream << mat(i, j);
			if (j < mat.getCols() - 1) stream << ",\t";
		}
		stream << std::endl;
	}
	return stream;
}