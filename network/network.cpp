#include "network.hpp"
#include "matrix.hpp"
#include <cstdio>
#include <random>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cmath>

static double sigmoid(double k)
{
	return (1 / (1 + exp(-k)));
}

static double sigmoid_prime(double k)
{
	return sigmoid(k) * (1 - sigmoid(k));
}

void Network::print()
{
	std::printf(" ---- BIASES -----\n");
	for (auto &b : biases) {
		b.print();
	}

	std::printf("\n");
	std::printf(" ----- WEIGHTS -----\n");
	for (auto &w : weights) {
		w.print();
	}
}

Network::Network(unsigned number_of_layers, std::vector<unsigned> layer_sizes)
{
	this->number_of_layers = number_of_layers - 1;

	for (unsigned i = 0; i < number_of_layers - 1; ++i) {
		Matrix b {layer_sizes[i + 1], 1};
		b.random_fill();
		biases.push_back(b);

		Matrix w {layer_sizes[i + 1], layer_sizes[i]};
		w.random_fill();
		weights.push_back(w);
	}
}

Matrix Network::feed_forward(Matrix inputs)
{
	for (unsigned i = 0; i < (number_of_layers); ++i) {
		inputs = (weights[i] * inputs) + biases[i];
		inputs.apply(sigmoid);
	}

	return inputs;
}

Matrix Network::cost_derivative(Matrix &a, Matrix &b)
{
	//(a - b).print();
	return (a - b);
}

std::tuple<std::vector<Matrix>, std::vector<Matrix>> Network::backprop(Matrix& x, Matrix& y)
{
	std::vector<Matrix> nabla_w(number_of_layers);
	std::vector<Matrix> nabla_b(number_of_layers);

	Matrix activation = x;
	std::vector<Matrix> activations{};
	activations.push_back(x);

	std::vector<Matrix> zs{};


	for (unsigned i = 0; i < number_of_layers; ++i) {
		Matrix z = (weights[i] * activation) + biases[i];
		zs.push_back(z);
		activation = z.apply(sigmoid);
		activations.push_back(activation);
	}

	Matrix delta {cost_derivative(activations[activations.size() - 1], y)};
	delta %= zs[zs.size() - 1].apply(sigmoid_prime);

	nabla_b[nabla_b.size() - 1] = delta;
	nabla_w[nabla_w.size() - 1] = delta * activations[activations.size() - 2].t();


	for (unsigned i = 2; i <= number_of_layers; ++i) {
		Matrix z = zs[zs.size() - i];
		Matrix sp = z.apply(sigmoid_prime);
		delta = (weights[weights.size() - i + 1].t() * delta) % sp;
		nabla_b[nabla_b.size() - i] = delta;
		nabla_w[nabla_b.size() - i] = delta * activations[activations.size() - i - 1].t();
	}

	return std::make_tuple(nabla_w, nabla_b);
}


void Network::update_mini_batch(std::vector<std::tuple<Matrix, Matrix>> &batch,
								double learning_rate,
								unsigned from,
								unsigned to)
// update the the network for the element in training from "from" to "to".
{
	std::vector<Matrix> nabla_w (number_of_layers);
	std::vector<Matrix> nabla_b (number_of_layers);

	for (unsigned i = 0; i < number_of_layers; ++i) {
		nabla_w[i] = Matrix(weights[i].get_rows(), weights[i].get_cols());
		nabla_b[i] = Matrix(biases[i].get_rows(), biases[i].get_cols());
	}

	for (unsigned i = from; i < to; ++i) {
		// delta nabal is a tuple of matrices representing the amount by wich
		// we must change the weight and biases. first element are the weights
		// and second are the biases
		//std::cout << "Entering backprop"<< std::endl;
		auto delta_nablas = backprop(std::get<0>(batch[i]), std::get<1>(batch[i]));

		for (unsigned i = 0; i < number_of_layers; ++i) {
			// adding the deltas to the total nablas
			nabla_w[i] += std::get<0>(delta_nablas)[i];
			nabla_b[i] += std::get<1>(delta_nablas)[i];
		}
	}

	double scalar = learning_rate / (to - from);
	// update weights and biases
	for (unsigned i = 0; i < number_of_layers; ++i) {
		weights[i] -= (nabla_w[i]);
		biases[i] -= (nabla_b[i]);
	}

	for(auto &e: nabla_w)
		e *= scalar;
	for(auto &e: nabla_b)
		e *= scalar;
}

void Network::train_net(std::vector<std::tuple<Matrix, Matrix>> &training,
		unsigned epoch,
		unsigned batch_size,
		double learning_rate,
		std::vector<std::tuple<Matrix, Matrix>> &testing)
{
	// seeding and seting up the random algorithms
	std::random_device rd;
	std::mt19937 mt(rd());
	if (!(testing).empty()) {
		// TODO test the network
		printf("No epoch completed. %u/%lu errors\n", test_mnist_net(testing), testing.size());
	}

	for (unsigned i = 0; i < epoch; ++i) {
		// suffling the training data
		std::shuffle(std::begin(training), std::end(training), mt);

		for (unsigned j = 0; j <= training.size() - batch_size; j += batch_size) {
			// update weights and biases for one minibatch
			update_mini_batch(training, learning_rate, j, j + batch_size);
		}

		// if provided the data to do so, test the network
		if (!(testing).empty()) {
			// TODO test the network
			printf("Epoch %u completed. %u/%lu errors\n", i, test_mnist_net(testing), testing.size());
		} else {
			printf("Epoch %u completed.\n", i);
		}
	}
}

unsigned Network::test_xor_net(std::vector<std::tuple<Matrix, Matrix>> &testing_data) {
	unsigned n = testing_data.size();
	unsigned errors = 0;

	for (unsigned i = 0; i < n; ++i) {
		Matrix m_y {feed_forward(std::get<0>(testing_data[i]))};
		std::vector<double> y {m_y.get_data()};
		std::vector<double> expected_y {std::get<1>(testing_data[i]).get_data()};

		unsigned result = y[0] < 0.5 ? 0 : 1;
		unsigned expected_result = expected_y[0];

		if (result != expected_result)
			++errors;
	}

	return errors;
}

unsigned Network::test_mnist_net(std::vector<std::tuple<Matrix, Matrix>> &testing_data) {
	unsigned n = testing_data.size();
	unsigned errors = 0;

	for (unsigned i = 0; i < n; ++i) {
		Matrix m_y  = feed_forward(std::get<0>(testing_data[i]));

		std::vector<double> y = m_y.get_data();

		std::vector<double> expected_y = std::get<1>(testing_data[i]).get_data();

		unsigned result = std::max_element(y.begin(), y.end()) - y.begin();

		unsigned expected_result = std::max_element(expected_y.begin(),
				expected_y.end()) - expected_y.begin();

		if (result != expected_result) {
			++errors;
			printf("Result: %u | expected: %u\n", result, expected_result);

		}
	}

	printf("errors: %u\n", errors);
	return errors;
}
