# sudo apt update
sudo apt install virtualbox virtualbox-ext-pack

# 微信https://blog.csdn.net/baidu_39140291/article/details/127824539
wget http://archive.ubuntukylin.com/software/pool/partner/ukylin-wine_70.6.3.25_amd64.deb
wget http://archive.ubuntukylin.com/software/pool/partner/ukylin-wechat_3.0.0_amd64.deb
sudo apt-get -f -y ./ukylin-wine_70.6.3.25_amd64.deb
sudo apt-get -f -y ./ukylin-wechat_3.0.0_amd64.deb
# env WINEPREFIX="$HOME/.ukylin-wine/wechat" /usr/bin/ukylin-wine winecfg #调整分辨率用

# smplayer视频播放
(echo "Y") | sudo dpkg-reconfigure libdvd-pkg
(echo "Y") | sudo add-apt-repository ppa:rvm/smplayer
(echo "Y") | sudo apt-get update
(echo "Y") | sudo apt-get install smplayer mpv
(echo "Y") | sudo apt-get install ubuntu-restricted-extras

