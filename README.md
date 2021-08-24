# MiniPoster_Client
## 项目介绍
* MiniPoster_Client为本地主机程序
* 实现本地主机到个人服务器的文件单向传输
* 面向 Linux系统编写
## 使用步骤
* 终端输入`git clone https://github.com/samona-omo/MiniPoster_Client.git`。
* 完成下载后，进入`MinPoster_Client`目录，输入`sh complier.sh`。
* 编译结束，输入`sh run.sh`，启动传输程序。
* 若个人服务器运行有`MiniPoster_Server`程序，则可以传输目标文件。
## 关于启动文件`run.sh`的说明
* 初始内容为:
```shell
# ./bin/client -f $file_name -a $server_ip
# e.g. (note: 123.56.23.24 is an invaild server ip address)
# ./bin/client -f Linux_System_Programing_By_Hit.pdf -a 123.56.23.24

# local test:
./bin/client -f Linux_System_Programing_By_Hit.pdf -a 127.0.0.1
```
* `-f`为必选项，用于指定待传输文件，`-a`也为必选项，用于指定目标服务器IP地址。
* 这里将目标服务器设置为了本地主机，可以更改目标服务器的IP地址，设置文件传输的目标主机，如上被注释掉的例子。
* 这里提供`Linux系统编程(哈工大版).pdf`作为测试文件，也可为各位在Linux环境下的系统编程提供参考。
# 不排除bug存在的可能性，>_<
