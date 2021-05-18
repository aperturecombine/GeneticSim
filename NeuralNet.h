#pragma once
#include <vector>
#include <iostream>
#include "Matrix.h"

class NeuralNet {
public:
	NeuralNet(size_t _inputs, std::vector<size_t> hiddens, size_t outputs);

	Matrix forward(Matrix inputs);
	Matrix activate(Matrix inputs);
	Matrix dactivate(Matrix inputs);

	size_t inputSize;
	std::vector<size_t> hiddenSizes;
	size_t outputSize;

	std::vector<Matrix*> weights;
	std::vector<float*> biases;
};