---
description: 现象展示
---

# Demo试验

github项目入口 [https://github.com/s1lently/Single-layer-perceptron](https://github.com/s1lently/Single-layer-perceptron)

```python
import numpy as np
import matplotlib.pyplot as plt


class Perceptron:
    def __init__(self, learning_rate=0.01, n_iterations=1000):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations
        self.weights = None
        self.bias = None

    def initialize(self, n_features):
        # Initialize to an incorrect state
        self.weights = np.array([-1.0, -1.0])
        self.bias = 5.0

    def fit(self, X, y, ax):
        n_samples, n_features = X.shape
        self.initialize(n_features)

        for i in range(self.n_iterations):
            misclassified = 0
            for idx, x_i in enumerate(X):
                linear_output = np.dot(x_i, self.weights) + self.bias
                y_predicted = 1 if linear_output >= 0 else 0

                if y[idx] != y_predicted:
                    update = self.learning_rate * (y[idx] - y_predicted)
                    self.weights += update * x_i
                    self.bias += update
                    misclassified += 1

            self.plot_decision_boundary(X, y, ax, i)
            plt.pause(0.1)

            if misclassified == 0:
                print(f"Converged after {i + 1} iterations")
                break

    def predict(self, X):
        linear_output = np.dot(X, self.weights) + self.bias
        return np.where(linear_output >= 0, 1, 0)

    def plot_decision_boundary(self, X, y, ax, iteration):
        ax.clear()
        ax.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='blue', label='Crocodile', s=50)
        ax.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='yellow', label='Snake', s=50)

        x1_min, x1_max = X[:, 0].min() - 0.5, X[:, 0].max() + 0.5
        x2_min, x2_max = X[:, 1].min() - 0.5, X[:, 1].max() + 0.5
        xx1, xx2 = np.meshgrid(np.arange(x1_min, x1_max, 0.02),
                               np.arange(x2_min, x2_max, 0.02))
        Z = self.predict(np.c_[xx1.ravel(), xx2.ravel()])
        Z = Z.reshape(xx1.shape)
        ax.contour(xx1, xx2, Z, colors='r', levels=[0.5], linestyles='--', linewidths=2)

        ax.set_xlabel('Length (x1)')
        ax.set_ylabel('Weight (x2)')
        ax.legend()
        ax.set_title(f'Crocodile and Snake Classification (Iteration {iteration})')
        ax.grid(True, linestyle='--', alpha=0.7)

        # Add text for current weights and bias
        weight_text = f'Weights: [{self.weights[0]:.2f}, {self.weights[1]:.2f}], Bias: {self.bias:.2f}'
        ax.text(0.05, 0.05, weight_text, transform=ax.transAxes,
                bbox=dict(facecolor='white', alpha=0.8))


def load_data(filename):
    X = []
    y = []
    with open(filename, 'r') as f:
        next(f)  # Skip header
        for line in f:
            length, weight, label = line.strip().split(',')
            X.append([float(length), float(weight)])
            y.append(1 if label == '鳄鱼' else 0)
    return np.array(X), np.array(y)


# Main program
if __name__ == "__main__":
    # Load data
    X, y = load_data('animal_data.txt')

    # Create figure and axis
    fig, ax = plt.subplots(figsize=(10, 8))

    # Create and train perceptron
    perceptron = Perceptron(learning_rate=0.01, n_iterations=1000)
    perceptron.fit(X, y, ax)

    # Predict and evaluate
    predictions = perceptron.predict(X)
    accuracy = np.mean(predictions == y)
    print(f"Accuracy: {accuracy:.2f}")

    # Output final weights and bias
    print(f"Final weights: {perceptron.weights}")
    print(f"Final bias: {perceptron.bias}")

    plt.show()
```

