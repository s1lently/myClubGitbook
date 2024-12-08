---
description: 卷积神经网络
---

# 上手

## 首先 这是一个canny边缘检测 能非常明晰地获取你的边缘

### 重要的点是 下面有一个拉框 你能通过调整其值 来了解到那些地方会很明显

```python
import cv2

# 定义滑动条的回调函数（必须要有，但不做实际操作）
def nothing(x):
    pass

# 打开默认摄像头
cap = cv2.VideoCapture(0)

# 创建一个窗口用于显示
cv2.namedWindow('Canny Edges')

# 创建两个滑动条用来调节 Canny 边缘检测的两个阈值
cv2.createTrackbar('Min Threshold', 'Canny Edges', 0, 255, nothing)  # 最小阈值范围 0-255
cv2.createTrackbar('Max Threshold', 'Canny Edges', 0, 255, nothing)  # 最大阈值范围 0-255

# 设置滑动条初始值
cv2.setTrackbarPos('Min Threshold', 'Canny Edges', 100)
cv2.setTrackbarPos('Max Threshold', 'Canny Edges', 200)

while True:
    # 读取摄像头帧
    ret, frame = cap.read()
    if not ret:
        print("无法读取摄像头帧")
        break

    # 转换为灰度图
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 从滑动条中获取当前的阈值
    min_val = cv2.getTrackbarPos('Min Threshold', 'Canny Edges')
    max_val = cv2.getTrackbarPos('Max Threshold', 'Canny Edges')

    # 应用 Canny 边缘检测
    edges = cv2.Canny(gray, min_val, max_val)

    # 显示原始视频帧和边缘检测结果
    cv2.imshow('Original Frame', frame)
    cv2.imshow('Canny Edges', edges)

    # 按下 'q' 键退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放摄像头资源并关闭所有窗口
cap.release()
cv2.destroyAllWindows()
```

## 但是 为什么要会这个呢

***

## 原因是...



### 在1980年代，神经科学家David H. Hubel和Torsten Wiesel研究了猫和猴子的视觉皮层（V1区）对视觉信号的反应。他们发现，视觉皮层中的神经元会响应图像中的某些特定的模式，比如边缘、方向和运动等。

### Yann LeCun在1990年代提出了基于分层结构的卷积神经网络，用于图像识别任务。最早的CNN模型（如LeNet-5）就成功应用于手写数字识别（如MNIST数据集）。

\


## 那么就尝试一下最简单的卷积神经网络

```python
import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms

# 定义超参数
batch_size = 64
learning_rate = 0.001
num_epochs = 5

# 加载MNIST数据集
transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5,), (0.5,))])
train_dataset = torchvision.datasets.MNIST(root='./data', train=True, transform=transform, download=True)
train_loader = torch.utils.data.DataLoader(dataset=train_dataset, batch_size=batch_size, shuffle=True)

test_dataset = torchvision.datasets.MNIST(root='./data', train=False, transform=transform)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset, batch_size=batch_size, shuffle=False)


# 定义卷积神经网络
class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=16, kernel_size=5, stride=1, padding=2)
        self.conv2 = nn.Conv2d(in_channels=16, out_channels=32, kernel_size=5, stride=1, padding=2)
        self.pool = nn.MaxPool2d(kernel_size=2, stride=2, padding=0)
        self.fc1 = nn.Linear(32 * 7 * 7, 128)
        self.fc2 = nn.Linear(128, 10)

    def forward(self, x):
        x = self.pool(torch.relu(self.conv1(x)))
        x = self.pool(torch.relu(self.conv2(x)))
        x = x.view(-1, 32 * 7 * 7)  # 展平
        x = torch.relu(self.fc1(x))
        x = self.fc2(x)
        return x


# 初始化模型、损失函数和优化器
model = CNN()
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

# 训练模型
for epoch in range(num_epochs):
    model.train()
    for images, labels in train_loader:
        # 前向传播
        outputs = model(images)
        loss = criterion(outputs, labels)

        # 反向传播和优化
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    print(f'Epoch [{epoch + 1}/{num_epochs}], Loss: {loss.item():.4f}')

# 测试模型
model.eval()
correct = 0
total = 0
with torch.no_grad():
    for images, labels in test_loader:
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print(f'Accuracy of the model on the test images: {100 * correct / total:.2f}%')

```
