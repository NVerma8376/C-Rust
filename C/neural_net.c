#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of sigmoid for backpropagation
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Random number generator for weights
double random_weight() {
    return ((double)rand() / RAND_MAX) * 2.0 - 1.0; // Random value between -1 and 1
}

int main() {
    // Input dataset
    double inputs[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    // Expected outputs
    double outputs[4] = {0, 1, 1, 0}; // XOR problem

    // Neural network parameters
    int input_neurons = 2;
    int hidden_neurons = 2;
    int output_neurons = 1;
    int epochs = 10000;  // Training iterations
    double learning_rate = 0.1;

    // Weight and bias initialization
    double hidden_weights[2][2];   // Weights for input -> hidden layer
    double hidden_bias[2];
    double output_weights[2];     // Weights for hidden -> output layer
    double output_bias;

    // Randomly initialize weights and biases
    for (int i = 0; i < hidden_neurons; i++) {
        hidden_bias[i] = random_weight();
        for (int j = 0; j < input_neurons; j++) {
            hidden_weights[i][j] = random_weight();
        }
    }
    output_bias = random_weight();
    for (int i = 0; i < hidden_neurons; i++) {
        output_weights[i] = random_weight();
    }

    // Training loop
    for (int epoch = 0; epoch < epochs; epoch++) {
        double total_error = 0.0;

        for (int sample = 0; sample < 4; sample++) {
            // Feedforward
            double hidden_layer[2] = {0, 0};
            double output = 0.0;

            // Calculate hidden layer activations
            for (int i = 0; i < hidden_neurons; i++) {
                hidden_layer[i] = hidden_bias[i];
                for (int j = 0; j < input_neurons; j++) {
                    hidden_layer[i] += inputs[sample][j] * hidden_weights[i][j];
                }
                hidden_layer[i] = sigmoid(hidden_layer[i]);
            }

            // Calculate output layer activation
            output = output_bias;
            for (int i = 0; i < hidden_neurons; i++) {
                output += hidden_layer[i] * output_weights[i];
            }
            output = sigmoid(output);

            // Calculate error
            double error = outputs[sample] - output;
            total_error += error * error;

            // Backpropagation (Output Layer)
            double output_gradient = error * sigmoid_derivative(output);
            for (int i = 0; i < hidden_neurons; i++) {
                output_weights[i] += learning_rate * output_gradient * hidden_layer[i];
            }
            output_bias += learning_rate * output_gradient;

            // Backpropagation (Hidden Layer)
            for (int i = 0; i < hidden_neurons; i++) {
                double hidden_gradient = output_gradient * output_weights[i] * sigmoid_derivative(hidden_layer[i]);
                for (int j = 0; j < input_neurons; j++) {
                    hidden_weights[i][j] += learning_rate * hidden_gradient * inputs[sample][j];
                }
                hidden_bias[i] += learning_rate * hidden_gradient;
            }
        }

        // Print error every 1000 epochs
        if (epoch % 1000 == 0) {
            printf("Epoch %d, Error: %f\n", epoch, total_error);
        }
    }

    // Test the network
    printf("\nTesting the network:\n");
    for (int sample = 0; sample < 4; sample++) {
        // Feedforward
        double hidden_layer[2] = {0, 0};
        double output = 0.0;

        for (int i = 0; i < hidden_neurons; i++) {
            hidden_layer[i] = hidden_bias[i];
            for (int j = 0; j < input_neurons; j++) {
                hidden_layer[i] += inputs[sample][j] * hidden_weights[i][j];
            }
            hidden_layer[i] = sigmoid(hidden_layer[i]);
        }

        output = output_bias;
        for (int i = 0; i < hidden_neurons; i++) {
            output += hidden_layer[i] * output_weights[i];
        }
        output = sigmoid(output);

        printf("Input: %d %d, Output: %f\n", (int)inputs[sample][0], (int)inputs[sample][1], output);
    }

    return 0;
}
