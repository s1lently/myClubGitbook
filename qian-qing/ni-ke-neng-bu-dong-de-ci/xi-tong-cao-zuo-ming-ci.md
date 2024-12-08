---
description: 对于系统操作的名字做了注解
---

# 系统操作名词

## Shell的使用(Windows的命令提示符cmd / MacOS的终端Terminal)

### 移动操作文件夹地址

* 可以通过cd+地址到某一个文件夹  相当于你打开了某一个文件夹 示例如下

#### Windows

```powershell
cd C:\Users\YourName\Documents
```

MacOS

```sh
cd /Users/YourName/Documents
```

### 创建文本文件

#### 在两种shell都可以完成的指令

```
// 在当前目录下创建一个txt文本 里面写了"Hello, World!"
echo Hello, World! > example.txt
```

在Windows会显示为C:\Users\YourName\Documents\example.txt

在MacOS会显示为/Users/YourName/Documents/example.txt

***

## Path

### Path是什么

Path是系统环境变量中的地址 Windows搜索框搜索环境变量 可以看见Path文件夹

让你在系统文件任意位置都能访问到此文件/文件夹内容

### 案例

#### Windows

**方法一：通过系统设置添加路径**

1. 右键点击 “此电脑” 或 “我的电脑”，选择 “属性”。
2. 点击左侧的 “高级系统设置”，然后点击 “环境变量”。
3. 在 “系统变量” 部分，找到名为 `Path` 的条目，点击 “编辑”。
4. 点击 “新建”，添加要全局可用的文件夹路径（例如 `C:\MyFolder`）。
5. 确定所有窗口，并重新启动命令提示符（或 PowerShell）使更改生效。

#### MacOS

如果你要添加的路径是 `/usr/local/myfolder`，可以使用以下命令：

```bash
echo "/usr/local/myfolder" | sudo tee -a /etc/paths
```

这个命令的作用是：

* `echo "/usr/local/myfolder"`：输出你要添加的路径。
* `sudo tee -a /etc/paths`：以 `sudo` 权限将路径追加（`-a` 参数）到 `/etc/paths` 文件中。\


### 为什么软件问你是否要将程序加入Path?

因为这样可以方便其他软件 (如Pycharm)更快地找到此软件
