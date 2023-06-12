sudo add-apt-repository universe
sudo apt install python2
sudo apt-get install  libpython2.7-dev 
sudo apt-get install libsasl2-dev  libldap2-dev libssl-dev
sudo apt-get install -y  libldap2-dev libsasl2-dev libssl-dev
sudo apt install python-cairo

pip2 --version

ls /usr/bin/python*

sudo update-alternatives --list python
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 2
sudo update-alternatives --list python
echo "1" | sudo update-alternatives --config python



sudo python2 get-pip.py
pip install xlrd
pip install xlwt
pip install xlutils
pip install pexpect
pip install python-ldap
