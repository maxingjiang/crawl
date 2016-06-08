# crawl_server
usage:

老版本部署：
1.ubuntu14环境:
(1)修改./comfigure
打开echo "export LD_LIBRARY_PATH=$DIR/lib/ubuntu14lib:\$LD_LIBRARY_PATH" >> /etc/profile
注释掉echo "export LD_LIBRARY_PATH=$DIR/lib/ubuntu15lib:\$LD_LIBRARY_PATH" >> /etc/profile
(2)修改./makefile
打开$(CC) $(OBJ)  -o $@ $(DIR_UBUNTU14_LIB) -lzmq -lpthread
删除掉$(CC) $(OBJ)  -o $@ $(DIR_UBUNTU15_LIB) -lzmq -lpthread

2.ubuntu15环境：
(1)修改./comfigure
打开echo "export LD_LIBRARY_PATH=$DIR/lib/ubuntu15lib:\$LD_LIBRARY_PATH" >> /etc/profile
注释掉echo "export LD_LIBRARY_PATH=$DIR/lib/ubuntu14lib:\$LD_LIBRARY_PATH" >> /etc/profile
(2)修改./makefile
打开$(CC) $(OBJ)  -o $@ $(DIR_UBUNTU15_LIB) -lzmq -lpthread
删除掉$(CC) $(OBJ)  -o $@ $(DIR_UBUNTU14_LIB) -lzmq -lpthread
OK

入口文件：main.cpp
新版本部署：
需要将第三方库所有编译的so文件拷贝到/usr/lib/下，用以支持crontab
cd VenusCPP ,make
cd VenusCPP/tools, make
chmod +x build.sh,checkapp.sh,checkbusline.sh,configure
项目需要放到/root/下
OK


其他有用资料；
need install libcurl ,jsoncpp
apt-get install curl libcurl3 libcurl3-dev php5-curl

git init
git status
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/maxingjiang/crawl.git
git push -u origin master

tcpdump -i eth0 host 192.168.88.128 -w tcpdump.log
