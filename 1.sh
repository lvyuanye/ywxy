##########################################################################
# File Name: 1.sh
# Author: amoscykl
# mail: amoscykl980629@163.com
# Created Time: 2022年06月05日 星期日 10时46分19秒
#########################################################################
#!/bin/zsh
PATH=/home/edison/bin:/home/edison/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin
export PATH
#安装编译器
(echo "Y") | sudo apt install build-essential
#交叉编译器
(echo "Y") | sudo apt-get install gcc-arm-linux-gnueabihf;
(echo "Y") | sudo apt-get install g++-arm-linux-gnueabihf;

#安装Vundle（vim插件）
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim;
vim +PluginInstall +qall;

(echo "Y") | sudo apt install samba-common-bin
sudo mkdir /var/lib/samba/usershares

ln -s ~/bin/.vimrc ~/.vimrc
echo "source ~/bin/bashrc" >> ~/.bashrc
