##########################################################################
# File Name: 3_python_pyqt4.sh
# Author: lvyuanye
# mail: 1349746865@qq.com
# Created Time: 2023年06月14日 星期三 14时38分28秒
#########################################################################
#!/bin/zsh
PATH=/home/lyy/bin:/home/lyy/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin
export PATH

(echo "Y") | sudo add-apt-repository ppa:rock-core/qt4
sudo apt-get update

cd ~/Downloads

wget http://archive.ubuntu.com/ubuntu/pool/universe/q/qt-assistant-compat/libqtassistantclient4_4.6.3-7build1_amd64.deb
(echo "Y") | sudo apt-get install ./libqtassistantclient4_4.6.3-7build1_amd64.deb
wget http://archive.ubuntu.com/ubuntu/pool/universe/p/python-qt4/python-qt4_4.12.1+dfsg-2_amd64.deb
(echo "Y") | sudo apt-get install ./python-qt4_4.12.1+dfsg-2_amd64.deb
wget http://archive.ubuntu.com/ubuntu/pool/universe/p/python-pyaudio/python-pyaudio_0.2.11-1build2_amd64.deb
(echo "Y") | sudo apt-get install ./python-pyaudio_0.2.11-1build2_amd64.deb

(echo "Y") | sudo apt-get install libcanberra-gtk-module
