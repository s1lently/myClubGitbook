---
description: 简要描述
---

# 如何使用别人开发好的任何模型

Hugging Face 平台支持多种开源模型架构和文件格式，以下是常见模型类型及其对应的文件后缀整理（已修正部分笔误并补充完整信息）：

***

#### **1. Transformer 系列模型**

* **主要用途**：NLP 任务（BERT、GPT、T5 等）
* **常见后缀**：
  * `.bin` (PyTorch 权重文件)
  * `.safetensors` (Hugging Face 安全格式，替代 `.bin`)
  * `.h5` (TensorFlow/Keras 权重文件)
  * `.msgpack` (旧版 Flax/JAX 格式)
  * `.gguf` (量化格式，用于 llama.cpp 等推理工具)

***

#### **2. Diffusion 模型（文生图、图生图）**

* **代表模型**：Stable Diffusion、DALL-E
* **常见后缀**：
  * `.safetensors` (推荐的安全格式，替代 `.ckpt`)
  * `.ckpt` (PyTorch 检查点文件，逐渐被弃用)
  * `.onnx` (导出为跨平台推理格式)

***

#### **3. 卷积神经网络 (CNN)**

* **主要用途**：图像分类、目标检测
* **常见后缀**：
  * `.pth` (PyTorch 原生格式)
  * `.h5` (TensorFlow/Keras 格式)
  * `.onnx` (标准化推理格式)
  * `.tflite` (移动端轻量化模型)

***

#### **4. 语音模型（ASR、TTS）**

* **代表模型**：Whisper、Wav2Vec2
* **常见后缀**：
  * `.bin` (PyTorch)
  * `.safetensors`
  * `.onnx` (导出为跨框架格式)

***

#### **5. 多模态模型**

* **代表模型**：CLIP、FLAVA
* **常见后缀**：
  * `.bin`、`.safetensors` (PyTorch)
  * `.h5` (TensorFlow)

***

#### **6. 其他特殊格式**

* **量化/轻量化格式**：
  * `.gguf` (llama.cpp、alpaca.cpp 使用)
  * `.ptl` (PyTorch Mobile)
* **框架通用格式**：
  * `.onnx` (支持跨框架推理)
  * `.pb` (TensorFlow Protocol Buffer)

####
