# cpp_linux_openssl_so
Create c++ dynamic library project for Linux based platform using vs2019 with third party library openssl, learn example

## 准备工作

### 1. VS安装C++的Liunx开发

![image-20241024175153149](\img\1.png)



### 2. 创建c++项目，并连接对应Linux机器(有条件可做)

工具-选项-跨平台-连接管理器

![image-20241024175153149](\img\2.png)

可更新IntelliSense管理器

![3.png](/img/3.png)



### 3. 新增源码

项目右键属性-常规-配置类型-动态库(.so)

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