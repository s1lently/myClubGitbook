---
description: 图像处理库的学习
---

# OpenCV预了解

`cv2` 是 OpenCV 的 Python 接口库，提供了大量图像处理和计算机视觉功能。以下是 OpenCV 中的一些常用 `cv2` 模块和函数列表：

#### 图像读取和写入

* `cv2.imread(filename, flags)`：读取图像文件
* `cv2.imwrite(filename, img)`：保存图像到文件
* `cv2.imdecode(buf, flags)`：从内存缓存中解码图像
* `cv2.imencode(ext, img)`：将图像编码成内存中的指定格式

#### 图像显示和窗口操作

* `cv2.imshow(winname, mat)`：在窗口中显示图像
* `cv2.waitKey([delay])`：等待按键输入
* `cv2.destroyWindow(winname)`：销毁指定窗口
* `cv2.destroyAllWindows()`：销毁所有窗口

#### 图像几何变换

* `cv2.resize(src, dsize, ...)`：调整图像大小
* `cv2.warpAffine(src, M, dsize, ...)`：仿射变换
* `cv2.warpPerspective(src, M, dsize, ...)`：透视变换
* `cv2.getRotationMatrix2D(center, angle, scale)`：获取旋转矩阵
* `cv2.flip(src, flipCode)`：图像翻转

#### 图像绘图函数

* `cv2.line(img, pt1, pt2, color, thickness, ...)`：画直线
* `cv2.rectangle(img, pt1, pt2, color, thickness, ...)`：画矩形
* `cv2.circle(img, center, radius, color, thickness, ...)`：画圆
* `cv2.putText(img, text, org, fontFace, fontScale, color, thickness, ...)`：在图像上绘制文字

#### 图像颜色空间转换

* `cv2.cvtColor(src, code)`：颜色空间转换
* `cv2.split(src)`：将图像分离成各个颜色通道
* `cv2.merge(mv)`：将颜色通道合并

#### 边缘检测与轮廓检测

* `cv2.Canny(image, threshold1, threshold2)`：Canny 边缘检测
* `cv2.findContours(image, mode, method)`：查找图像轮廓
* `cv2.drawContours(image, contours, contourIdx, color, ...)`：绘制轮廓

#### 阈值操作

* `cv2.threshold(src, thresh, maxval, type)`：图像阈值化
* `cv2.adaptiveThreshold(src, maxValue, adaptiveMethod, thresholdType, blockSize, C)`：自适应阈值

#### 滤波与图像平滑

* `cv2.GaussianBlur(src, ksize, sigmaX, ...)`：高斯模糊
* `cv2.medianBlur(src, ksize)`：中值模糊
* `cv2.bilateralFilter(src, d, sigmaColor, sigmaSpace)`：双边滤波
* `cv2.blur(src, ksize)`：均值模糊

#### 图像直方图

* `cv2.calcHist(images, channels, mask, histSize, ranges)`：计算直方图
* `cv2.equalizeHist(src)`：直方图均衡化

#### 形态学操作

* `cv2.erode(src, kernel, iterations)`：腐蚀
* `cv2.dilate(src, kernel, iterations)`：膨胀
* `cv2.morphologyEx(src, op, kernel, ...)`：形态学变换（开运算、闭运算等）

#### 特征检测与匹配

* `cv2.SIFT_create()`：创建 SIFT 特征检测器
* `cv2.ORB_create()`：创建 ORB 特征检测器
* `cv2.BFMatcher_create()`：创建暴力匹配器

#### 视频操作

* `cv2.VideoCapture(index)`：创建视频捕获对象
* `cv2.VideoWriter(filename, fourcc, fps, frameSize)`：创建视频写入对象
* `cv2.VideoCapture.read()`：读取视频帧
* `cv2.VideoCapture.release()`：释放视频捕获对象
* `cv2.VideoWriter.release()`：释放视频写入对象

#### 图像金字塔

* `cv2.pyrUp(src, dstsize, ...)`：向上采样
* `cv2.pyrDown(src, dstsize, ...)`：向下采样

#### 其他常用操作

* `cv2.addWeighted(src1, alpha, src2, beta, gamma)`：图像加权求和
* `cv2.absdiff(src1, src2)`：计算两图像差异的绝对值
* `cv2.bitwise_and(src1, src2, ...)`：按位与操作
* `cv2.bitwise_or(src1, src2, ...)`：按位或操作
* `cv2.bitwise_not(src, ...)`：按位取反

这个列表并非完整的 `cv2` 函数集，但包含了常用的图像处理和计算机视觉函数。如果你需要查看详细的所有函数列表，可以使用以下命令：

```python
pythonCopy codeimport cv2
help(cv2)
```

这样可以查看 `cv2` 模块中所有函数的详细说明。
