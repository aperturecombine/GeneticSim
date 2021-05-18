#include "NeuralNet.h"

NeuralNet::NeuralNet(size_t _inputs, std::vector<size_t> hiddens, size_t _outputs) {
	inputSize = _inputs;
	outputSize = _outputs;

	auto numHiddenLayers = hiddens.size();

	weights.resize(numHiddenLayers + 1);
	weights[0] = new Matrix(inputSize, hiddens[0], true);

	size_t prev = hiddens[0];
	for (int i = 1; i<numHiddenLayers; i++) {
		weights[i] = new Matrix(prev, hiddens[i], true);
		prev = hiddens[i];
	}

	weights[weights.size()-1] = new Matrix(prev, outputSize, true);

	/*for (Matrix *m : weights) {
		std::cout << *m << std::endl;
	}*/
}

Matrix NeuralNet::forward(Matrix inputs) {
	Matrix output;

	//std::cout << inputs.getRows() << " " << inputs.getCols() << std::endl;
	//std::cout << inputs << std::endl << std::endl;
	for (Matrix* m : weights) {
		/*std::cout << inputs.getRows() << "x" << inputs.getCols() <<
			" " << (*m).getRows() << "x" << (*m).getCols() << std::endl;*/
		output = inputs * (*m);
		//std::cout << output.getRows() << " " << output.getCols() << std::endl;
		output = activate(output);
		//std::cout << output << std::endl << std::endl;
		inputs = output;
	}

	return output;
}

Matrix NeuralNet::activate(Matrix inputs) {
	Matrix newMat(inputs.getRows(), inputs.getCols());
	for (int c = 0; c < inputs.getCols(); c++) {
		std::cout << inputs(0, c) << "\t-> " << tanh(inputs(0, c)) << std::endl;
		newMat(0, c) = tanh(inputs(0, c));
	}
	std::cout << std::endl;
	return newMat;
}

Matrix NeuralNet::dactivate(Matrix inputs) {
	Matrix newMat(inputs.getRows(), inputs.getCols());
	for (int c = 0; c < inputs.getCols(); c++) {
		newMat(0, c) = 1 - pow(tanh(inputs(0, c)), 2);
	}
	return newMat;
}