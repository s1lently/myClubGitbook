# 基础的

```
import numpy as np
import tkinter as tk
from tkinter import ttk
from torchvision import datasets, transforms
from scipy.special import expit  # for sigmoid function


class DigitRecognizer:
    def __init__(self):
        # Load MNIST data from torchvision
        mnist_data = datasets.MNIST('data', train=True, download=True,
                                    transform=transforms.ToTensor())
        self.x_train = mnist_data.data.numpy().reshape(-1, 784) / 255.0
        self.y_train = mnist_data.targets.numpy()

        # Initialize weights and biases for 10 digits
        self.weights = np.random.randn(784, 10) * 0.01
        self.biases = np.zeros(10)

        # Training parameters
        self.learning_rate = 0.01
        self.epochs = 5

        # GUI setup
        self.setup_gui()

    def sigmoid(self, x):
        return expit(x)

    def train(self):
        print("Training started...")
        for epoch in range(self.epochs):
            for i in range(len(self.x_train)):
                # Forward pass
                x = self.x_train[i]
                y = np.zeros(10)
                y[self.y_train[i]] = 1

                # Calculate predictions
                z = np.dot(x, self.weights) + self.biases
                predictions = self.sigmoid(z)

                # Backward pass
                error = predictions - y
                self.weights -= self.learning_rate * np.outer(x, error)
                self.biases -= self.learning_rate * error

            if epoch % 1 == 0:
                print(f"Epoch {epoch + 1}/{self.epochs} completed")
        print("Training completed!")

    def setup_gui(self):
        self.root = tk.Tk()
        self.root.title("Digit Recognizer")

        # Drawing area
        self.canvas = tk.Canvas(self.root, width=280, height=280, bg='black')
        self.canvas.pack(pady=20)

        # Create 28x28 grid of rectangles
        self.cells = []
        for i in range(28):
            row = []
            for j in range(28):
                x1, y1 = j * 10, i * 10
                x2, y2 = x1 + 10, y1 + 10
                rect = self.canvas.create_rectangle(x1, y1, x2, y2, fill='black', outline='gray')
                row.append(rect)
            self.cells.append(row)

        # Bind mouse events
        self.canvas.bind('<B1-Motion>', self.paint)
        self.canvas.bind('<ButtonRelease-1>', self.update_probabilities)

        # Probability bars
        self.prob_frame = ttk.Frame(self.root)
        self.prob_frame.pack(pady=20, padx=20, fill='x')

        self.prob_bars = []
        self.prob_labels = []
        for i in range(10):
            label = ttk.Label(self.prob_frame, text=str(i))
            label.grid(row=i, column=0, padx=5)

            progressbar = ttk.Progressbar(self.prob_frame, length=200, mode='determinate')
            progressbar.grid(row=i, column=1, padx=5, pady=2)

            value_label = ttk.Label(self.prob_frame, text="0.00%")
            value_label.grid(row=i, column=2, padx=5)

            self.prob_bars.append(progressbar)
            self.prob_labels.append(value_label)

        # Clear button
        clear_btn = ttk.Button(self.root, text="Clear", command=self.clear_canvas)
        clear_btn.pack(pady=10)

    def paint(self, event):
        # Get cell coordinates
        x, y = event.x // 10, event.y // 10
        if 0 <= x < 28 and 0 <= y < 28:
            # Paint current cell and neighbors
            for dx in [-1, 0, 1]:
                for dy in [-1, 0, 1]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < 28 and 0 <= ny < 28:
                        intensity = 255 - (abs(dx) + abs(dy)) * 50
                        color = f'#{intensity:02x}{intensity:02x}{intensity:02x}'
                        self.canvas.itemconfig(self.cells[ny][nx], fill=color)

    def update_probabilities(self, event):
        # Get image data
        image = np.zeros((28, 28))
        for i in range(28):
            for j in range(28):
                color = self.canvas.itemcget(self.cells[i][j], 'fill')
                if color != 'black':
                    # Convert hex color to grayscale value
                    intensity = int(color[1:3], 16) / 255.0
                    image[i][j] = intensity

        # Flatten and predict
        flat_image = image.reshape(784)
        z = np.dot(flat_image, self.weights) + self.biases
        probabilities = self.sigmoid(z)

        # Update probability bars
        for i in range(10):
            prob = probabilities[i] * 100
            self.prob_bars[i]['value'] = prob
            self.prob_labels[i]['text'] = f"{prob:.2f}%"

    def clear_canvas(self):
        for row in self.cells:
            for cell in row:
                self.canvas.itemconfig(cell, fill='black')
        for i in range(10):
            self.prob_bars[i]['value'] = 0
            self.prob_labels[i]['text'] = "0.00%"

    def run(self):
        self.train()
        self.root.mainloop()


if __name__ == "__main__":
    app = DigitRecognizer()
    app.run()
```
