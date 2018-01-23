#!/bin/bash
if [ -z $1 ];then
echo "should be ./test.sh filename"
exit -1
fi
SUM=`md5sum $1`
echo ${SUM}
./testota ${SUM} "http://192.168.36.193:8000/${1}"
cat latest.json
echo  ""
