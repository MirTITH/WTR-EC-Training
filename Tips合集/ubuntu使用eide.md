# ubuntu使用eide

## ubuntu 基础知识
[ubuntu基础知识.md](ubuntu基础知识.md)

## 安装 vscode
从微软官网下安装包

## 安装 vscode 插件

参考 [01-stm32基础，环境配置.md#扩展插件](../01-stm32基础，环境配置/01-stm32基础，环境配置.md#扩展插件)

## 安装 arm-none-eabi-gcc

请使用战队网盘里的 deb 安装包，不要使用 apt 在线安装的包。

（如果已经使用 apt 在线安装了，请使用 `sudo apt purge gcc-arm-none-eabi` 删除）

安装包位置：

```
smb://pan.wtrobot.net/WTR/Softwares/Ubuntu/gcc-arm-none-eabi-10.3-2021.10
```
> 家用电脑请使用以`x86_64`结尾的包。（树莓派等 arm 架构的电脑选择 `arm64` 结尾的包）

安装方法：
```
sudo apt install 安装包路径
```

附：为什么不要使用 apt 在线安装的包：
1. apt 在线安装的版本太老了，eide 和 Cortex-Debug 不支持那么老的版本
2. apt 在线安装的版本没有 arm-none-eabi-gdb，不能调试

**战队网盘里的 deb 安装包包括了 arm-none-eabi-gcc 和 arm-none-eabi-gdb**

## 安装 openocd

**不要使用 apt 在线安装 Openocd，版本太老（需要至少 v0.11）**

**如果已经使用 apt 在线安装，请使用`sudo apt purge openocd`卸载**

OpenOCD 有很多种方法安装，以下是其中一种方法（编译安装）

> 编译安装会把可执行文件放在系统目录`/usr/local/bin/`中，因此不需要手动添加 PATH 了

1. 获得源代码：
    ```bash
    git clone git://git.code.sf.net/p/openocd/code openocd
    ```

2. 切换到 release 版本
    ```bash
    # 进入 git 仓库目录
    cd openocd 

    # 查看有哪些版本（使用 q 退出）
    git tag

    # 这里的版本可以选上条命令显示的最新版本（数字越大越新，不要选带rc的）
    git checkout v0.11.0
    ```
    
    出现类似如下提示表示成功：
    ```
    M       jimtcl
    注意：正在切换到 'v0.11.0'。

    您正处于分离头指针状态。您可以查看、做试验性的修改及提交，并且您可以在切换
    回一个分支时，丢弃在此状态下所做的提交而不对分支造成影响。

    如果您想要通过创建分支来保留在此状态下所做的提交，您可以通过在 switch 命令
    中添加参数 -c 来实现（现在或稍后）。例如：

    git switch -c <新分支名>

    或者撤销此操作：

    git switch -

    通过将配置变量 advice.detachedHead 设置为 false 来关闭此建议

    HEAD 目前位于 f342aac08 The openocd-0.11.0 release
    ```

3. 安装编译所需库
    ```
    sudo apt install build-essential pkg-config autoconf automake libtool libusb-dev libusb-1.0-0-dev libhidapi-dev libtool libsysfs-dev
    ```

4. 添加 UDEV rules
    ```
    sudo cp ./contrib/60-openocd.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules
    ```
    > 不添加的话有些烧录器需要 root 权限才能访问  
    > 这一步也可以在安装完成后进行，在这一步进行是因为后面的步骤比较费时

5. 引导生成环境
    ```
    ./bootstrap
    ```

6. 配置
    ```
    ./configure
    ```
    > 此命令运行结束时会打印适配器列表，大部分 yes 就行

7. 编译安装
   ```
   make -j
   sudo make install
   ```

8. 安装完成，检查版本
    ```
    openocd -v
    ```

> 编译安装的 OpenOCD 不能用 apt 卸载，需要在这个文件夹里使用 `sudo make uninstall` 卸载  
> 安装完后可以删除这个源代码目录。删除这个目录后如果想卸载 OpenOCD，需要再次按照这个教程进行完第5步，然后执行 `sudo make uninstall`
