# YOLO DEMO

## 如果你想快速尝试 可以直接下载github的项目 另外 也有备份存在

Github地址: [点击此处进入](https://github.com/s1lently/YOLO-DEMO/tree/main)\
蓝奏云地址: [点击此处进入](https://wwpl.lanzouw.com/iztre2am12jc)

***

## 下方将会提供三种不同的的调用YOLO V8官方的模型yolov8s.pt

### 1. 处理视频

#### 运行前提:

* a. 请完成ppt已描述过的步骤
* b. 需要你将项目文件夹内添加一个任意的视屏 并改名为"test.mp4"

#### Code:

```python
import cv2
from ultralytics import YOLO

model = YOLO('yolov8s.pt')
cap = cv2.VideoCapture('test.mp4')
out = cv2.VideoWriter('output_video.mp4', cv2.VideoWriter_fourcc(*'mp4v'), cap.get(cv2.CAP_PROP_FPS),
                      (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))))

while cap.isOpened():
    ret, frame = cap.read()
    if not ret: break
    results = model(frame)
    out.write(results[0].plot())

cap.release()
out.release()
```

### 2. 处理照片

#### 运行前提:

* a. 请完成ppt已描述过的步骤
* b. 需要你将项目文件夹内添加一个任意的图片文件 并改名为"test.png"

#### Code:

```python
from ultralytics import YOLO
import cv2

# 加载 YOLOv8 模型
model = YOLO('yolov8s.pt')

# 读取图片
img = cv2.imread('test.png')

# 使用 YOLOv8 进行目标检测
results = model(img)

# 在图片上绘制边框
annotated_img = results[0].plot()

# 保存带有边框的图片
cv2.imwrite('result.png', annotated_img)

print("处理完成，结果保存在 result.png")
```

### 3. 处理摄像头人脸

#### 运行前提:

* a. 请完成ppt已描述过的步骤

#### Code:

```python
import cv2
from ultralytics import YOLO

# 加载 YOLOv8 模型
model = YOLO('yolov8s.pt')

# 打开系统摄像头（0 表示默认摄像头）
cap = cv2.VideoCapture(0)

# 检查摄像头是否成功打开
if not cap.isOpened():
    print("无法打开摄像头")
    exit()

while True:
    # 从摄像头读取一帧
    ret, frame = cap.read()

    if not ret:
        print("无法读取摄像头画面")
        break

    # 使用 YOLOv8 进行目标检测
    results = model(frame)

    # 获取检测结果并在帧上绘制边框
    annotated_frame = results[0].plot()

    # 显示处理后的帧
    cv2.imshow('YOLOv8 Detection', annotated_frame)

    # 按 'q' 键退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放摄像头资源并关闭窗口
cap.release()
cv2.destroyAllWindows()
```
