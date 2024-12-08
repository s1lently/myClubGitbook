---
description: 如何更快理解这一章
---

# 思路

{% file src="../../.gitbook/assets/a [Autosaved].pptx" %}
这是24年9月份开学的ppt
{% endfile %}

## 如果需要国内下载链接 [点击此处 ](https://wwpl.lanzouw.com/iapAt2ckzlof)

## 请先抛开一切 聚焦于 <mark style="color:red;">分类</mark>

***

## 不要代入其他任何知识 思考下方问题

## 现在我们有两种动物&#x20;

* ### <mark style="color:blue;">鳄鱼</mark>&#x20;
* ### <mark style="color:yellow;">蛇</mark>

## 如何区分他们？

***

## 我们不能直接看到他们的外表 但是传感器告诉了你两种数据

* ### <mark style="color:purple;">x1: 体重</mark>&#x20;
* ### <mark style="color:green;">x2: 身长</mark>

## 为了<mark style="color:red;">让你</mark>能理解 于是有了这一个二维坐标系

<figure><img src="../../.gitbook/assets/image (8).png" alt=""><figcaption></figcaption></figure>

* ### 其中<mark style="color:green;">绿轴x2</mark>代表身长;<mark style="color:purple;">紫轴x1</mark>代表体重
* ### 其中蓝圆代表鳄鱼;黄圆代表蛇

***

## 明显的 基于二维图像 可以简单地利用一条一次函数将二者分开

* ## x1 = k·x2+b

<figure><img src="../../.gitbook/assets/image (2).png" alt=""><figcaption></figcaption></figure>

##

##

## 关键问题是 机器看不懂这样的图像

## 现在的目的是 让机器完成这样的自动调整 以成功地对着一条线进行绘制 以完成分割两个群体的目的&#x20;

