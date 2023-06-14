#(echo "Y") | sudo add-apt-repository ppa:danielrichter2007/grub-customizer
sudo apt-get update
(echo "Y") | sudo apt-get install grub-customizer
#(echo "Y") | sudo apt-get install openjdk-7-jdk #use .tar.gz to install
(echo "Y") | sudo apt-get install openjdk-8-jdk net-tools

(echo "Y") | sudo apt-get install wine64
(echo "Y") | sudo apt-get install -y git flex bison gperf build-essential libncurses5-dev:i386 
(echo "Y") | sudo apt-get install libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-dev g++-multilib 
(echo "Y") | sudo apt-get install tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386 
(echo "Y") | sudo apt-get install dpkg-dev libsdl1.2-dev libesd0-dev
(echo "Y") | sudo apt-get install git-core gnupg flex bison gperf build-essential  
(echo "Y") | sudo apt-get install zip curl zlib1g-dev gcc-multilib g++-multilib 
(echo "Y") | sudo apt-get install libc6-dev-i386 
(echo "Y") | sudo apt-get install lib32ncurses5-dev x11proto-core-dev libx11-dev 
(echo "Y") | sudo apt-get install lib32z-dev ccache
(echo "Y") | sudo apt-get install libgl1-mesa-dev libxml2-utils xsltproc unzip m4
(echo "Y") | sudo apt-get install libssl-dev
(echo "Y") | sudo apt-get install samba net-tools build-essential cmake python3-dev python-dev
#(echo "Y") | sudo apt-get install smbfs
(echo "Y") | sudo apt-get install cifs-utils
(echo "Y") | sudo apt-get install pip

#gcc-4.4 g++-4.4 g++-4.4-multilib gcc-4.4-multilib smbfs cifs-utils mingw32 
(echo "Y") |sudo apt-get install openssh-server xrdp samba   git gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386   g++-multilib tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386  libxml2-utils gnome-system-tools apcupsd xrdp vim vim-tiny vim-athena vim-gtk vim-nox python-pexpect  libwww-mechanize-gzip-perl gawk
(echo "Y") |sudo apt-get install terminator git-core curl git
#dconf-tools python-pip
sudo gsettings set org.gnome.desktop.default-applications.terminal exec /usr/bin/terminator
(echo "Y") |sudo apt-get install nautilus-actions
(echo "Y") |sudo apt-get install tofrodos bison flex gperf libxml2-utils
(echo "Y") |sudo apt-get install  python-dev build-essential
#(echo "Y") |sudo apt-get install python-ldap python-wxtools python-xlrd python-openpyxl python-setuptools python-mysqldb p7zip-full python-socks
(echo "Y") |sudo apt-get install python-wxtools python3-xlrd python-xlrd-docs  python-setuptools  p7zip-full python-socks

sudo easy_install xlrd
sudo easy_install xlwt
sudo easy_install xlutils
sudo easy_install pexpect
#sudo pip install --upgrade pip
sudo pip install xlsxwriter
sudo pip install xlutils
#sudo pip install pymongo==2.6.2
#sudo pip install openpyxl==2.2.3（版本不能太久，也不能太高
#echo "deb http://us.archive.ubuntu.com/ubuntu trusty main universe" >> /etc/apt/sources.list
(echo "Y") |sudo apt-get install mingw32 
#(echo "Y") |sudo apt-get install gcc-mingw-w64





(echo "Y") |sudo apt-get install tree
(echo "Y") |sudo apt-get install fastboot
(echo "Y") |sudo apt-get install gitk silversearcher-ag
(echo "Y") |sudo apt-get install ctags cscope ckermit qt4* libqtwebkit-dev libxrender-dev

#for android p
(echo "Y") | sudo apt-get install libswitch-perl
## gedit chinese error
gsettings set org.gnome.gedit.preferences.encodings candidate-encodings "['GB18030','UTF-8','CURRENT','ISO-8859-15','UTF-16']"
#sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 100
#sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.6 50
#sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 100
#sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 50
#sudo update-alternatives --install /usr/bin/cpp cpp-bin /usr/bin/cpp-4.4 100
#sudo update-alternatives --install /usr/bin/cpp cpp-bin /usr/bin/cpp-4.6 50
#dpkg --get-selections  | grep linux
#(echo "Y") | sudo apt-get install linux-modules-extra-4.15.0-38-generic
#(echo "Y") | sudo apt-get install linux-headers-4.15.0-38-generic
#(echo "Y") | sudo apt-get install linux-image-4.15.0-38-generic


(echo "Y") | sudo pip install pyinstaller
(echo "Y") | sudo apt-get install qt4-dev-tools qt4-doc qt4-qtconfig qt4-demos qt4-designer libqwt5-qt4 libqwt5-qt4-dev 

(echo "Y") |pip install python-jenkins
(echo "Y") |pip install jira
(echo "Y") |pip install xlrd
(echo "Y") |pip install xlwt
(echo "Y") |pip install xlutils
(echo "Y") |pip install pexpect
(echo "Y") |pip install xlsxwriter
(echo "Y") |sudo apt-get install python-ldap
(echo "Y") |sudo apt install libssl-dev vim
(echo "Y") |sudo apt-get install ctags cscope
(echo "Y") |sudo apt-get install scrcpy
(echo "Y") |sudo apt install libssl-dev
pip install pyelftools #for rk3566 r
(echo "Y") |sudo apt-get install device-tree-compiler
(echo "Y") |sudo apt-get install liblz4-tool net-tools gparted

# 压缩和解压rar文件
(echo "Y") | sudo apt-get install rar
(echo "Y") | sudo apt-get install unrar

#no in 2004

#ckermit
#easy_install
#python-xlrd


#no in 2004

#
#python-openpyxl
#python-mysqldb
#pip
#mingw32
#libqtwebkit-dev
#qt4-dev-tools
#qt4-doc
#qt4-qtconfig
#qt4-demos
#qt4-designer
#libqwt5-qt4
#libqwt5-qt4-dev
