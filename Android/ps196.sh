##########################################################################
# File Name: ps196.sh
# Author: lvyuanye
# mail: lvyy@ktc.cn
# Created Time: Wed 11 Sep 2024 08:49:31 AM CST
#########################################################################
#!/bin/zsh
PATH=/home/lvyy/bin:/home/lvyy/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin
export PATH

while true
do
	echo "=================ps196_read_start=============== "
	echo -n "ps196_0x001f = "
	i2ctransfer -y -f 7 w2@0x08 0x00 0x1f r2
	echo -n "ps196_0x0025 = "
	i2ctransfer -y -f 7 w2@0x08 0x00 0x25 r2
	echo -n "ps196_0x3332 = "
	i2ctransfer -y -f 7 w2@0x08 0x03 0x32 r2
	echo -n "ps196_0x0338 = "
	i2ctransfer -y -f 7 w2@0x08 0x03 0x38 r8
	echo "=================ps196_read_end================= "

	sleep 1s

done
