
#mkdir -p ~/work_setup/
#cd ~/work_setup/
#git clone https://manjusaka_lin@bitbucket.org/manjusaka_lin/a_home_bin.git
#git clone https://manjusaka_lin@bitbucket.org/manjusaka_lin/a_work_tools.git

#ln -s ~/work_setup/a_home_bin ~/bin
#mv ~/.bashrc ~/bk_bashrc
#ln -s ~/bin/bashrc ~/.bashrc

#sudo chown root:root ~/bin/adb
#sudo chown root:root ~/bin/fastboot

#sudo chmod 4755 ~/bin/adb
#sudo chmod 4755 ~/bin/fastboot

#mkdir -p ~/.android
#ln -s ~/bin/usb_adb.ini ~/.android/usb_adb.ini
#ln -s ~/bin/kermrc ~/.kermrc
#ln -s ~/bin/sprdrc ~/sprdrc
#ln -s ~/bin/rkrc ~/rkrc
ln -s ~/bin/.vimrc ~/.vimrc
echo "source ~/bin/bashrc" >> ~/.bashrc

