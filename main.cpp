#include "idx_header.hpp"
#include "network.hpp"
#include <iostream>
#include <vector>
#include <tuple>

std::vector<double> make_label_vect(unsigned char label)
{
	std::vector<double> label_vect{};

	for (unsigned i = 0; i < 10; ++i){
		if (i == label)
			label_vect.push_back(1);
		else
			label_vect.push_back(0);
	}

	return label_vect;
}

std::vector<std::tuple<Matrix, Matrix>> make_input(const std::vector<unsigned char> &label_data,
													const std::vector<unsigned char> &image_data,
													unsigned n)
{
	unsigned image_h {28};
	unsigned image_w {28};
	unsigned image_lenght {image_h * image_w};
	std::cout << n << std::endl;

	std::vector<std::tuple<Matrix, Matrix>> data{};

	for (unsigned k = 0; k < 1000; ++k) {
		// make the image matrix
		std::vector<double> image (image_data.begin() + k * image_lenght, image_data.begin() + k * image_lenght + image_lenght);
		Matrix m_image {image_lenght, 1, image};

		// make the label matrix
		Matrix m_label {10, 1, make_label_vect(label_data[k])};

		(data).push_back(std::make_tuple(m_image, m_label));
	}

	return data;
}

int main(int argc, char *argv[])
{
	if (argc != 5) {
		std::cerr << "Usage: ./parser <training Images files> <training label file> <testing images file> <testing label file>\n";
		exit(EXIT_FAILURE);
	}

	Idx_file training_images {argv[1]};
	Idx_file training_labels {argv[2]};
	Idx_file testing_images {argv[3]};
	Idx_file testing_labels {argv[4]};

	auto training_data = make_input(training_labels.get_data(), training_images.get_data(), 60000);
	auto testing_data = make_input(testing_labels.get_data(), testing_images.get_data(), 10000);

	//Matrix test_d1 {2, 1, {1, 1}};
	//Matrix test_d2 {2, 1, {1, 0}};
	//Matrix test_d3 {2, 1, {0, 1}};
	//Matrix test_d4 {2, 1, {0, 0}};
	//Matrix expected_result1 {1, 1, {1}};
	//Matrix expected_result2 {1, 1, {0}};

	//std::tuple<Matrix, Matrix> t1 = std::make_tuple(test_d1, expected_result2);
	//std::tuple<Matrix, Matrix> t2 = std::make_tuple(test_d2, expected_result1);
	//std::tuple<Matrix, Matrix> t3 = std::make_tuple(test_d3, expected_result1);
	//std::tuple<Matrix, Matrix> t4 = std::make_tuple(test_d4, expected_result2);

	//std::vector<std::tuple<Matrix, Matrix>> training_data {t1, t2, t3, t4};

	Network net {3, std::vector<unsigned> {784, 30, 10}};
	//net.train_net(training_data, 100, 30, 100, training_data);
	net.test_mnist_net(testing_data);

	return 0;
}
