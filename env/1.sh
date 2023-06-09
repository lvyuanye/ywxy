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

(echo "Y") | sudo apt-get install vim
(echo "Y") | sudo apt-get install ctags

#安装Vundle（vim插件）
git clone --depth 1 https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim;
vim +PluginInstall +qall;

(echo "Y") | sudo apt-get install cmake
(echo "Y") | sudo apt install samba-common-bin
sudo mkdir /var/lib/samba/usershares

ln -s ~/ywxy/.vimrc ~/.vimrc
echo "source ~/ywxy/bashrc" >> ~/.bashrc

# nerd 字体 内容较大，放到最后下载
git clone --depth 1 https://github.com/ryanoasis/nerd-fonts.git ~/fonts/nerd-fonts
bash ~/fonts/nerd-fonts/install.sh
