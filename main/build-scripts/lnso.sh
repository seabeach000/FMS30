#!/bin/sh

# 由.so.x自动创建.so软连接
ls *.so.* | while read line
do
	eval $(echo $line | awk -F '\\.so\\.' '{ print "n1="$1 }')
	ln -rs $line "${n1}.so"
done
