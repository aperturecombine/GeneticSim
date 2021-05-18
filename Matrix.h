#pragma once
#include <vector>
#include <iostream>
#include "math.h"

class Matrix {
public:
	Matrix() {}
	Matrix(std::vector<std::vector<float>> vals);
	Matrix(size_t _rows, size_t _cols, std::vector<std::vector<float>> vals);
	Matrix(size_t _rows, size_t _cols, bool random=false);

	float& operator() (const size_t& row, const size_t& col);
	const float& operator() (const size_t& row, const size_t& col) const;
	
	Matrix operator*(const Matrix& rhs);
	Matrix transpose();

	size_t getRows() { return rows; }
	size_t getCols() { return cols; }

	friend std::ostream& operator<< (std::ostream& os, Matrix& matrix);

private:
	size_t rows;
	size_t cols;

	std::vector<std::vector<float>> mat;
};