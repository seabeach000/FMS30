#!/bin/sh

# 判断系统
if [ -f '/etc/centos-release' ]; then
	export destos='centos'
elif [ -f '/etc/lsb-release' ]; then
	export destos='ubuntu'
else
	echo '不支持的编译环境！' && exit 1
fi
if [ $destos = 'centos' ]; then
	udevno='1.6.2'
elif [ $destos ]; then
	udevno='1.6.5'
else
	echo '不支持的编译环境！' && exit 1
fi

# 清理
rm -rf '../build'
rm -rf '../dependencies64/boost/boost'
rm -rf '../dependencies64/boost/stage/lib/linux'
rm -f '../dependencies64/cef/bin/linux/libcef.so'
rm -f '../dependencies64/cef/bin/linux/libudev.so'
rm -f '../dependencies64/cef/bin/linux/libudev.so.0'
rm -f '../dependencies64/cef/bin/linux/libudev.so.1'
rm -f '../dependencies64/cef/lib/linux/libcef.so'
rm -f "../dependencies64/cef/lib/linux/libudev.so.${udevno}"
rm -f '../dependencies64/cef/lib/linux/libudev.so'
rm -f '../dependencies64/cef/lib/linux/libudev.so.0'
rm -f '../dependencies64/cef/lib/linux/libudev.so.1'
rm -rf '../dependencies64/ffmpeg/bin/linux'
rm -rf '../dependencies64/ffmpeg/include'
rm -rf '../dependencies64/ffmpeg/lib/linux'
rm -rf '../dependencies64/freeimage/bin/linux'
rm -rf '../dependencies64/freeimage/include'
rm -rf '../dependencies64/freeimage/lib/linux'
rm -rf '../dependencies64/glew/bin/linux'
rm -rf '../dependencies64/glew/include'
rm -rf '../dependencies64/glew/lib/linux'
rm -rf '../dependencies64/gtest/include'
rm -rf '../dependencies64/gtest/lib/linux'
rm -rf '../dependencies64/ldkdog/bin/linux'
rm -rf '../dependencies64/mainconcept/bin/linux'
rm -rf '../dependencies64/mainconcept/include'
rm -rf '../dependencies64/openal/bin/linux'
rm -rf '../dependencies64/openal/lib/linux'
rm -rf '../dependencies64/sfml/include'
rm -rf '../dependencies64/sfml/lib/linux'
rm -rf '../dependencies64/tbb/bin/linux'
rm -rf '../dependencies64/tbb/include'
rm -rf '../dependencies64/tbb/lib/linux'
rm -f '../common/CMakeLists.txt'
rm -f '../modules/ffmpeg/CMakeLists.txt'
find "../dependencies64/ffmpeg/bin/${destos}" -type l -exec rm -rf {} \;
find "../dependencies64/freeimage/lib/${destos}" -type l -exec rm -rf {} \;
find "../dependencies64/glew/lib/${destos}" -type l -exec rm -rf {} \;
find '../dependencies64/mainconcept/lib/linux' -type l -exec rm -rf {} \;
find "../dependencies64/openal/lib/${destos}" -type l -exec rm -rf {} \;
find "../dependencies64/tbb/lib/${destos}" -type l -exec rm -rf {} \;
if [ $# -eq 1 ]; then
	if [ $1 = 'clean' ]; then
		exit 0
	fi
fi

# dependencies64自动匹配, 动态库依赖于系统, 静态库可以通用
if [ $destos = 'centos' ]; then
	ln -rs "../dependencies64/boost/boost-${destos}" '../dependencies64/boost/boost'
else
	ln -rs '../dependencies64/boost/boost-win' '../dependencies64/boost/boost'
fi
ln -rs "../dependencies64/boost/stage/lib/${destos}" '../dependencies64/boost/stage/lib/linux'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so.0'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so.1'
ln -rs '../dependencies64/cef/bin/linux/libcef.so' '../dependencies64/cef/lib/linux/libcef.so'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" "../dependencies64/cef/lib/linux/libudev.so.${udevno}"
ln -rs '../dependencies64/cef/bin/linux/libudev.so' '../dependencies64/cef/lib/linux/libudev.so'
ln -rs '../dependencies64/cef/bin/linux/libudev.so.0' '../dependencies64/cef/lib/linux/libudev.so.0'
ln -rs '../dependencies64/cef/bin/linux/libudev.so.1' '../dependencies64/cef/lib/linux/libudev.so.1'
ln -rs "../dependencies64/ffmpeg/bin/${destos}" '../dependencies64/ffmpeg/bin/linux'
ln -rs "../dependencies64/ffmpeg/include-${destos}" '../dependencies64/ffmpeg/include'
ln -rs '../dependencies64/ffmpeg/bin/linux' '../dependencies64/ffmpeg/lib/linux'
ln -rs '../dependencies64/freeimage/lib/linux' '../dependencies64/freeimage/bin/linux'
if [ $destos = 'centos' ]; then
	ln -rs "../dependencies64/freeimage/include-${destos}" '../dependencies64/freeimage/include'
else
	ln -rs '../dependencies64/freeimage/include-win' '../dependencies64/freeimage/include'
fi
ln -rs "../dependencies64/freeimage/lib/${destos}" '../dependencies64/freeimage/lib/linux'
ln -rs '../dependencies64/glew/lib/linux' '../dependencies64/glew/bin/linux'
if [ $destos = 'centos' ]; then
	ln -rs "../dependencies64/glew/include-${destos}" '../dependencies64/glew/include'
else
	ln -rs '../dependencies64/glew/include-win' '../dependencies64/glew/include'
fi
ln -rs "../dependencies64/glew/lib/${destos}" '../dependencies64/glew/lib/linux'
if [ $destos = 'centos' ]; then
	ln -rs "../dependencies64/gtest/include-${destos}" '../dependencies64/gtest/include'
else
	ln -rs '../dependencies64/gtest/include-win' '../dependencies64/gtest/include'
fi
ln -rs "../dependencies64/gtest/lib/${destos}" '../dependencies64/gtest/lib/linux'
ln -rs '../dependencies64/ldkdog/lib/linux' '../dependencies64/ldkdog/bin/linux'
ln -rs '../dependencies64/mainconcept/lib/linux' '../dependencies64/mainconcept/bin/linux'
ln -rs '../dependencies64/mainconcept/include-centos' '../dependencies64/mainconcept/include'
ln -rs '../dependencies64/openal/lib/linux' '../dependencies64/openal/bin/linux'
ln -rs "../dependencies64/openal/lib/${destos}" '../dependencies64/openal/lib/linux'
ln -rs '../dependencies64/sfml/include-centos' '../dependencies64/sfml/include'
ln -rs "../dependencies64/sfml/lib/${destos}" '../dependencies64/sfml/lib/linux'
ln -rs '../dependencies64/tbb/lib/linux' '../dependencies64/tbb/bin/linux'
if [ $destos = 'centos' ]; then
	ln -rs "../dependencies64/tbb/include-${destos}" '../dependencies64/tbb/include'
else
	ln -rs '../dependencies64/tbb/include-win' '../dependencies64/tbb/include'
fi
ln -rs "../dependencies64/tbb/lib/${destos}" '../dependencies64/tbb/lib/linux'
ln -rs "../common/CMakeLists.txt.${destos}" '../common/CMakeLists.txt'
ln -rs "../modules/ffmpeg/CMakeLists.txt.${destos}" '../modules/ffmpeg/CMakeLists.txt'
cd "../dependencies64/ffmpeg/bin/${destos}"
../../../../build-scripts/lnso.sh
cd "../../../freeimage/lib/${destos}"
../../../../build-scripts/lnso.sh
cd "../../../glew/lib/${destos}"
../../../../build-scripts/lnso.sh
cd '../../../mainconcept/lib/linux'
../../../../build-scripts/lnso.sh
cd "../../../openal/lib/${destos}"
../../../../build-scripts/lnso.sh
cd "../../../tbb/lib/${destos}"
../../../../build-scripts/lnso.sh
cd '../../../../build-scripts'

export BUILD_ARCHIVE_NAME='famous'
export BUILD_PARALLEL_THREADS=12

./build-linux.sh
