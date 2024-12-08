---
description: 简要描述如何配置Conda环境 并对可能出现的问题给出了
---

# 配置新的Conda环境

## 配置环境

如果你已经成功安装好了Anaconda和Pycharm 那么我们有两种方式创建新的Python环境

* 在Terminal或者Cmd中直接安装

```lua
conda create --name myenv python=3.8
```

这会创建一个名为 `myenv` 的环境\


* 直接在pycharm创建环境的过程中创建新的conda环境

<figure><img src="../../.gitbook/assets/截屏2024-09-22 下午6.57.51.png" alt="" width="563"><figcaption></figcaption></figure>

* &#x20;步骤是 _**自定义环境->选择 Condo->选择生成新的->选择Python版本3.8->自定一个名字**_

***

## 处理问题

如果环境创建失败 有以下几种可能

### MacOS没有给Conda权限

**尝试使用 `sudo` 命令**

如果权限问题是因为系统权限不足，试试使用 `sudo` 提权来创建环境：

```bash
codesudo conda create --name myenv
```

### **网络问题**

* 后台在下载东西

解决方案 请在创建环境的时候不要下载

* 开了VPN但是没有开终端代理

解决方案&#x20;

#### 请尝试关闭cmd或terminal 然后关闭vpn 然后再次打开cmd或者terminal 或者<mark style="color:red;background-color:blue;">使用专用的port</mark> 其中port是<mark style="color:red;background-color:blue;">端口号</mark> 例如使用clash就需要把port(端口号)改成7890

### Windows

```bash
set http_proxy=http://proxy_address:port
set https_proxy=https://proxy_address:port
```

### MacOS

```bash
export http_proxy=http://proxy_address:port
export https_proxy=https://proxy_address:port
```

