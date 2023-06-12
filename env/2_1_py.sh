
(echo "Y") |sudo apt-get install python-wxtools python3-xlrd python-xlrd-docs  python-setuptools  p7zip-full python-socks python2-dev
sudo add-apt-repository universe
sudo apt update 
(echo "Y") |sudo apt install python2
(echo "Y") |sudo python2 get-pip.py
(echo "Y") |sudo proxychains4 python2 get-pip.py
pip2 --version

sudo  ~/.local/bin/easy_install xlrd
sudo ~/.local/bin/easy_install xlwt
sudo ~/.local/bin/easy_install xlutils
(echo "Y") | sudo apt-get install libsasl2-dev python-dev libldap2-dev libssl-dev
sudo ~/.local/bin/easy_install pexpect
sudo ~/.local/bin/easy_install python-ldap
sudo pip2 install xlsxwriter
#sudo pip2 install xlutils
sudo pip2 install pyinstaller
sudo pip2 install python-jenkins
sudo pip2 install jira
sudo pip2 install pycrypto #for v55 build q
pip install pycrypto
(echo "Y") | sudo apt-get install libmysqlclient-dev
sudo cp my_config.h /usr/include/mysql/
sudo pip2 install MySql-python
sudo pip2 install openpyxl 
(echo "Y") |sudo apt-get install libncurses5

#gms
sudo apt-get install python-dev
sudo apt-get install python-protobuf
sudo apt-get install protobuf-compiler
sudo apt-get install python-virtualenv
sudo apt-get install python-pip
pip install pycrypto #for rsp618 build.
pip install Crypto #for rsp618 build.

