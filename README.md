# cpp_linux_openssl_so
Create c++ dynamic library project for Linux based platform using vs2019 with third party library openssl, learn example

### 系统必备

**VS**现在仅支持在 Linux 目标计算机上远程构建。我们不受特定 Linux 发行版的限制，但确实依赖于某些工具的存在。具体说来，我们需要 openssh-server、g++、gdb 和 gdbserver。请使用你喜爱的包管理器安装它们，例如，在基于 Debian 的系统上，可以使用 sudo apt-get install openssh-server g++ gdb gdbserver

## 准备工作

### 1. VS安装C++的Liunx开发

![image-20241024175153149](/img/1.png)



### 2. 创建c++项目，并连接对应Linux机器(有条件可做)

工具-选项-跨平台-连接管理器

![image-20241024175153149](/img/2.png)

可更新IntelliSense管理器

![3.png](/img/3.png)



### 3. 新增源码

项目右键属性-常规-配置类型-动态库(.so)

![4.png](/img/4.png)

### 4. 使用命令查找openssl lib和include文件夹

include默认文件夹：/usr/include

```bash
# 查看openssl版本
openssl version -a

# 查看安装包openssl安装情况
dpkg -l | grep ssl

# gcc 检测是否安装
gcc -v

# g++ 检测是否安装
g++ -v

# 查找libcrypto库目录
find -name "libcrypto*"

# 查找libssl库目录
find -name "libssl*"

# 例如输出:
./opt/kingsoft/wps-office/office6/libssl.so
./opt/kingsoft/wps-office/office6/addons/kpdf2wordv3/ofd2pdf/libssl.so.1.1
./opt/kingsoft/wps-office/office6/libssl.so.1.1
./opt/kingsoft/wps-office/office6/wtool/libssl.so
./opt/kingsoft/wps-office/office6/wtool/libssl.so.1.1
./opt/kingsoft/wtool/libssl.so
./opt/kingsoft/wtool/libssl.so.1.1
./usr/lib/aarch64-linux-gnu/libssl.so
./usr/lib/aarch64-linux-gnu/libssl3.so
./usr/lib/aarch64-linux-gnu/libssl.so.1.1
./usr/lib/aarch64-linux-gnu/libssl.a
./usr/lib/aarch64-linux-gnu/pkgconfig/libssl.pc
./usr/share/kylin-software-center/libssl.so.1.1
./usr/share/kylin-software-center/backend/remote/start_remoter/libssl.so.1.1
./usr/share/doc/libssl-dev
./usr/share/doc/libssl1.1
```



### 5. 配置vs项目属性

配置openssl 的 lib 和 include 文件夹目录

#### 方式一：

![5.png](/img/5.png)



#### 方式二：

配置包

![6.png](/img/6.png)

配置库

![7.png](/img/7.png)

![8.png](/img/8.png)

配置库依赖项

![9.png](/img/9.png)

配置库运行依赖搜索库

![10.png](/img/10.png)

### 6. 编译生成

我是方法一和二都执行，编译成功。



学习参考：[Visual Studio 2022 跨平台开发Linux C程序环境搭建_vs2022 linux 编程需要-CSDN博客](https://blog.csdn.net/zyy29182918/article/details/130405807)



## 拓展

> Linux下的静态库通常以`.a`结尾，但在 Winodws下为`.lib`或者`.a`结尾)
>
> Linux下的动态库以`.so` 或`.so.y`结尾，其中y代表版本号(Windows下为`.dll`)，而且，Linux下的库必须以`lib`开头，用于系统识别(如：`libjpeg.a`,`libsdl.so`等等)

- Linux动态库默认搜索路径

```
/lib64、/usr/lib64、/lib、/usr/lib
```

- 系统头文件目录

```
/usr/include
```

- 常用命令

```
ldd main`：查看二进制可执行文件链接的动态链接库信息，例如`ldd nginx
```

`g++ -c main.cpp`：以单个xx.cpp源文件为单位只编译出xx.o的二进制文件（称为：目标文件）

`g++ xx.o yy.o -o main`：链接所有相关的目标文件连同用到的静态库、动态库、运行时库到最终独立的可执行文件

`file main`：查看文件格式信息

`readelf -h main`：查看ELF文件的基本信息(ELF文件是Linux系统可执行文件的通用格式，windows系统的可执行文件通用格式为PE，二者非常相似，但是不兼容，都是对二进制代码的一种封装)

`readelf -S main`：查看程序的区块，包含机器代码，与程序的数据

`objdump -s -d main.o/main` ：查看ELF文件中的内容

`objdump -r main.o`：查看目标文件的重定位表，用于查看哪些函数需要被重定位，以及被重定位位置的偏移量

#### windows

既可以使用.def文件指明导出函数，可以用__declspec(dllexport)，建议第二种

```c++
extern "C" __declspec(dllexport) void add(int a, int b);
```

**extern C**表示导出标准C语言符号，体现在没有不干净的c++语言符号，

例如：add函数名后面有乱码

动态库通常会生成三个文件 dll、exp、lib。dll包含整体代码实现，lib是编译时需要包含了符号，exp没用。

动态库lib文件与静态库lib不同

#### Linux

动态库仅生成一个so文件，静态库生成一个a文件

