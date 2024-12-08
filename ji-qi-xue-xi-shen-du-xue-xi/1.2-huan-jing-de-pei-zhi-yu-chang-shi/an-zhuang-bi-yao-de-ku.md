---
description: 如若想使用YOLO v8作为演示demo 那么必须要安装对应的库
---

# 安装必要的库

## 库的安装

### 使用终端安装 进入此conda环境的终端有两种方式

* #### 方法1: 直接通过Windows的 Conda Prompt进入 然后直接键入

```bash
conda activate env
// 其中env是你创建环境的名字 需要替换掉
```

* &#x20;方法2: **通过加入过Path的Terminal或者cmd 与上面代码相同**

```bash
conda activate env
// 其中env是你创建环境的名字 需要替换掉
```

* 方法3: Pycharm直接进入Conda终端

<figure><img src="../../.gitbook/assets/截屏2024-09-22 下午7.18.30.png" alt="" width="168"><figcaption><p>看箭头</p></figcaption></figure>

在你配置好conda环境之后 直接点击这个![](<../../.gitbook/assets/截屏2024-09-22 下午7.19.41.png>)图标 就可以进入对应的conda终端\


***

## 开始安装库

如果你已经成功进入了你的conda环境 那么你应该可以看见<mark style="color:blue;background-color:orange;">**如图所示**</mark>的一个括号内有你的环境名字

<figure><img src="../../.gitbook/assets/截屏2024-09-22 下午7.23.47.png" alt=""><figcaption><p>(pytorch_new)是环境的名字</p></figcaption></figure>

### 现在开始安装三个库

### 安装pytorch 一个机器学习框架

如果你是MacOS 键入

```bash
conda install pytorch::pytorch torchvision torchaudio -c pytorch
```

如果你是Windows

有英伟达显卡 请键入:

```powershell
conda install pytorch torchvision torchaudio pytorch-cuda=11.8 -c pytorch -c nvidia
```

没有英伟达显卡:

```powershell
conda install pytorch torchvision torchaudio cpuonly -c pytorch
```

***

### 安装OpenCV 一个图像处理框架

#### 任何系统 键入

```powershell
conda install -c conda-forge opencv
```

***

### 配置YOLO v8

#### 任何系统 键入

```powershell
conda install -c conda-forge ultralytics
```

***

## 可能遇到的问题

### 卡进度

* 解决方案: 关掉终端新开一个 检查后台下载 检查vpn 解决网络问题后重试

### 连接失败

* 解决方案: 尝试切换成cmd或者terminal 检查后台下载 检查vpn 解决网络问题后重试
