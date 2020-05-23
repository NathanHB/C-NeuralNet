#ifndef NETWORK_H
#define NETWORK_H
#include "matrix.hpp"
#include <vector>
#include <tuple>

class Network {
	std::vector<Matrix> weights, biases;

	// number of layer without counting the input layer
	unsigned number_of_layers{};

	void update_mini_batch(std::vector<std::tuple<Matrix, Matrix>> &, double, unsigned, unsigned);

	std::tuple<std::vector<Matrix>, std::vector<Matrix>> backprop(Matrix&, Matrix&);

	Matrix cost_derivative(Matrix&, Matrix&);

public:

	// constructor for the network first agrument is number of layer input
	// included, second is the size of each respective layers from input to
	// ouptut
	Network(unsigned number_of_layer, std::vector<unsigned> layer_sizes);

	// feed the input into the net and return the matrix of output
	Matrix feed_forward(Matrix inputs);

	// train the net with the inputs and outputs given in parameters
	// the number of iterations (epoch) to train for and the batchsize for the
	// stochastic gradient descend

	void train_net(std::vector<std::tuple<Matrix, Matrix>> &training,
				   unsigned epoch,
				   unsigned batch_size,
				   double learning_rate,
				   std::vector<std::tuple<Matrix, Matrix>> &testing);

	unsigned test_mnist_net(std::vector<std::tuple<Matrix, Matrix>> &testing_data);
	unsigned test_xor_net(std::vector<std::tuple<Matrix, Matrix>> &testing_data);


	void print();
};

#endif
