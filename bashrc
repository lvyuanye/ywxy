# ~/.bashrc: executed by bash(1) for non-login shells.

#add for ubuntu 1804 local install
export PATH=~/ywxy:$PATH

#export PATH=~/all_codes/my_codes/myqq_python/dev_tools/depot_tools:~/bin:~/bin/images:~/bin/SignTool:$PATH
#export PATH=/home/manjusaka/all_codes/mtk6572/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin:$PATH
#export PATH=/usr/lib/arm-linux-androideabi-4.6/prebuilt/linux-x86_64/bin:$PATH
#export PATH=/usr/lib/arm-linux-androideabi-4.9/bin:$PATH
#export PATH=/usr/lib/gcc-arm-none-eabi-4_8-2014q3/bin:$PATH

# export USE_CCACHE=1
# #export CCACHE_COMPILERCHECK=content
# #export CCACHE_SLOPPINESS=time_macros,include_file_mtime,file_macro
#
# #export CCACHE_DIR=/media/2Tdata/for_ccache_dir
# export CCACHE_DIR=~/for_ccache_dir
#
# export CCACHE_LOGFILE=/media/misc_data/for_ccache_dir/ccache.logss
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
# #alias kinc='cd /data/build/kernel_l27x/omap;make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- -j4 uImage;cp arch/arm/boot/zImage /data/data/emmc/zImage;cd /data/data/emmc;  ./umulti.sh; ls -l;sudo ./fastboot flash boot boot.img'
# #alias mkinc='cd /home/manjusaka/all_codes/mtk_codes/exocet_jb_6577; ./makeMtk  r k; out/host/linux-x86/bin/mkbootimg  --kernel kernel/out/kernel_jrdsh77_cu_jb.bin --ramdisk out/target/product/jrdsh77_cu_jb/ramdisk.img --board vS21-0 --output out/target/product/jrdsh77_cu_jb/boot.img'
# alias mlog='adb logcat | /home/manjusaka/bin/coloredlogcat.py'
# alias radiolog='adb logcat -b radio | /home/manjusaka/bin/coloredlogcat.py'
# #alias cpwd='pwd | xsel'
# alias mkmtkboot='bash ~/bin/mk_boot.sh'
# alias mkkmtkboot='bash ~/bin/mk_bootkk.sh'
# #alias reposync='cd version_babyd; git fetch --tags --force; cd -;repo forall -c git checkout -f;repo forall -c git clean -fd;repo forall -c git checout master ;repo sync -j16 -f;'
# #alias cpwd='pwd | xsel'
# alias mkmtkboot='bash ~/bin/mk_boot.sh'
# alias mkkmtkboot='bash ~/bin/mk_bootkk.sh'
# alias mdmake='bash ~/bin/modemmake.sh'
# export GREP_OPTIONS='--color=auto'
# alias mkfastflash='bash ~/bin/flash_fast.sh'
# alias gitadd='bash ~/bin/gitaddm.sh'
# #alias ggat='/home/manjusaka/work_data/oold/debug/gat-linux-x86_64-3.0/gat'
#alias ggat='//media/newdata/mtk_toolss/GAT_v3.1633.2/GAT_exe_v3.1633.2/gat-linux-x86_64-3/gat'


# alias ggat='~/mytools/curent_gat/gat'
#alias ggat='/media/misc_data/GAT_v3.1716.3/GAT_exe_v3.1716.3/gat-linux-x86_64-3/gat'

# alias appins='bash ~/bin/appinstall.sh'
# alias myfgrep='echo "find . \( -path ".*/.*" -o -path "*/out" \) -prune -o -type f -print | xargs grep"; find . \( -path ".*/.*" -o -path "*/out" \) -prune -o -type f -print | xargs grep '
# alias mlpl='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);cd bootable/bootloader/preloader;TARGET_PRODUCT=$PROJ ./build.sh 2>&1;cd -;cp $CURDIRLL/out/target/product/$PROJ/obj/PRELOADER_OBJ/bin/preloader_$PROJ.bin $CURDIRLL/out/target/product/$PROJ/'
# alias mllk='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);cd bootable/bootloader/lk;make -j24 $PROJ;cp ./build-$PROJ/lk.bin $CURDIRLL/out/target/product/$PROJ/;cd -'
# alias myfgrep='echo "find . \( -path ".*/.*" -o -path "*/out" \) -prune -o -type f -print | xargs grep"; find . \( -path ".*/.*" -o -path "*/out" \) -prune -o -type f -print | xargs grep -n'
#alias mlkk='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);make -j16 -C kernel-3.10 O=$CURDIRLL/kernel-3.10/OUT_${PROJ}/ ARCH=arm64 CROSS_COMPILE="ccache $CURDIRLL/prebuilts/gcc/linux-x86/aarch64/cit-aarch64-linux-android-4.9/bin/aarch64-linux-android-" ROOTDIR=$CURDIRLL;cp $CURDIRLL/kernel-3.10/OUT_${PROJ}/arch/arm64/boot/Image.gz-dtb  $CURDIRLL/out/target/product/$PROJ/kernel;make ramdisk-nodeps; make bootimage-nodeps'
# stty -ixon
# alias mmmdcopy='bash ~/bin/modem_copy.sh'
# alias mlmdcopy='perl /home/manjusaka/all_codes/6735l1/device/mediatek/build/build/tools/modemRenameCopy.pl $(pwd)'
# alias mlcmdcopy='perl /home/manjusaka/all_codes/m06735/device/mediatek/build/build/tools/modemRenameCopy.pl $(pwd)'
# alias ml8mdcopy='perl /home/manjusaka/all_codes/ll80/device/mediatek/build/build/tools/modemRenameCopy.pl $(pwd)'
#alias mlcf='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);mkdir kernel-3.10/OUT_$PROJ;cd kernel-3.10;make O=OUT_${PROJ} ${PROJ}_debug_defconfig ARCH=arm64;cd -'

#alias ml8cf='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);mkdir kernel-3.10/OUT_$PROJ;cd kernel-3.10;make O=OUT_${PROJ} ${PROJ}_debug_defconfig ARCH=arm;cd -'
#alias ml8kk='PROJ=$(echo $TARGET_PRODUCT | sed 's/full_//g');CURDIRLL=$(pwd);make -j16 -C kernel-3.10 O=$CURDIRLL/kernel-3.10/OUT_${PROJ}/ ARCH=arm CROSS_COMPILE="ccache $CURDIRLL/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-" ROOTDIR=$CURDIRLL;cp $CURDIRLL/kernel-3.10/OUT_${PROJ}/arch/arm/boot/zImage-dtb  $CURDIRLL/out/target/product/$PROJ/kernel;make ramdisk-nodeps; make bootimage-nodeps'

# alias mlkk='bash ~/bin/mk_l1_kernel.sh'
# alias mykill='bash ~/bin/kill_dev_bin.sh'
# alias myadbp='bash ~/bin/myadbpushall.sh'
# alias mlmddircopy='bash ~/bin/for_modem/auto_copy_temp_modem_to_system_dir.sh'
# alias mmpl='bash ~/bin/mm_make.sh pl'
# alias mmlk='bash ~/bin/mm_make.sh lk'
# alias mmkk='bash ~/bin/mm_make.sh kk'
# alias mmkcf='bash ~/bin/mm_make.sh kconfig'
# alias mymdpush='bash ~/bin/modem_push.sh'
# alias mymdprocopy='bash ~/bin/md_copy_pro.sh'
# alias mmsp='bash ~/bin/mm_sprd_l1.sh'
# alias mlmdmake='bash ~/bin/modem_copy.sh'
#
# alias mtkoldflash1648='cd ~/mytools/fl_1648_2; sudo ./flash_tool'
# alias mtknew_fl_cur_code='cd ~/mytools/fl1904/; sudo ./flash_tool'
# alias mtk1928_fl_cur_code='cd ~/mytools/fl1928/; sudo ./flash_tool'
# alias batpull='sh ~/bin/battery_pull.sh'
# alias rpull='sh ~/bin/battery_rpull.sh'
# alias batvi='sh ~/bin/battery_pull_vi.sh'
# alias batls='adb shell ls -l /sdcard/DCIM/;adb shell ls -l /sdcard/logjlink/;sh ~/bin/battery_cat.sh'
# alias sbatls='adb root;adb shell ls -l /data/ylog/;sh ~/bin/battery_cat.sh'
#export JAVA_HOME=/usr/lib/jvm/java-1.7.0-openjdk-amd64/
#alias jmkc='./makeJlink -a "make copy" -p '
#alias jmk='. ~/bin/jmk_init_project.sh'
#source ~/perl5/perlbrew/etc/bashrc
#export PERLLIB="$PERLLIB:~/perl5//perlbrew/build/perl-5.14.2/perl-5.14.2/lib"
# export PERLLIB="$PERLLIB:./"  ##for per5.26 on ubuntu 18.04.5 to buid  6737n modem
# unset GREP_OPTIONS

# export PATH=/opt/atlassian-plugin-sdk/bin:$PATH
# alias mk82='./makeMtk zh960 r k;mkbootimg --kernel ./out/target/product/zh960/obj/KERNEL_OBJ/kernel_zh960.bin --ramdisk ./out/target/product/zh960/ramdisk.img -o out/target/product/zh960/boot.img'

# alias mk92='./makeMtk j960_mt6592_32_kk r k;mkbootimg --kernel ./out/target/product/j960_mt6592_32_kk/obj/KERNEL_OBJ/kernel_j960_mt6592_32_kk.bin --ramdisk ./out/target/product/j960_mt6592_32_kk/ramdisk.img -o out/target/product/j960_mt6592_32_kk/boot.img'
# alias jj_autoindent='sh ~/bin/code_fix.sh .'
# alias mymake='make -j4 2>&1 | tee cur_full_make_log'

# alias mk92='./makeMtk  j960_mt6592_32_kk r k;mkbootimg --kernel ./out/target/product/j960_mt6592_32_kk/obj/KERNEL_OBJ/kernel_j960_mt6592_32_kk.bin --ramdisk ./out/target/product/j960_mt6592_32_kk/ramdisk.img -o out/target/product/j960_mt6592_32_kk/boot.img'

# alias jppublic="cd /media/4Tdata/source_codes/mtk6592_kk/jlink/version_integration/bsp/tools_bsp/public_project_info/; bash cron_auto_update.sh"


# alias bspmount="sudo mount -t cifs //192.168.8.205/data1/ ~/cur_images/server_ftp/data1 -o username=linhuasheng,password=mobile#3;sudo mount -t cifs //192.168.8.205/data2/ ~/cur_images/server_ftp/data2 -o username=linhuasheng,password=mobile#3;"
# alias jsca="cd ~/mytools/sca/; env LANG=\"zh_CN.UTF-8\" wine ScaConfig.exe"
# alias jm62p="cd ~/all_codes/up0_mtk6762"
# alias jm80n="cd ~/all_codes/nn80"
# alias jm80l="cd ~/all_codes/ll80"
# alias jm80p="cd ~/all_codes/m80p1"
# alias jm37n="cd ~/all_codes/m37n0"
# alias jm65p="cd ~/all_codes/m65p0"
# alias jm82k="cd ~/all_codes/kkmtk6582"
# alias jm92k="cd ~/all_codes/kk_mtk6592"
# alias jm37o="cd ~/all_codes/go1_mtk6737"
# alias jm8163n="cd ~/all_codes/mtk8163_n0"
# alias jmodem="cd ~/all_codes/modem/MTK-modem/MT6762"
# alias jp7731m="cd ~/all_codes/sprd_m0_7731"
# alias jp7730k="cd ~/all_codes/sprd_kk_8830"
# alias jp9820ek="cd ~/all_codes/sprd_kk_9820e"
# alias jp7731o="cd ~/all_codes/sprd_o_7731e"
# alias jp9832m="cd ~/all_codes/sprd_m_9832"

#add for 1804 build android m
# export LC_ALL=C

#for chromium
# export GOOGLE_API_KEY="no"
# export GOOGLE_DEFAULT_CLIENT_ID="no"
# export GOOGLE_DEFAULT_CLIENT_SECRET="no"

#source ~/bin/auto_minicom.sh
# alias jcam_mtkp_meta="mmm vendor/mediatek/proprietary/hardware/mtkcam/utils/metastore/metadataprovider/custom/ 2>&1 | tee _l1 && mmm vendor/mediatek/proprietary/hardware/mtkcam/utils/metastore/metadataprovider/ 2>&1 | tee _l2 && mmm vendor/mediatek/proprietary/hardware/mtkcam/utils/metastore/ 2>&1 | tee logmeta; cat _l1>>logmeta; cat_l2>>logmeta"
# alias jcam_6739_hal="mmm vendor/mediatek/proprietary/hardware/mtkcam/drv/src/sensor/mt6739/custom/ && mmm vendor/mediatek/proprietary/hardware/mtkcam/drv/src/sensor/mt6739/ 2>&1 | tee loghal "
# alias jcam_6765_hal="mmm vendor/mediatek/proprietary/custom/mt6765/hal/imgsensor_src/ 2>&1 | tee _log2 &&mmm vendor/mediatek/proprietary/hardware/mtkcam/drv/src/sensor/mt6765/custom/ 2>&1 | tee _log1 && mmm vendor/mediatek/proprietary/hardware/mtkcam/drv/src/sensor/mt6765/ 2>&1 | tee loghal ; cat _log1 >> loghal; rm _log1; cat _log2 >> loghal; rm _log2"
#libmtkcam_device1.so
# alias jcam_om65dev1="mmm vendor/mediatek/proprietary/hardware/mtkcam/main/hal/device/1.x/ 2>&1 | tee logdev1"
#lib3a
# alias jcam_om65aaa="mmm vendor/mediatek/proprietary/hardware/mtkcam/aaa/source/mt6765/ 2>&1 | tee logaaa"
# alias jcam_cust="mmm vendor/mediatek/proprietary/custom/ 2>&1 | tee logcust" 
# alias jcam_cust_chg_list="mmma vendor/mediatek/proprietary/custom/ 2>&1 | tee logcust" 
#for update vendor/mediatek/proprietary/custom/mt6765/hal/sendepfeature/
# alias jcam_65send="mmm vendor/mediatek/proprietary/hardware/mtkcam/middleware/v1/common/paramsmgr/ 2>&1 | tee logsend"
#
# alias jcam_cam3="mmma vendor/mediatek/proprietary/hardware/mtkcam3 2>&1 | tee logcam3"
#
# alias tjcam_6765_hal="mmm vendor/mediatek/proprietary/custom/mt6765/hal/imgsensor_src/ vendor/mediatek/proprietary/hardware/mtkcam/drv/src/sensor/mt6765/ 2>&1 | tee loghal"
#
#
# alias jrkk="make ARCH=arm64 BOOT_IMG=../rockdev/Image-rkx11_3399_64_q/boot.img rkx11_3399_64_q-sapphire-excavator-edp-avb.img -j8"
# alias rkx11="make ARCH=arm64 BOOT_IMG=../rockdev/Image-rkx11_3399_64_q/boot.img rkx11_3399_64_q-sapphire-excavator-edp-avb.img -j8"

# alias jkill="bash ~/bin/jlink_kill.sh " 
# export PATH=~/.local/bin:$PATH
# alias jrkcameraname='adb shell "grep '' /sys/class/video4linux//video*/name"'
# export LIBDIR=~/bin:$LIBDIR
# alias jforcebabyd="cd version_babyd; git fetch --tags --force; cd -"
# alias batline="python ~/battery/line_top.py "
# alias jrepo="repo init -u git@192.168.8.204:alps/manifest.git -m "
# alias bpull='git pull origin master'
# alias clogcat='coloredlogcat.py '

alias cd11="cd ~/code/rk356x/"
alias c...="cd ../../../"
alias c..="cd ../../"
alias c....="cd ../../../../"
alias c.....="cd ../../../../../"
alias c......='cd ../../../../../../'
alias cd...="cd ../../../"
alias cd..="cd ../../"
alias cd....="cd ../../../../"
alias cd.....="cd ../../../../../"
alias cd......='cd ../../../../../../'
alias reposync='cd version_babyd; git fetch --tags --force; cd -;repo forall -c git checkout -f;repo forall -c git clean -fd; repo sync -j8 -f;'
alias jbuild='cd /home/bsp/all_codes/up0_mtk6762/jlink/version_integration/bsp/tools/build; python t4_main.py;'
alias jmbuild='cd /home/manjusaka/all_codes/up0_mtk6762/jlink/version_integration/bsp/tools/build; python t4_main.py;'
alias jlog="adb shell uptime; adb root; adb shell cat /proc/cmdline; adb shell cat /proc/last_kmsg"
alias jjs="source build/envsetup.sh"
export PS1='\[\e[32;1m\]\u\[\e[32;1m\][\[\e[33;1m\]\A\[\e[32;1m\]]\[\e[35;1m\]:\[\e[34;1m\]\w\[\e[37;1m\]\$\[\e[m\] '"\[\033]0;\W\007\]"
alias treew="tree -fplaDF"
#解决ls中文乱码问题
#  $sudo locale-gen zh_CN.UTF-8
    export LANG=en_US.UTF-8
    export LANGUAGE=
    export LC_CTYPE="en_US.UTF-8"
    export LC_NUMERIC=zh_CN.UTF-8
    export LC_TIME=zh_CN.UTF-8
    export LC_COLLATE="en_US.UTF-8"
    export LC_MONETARY=zh_CN.UTF-8
    export LC_MESSAGES="en_US.UTF-8"
    export LC_PAPER=zh_CN.UTF-8
    export LC_NAME=zh_CN.UTF-8
    export LC_ADDRESS=zh_CN.UTF-8
    export LC_TELEPHONE=zh_CN.UTF-8
    export LC_MEASUREMENT=zh_CN.UTF-8
    export LC_IDENTIFICATION=zh_CN.UTF-8
    export LC_ALL=
