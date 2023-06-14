# sudo apt update
sudo apt install virtualbox virtualbox-ext-pack

# 微信https://blog.csdn.net/baidu_39140291/article/details/127824539
wget http://archive.ubuntukylin.com/software/pool/partner/ukylin-wine_70.6.3.25_amd64.deb
wget http://archive.ubuntukylin.com/software/pool/partner/ukylin-wechat_3.0.0_amd64.deb
sudo apt-get -f -y ./ukylin-wine_70.6.3.25_amd64.deb
sudo apt-get -f -y ./ukylin-wechat_3.0.0_amd64.deb
# env WINEPREFIX="$HOME/.ukylin-wine/wechat" /usr/bin/ukylin-wine winecfg #调整分辨率用


