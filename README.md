# innfos-robot-cpp-sdk

cd innfos-robot-cpp-sdk/example

mkdir build

cmake ..

make

可执行文件存储在bin文件夹下

5个demo

mode0： 文件夹bin/basic下     功能: 失能机器人

mode1： 文件夹bin/advanced下  功能:异步方式连续记录机器人关节点位（弧度），并打印到终端

mode2： 文件夹bin/advanced下  功能:连续记录机器人关节点位（弧度）一分钟，之后复现该轨迹

mode3： 文件夹bin/advanced下  功能:同步获取方式得到机器人当前点的位置

mode4： 文件夹bin/advanced下  功能:同步获取方式得到机器人当前点的位置，并以关节插值的方式使驱动得最后一轴来回运动20度
