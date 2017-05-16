@echo off

:: 说明
echo 在cmd运行set-variables-and-build-windows.bat windev为vs界面编译生成链接
echo 在cmd运行set-variables-and-build-windows.bat sln为vs界面编译重新生成解决方案
echo 在cmd运行set-variables-and-build-windows.bat clean为打包源码清理解决方案
echo 在cmd运行set-variables-and-build-windows.bat快速编译并打包famous

:: 清理
echo %1 | findstr clean >nul
if %errorlevel% equ 0 (set v=1) else (set v=0)
echo %1 | findstr sln >nul
if %errorlevel% equ 0 (set sln=1) else (set sln=0)
echo %1 | findstr windev >nul
if %errorlevel% equ 0 (set windev=1) else (set windev=0)
if %windev% equ 1 goto :step0
if exist ..\build rd /q /s ..\build
if exist ..\dependencies64\boost\stage\lib\win32\libboost_wave-vc140-mt-gd-1_59.lib del /f /q ..\dependencies64\boost\stage\lib\win32\libboost_wave-vc140-mt-gd-1_59.lib
if exist ..\dependencies64\cef\bin\win32\libcef.dll.pdb del /f /q ..\dependencies64\cef\bin\win32\libcef.dll.pdb
:step0
if exist ..\dependencies64\boost\boost rd /q /s ..\dependencies64\boost\boost
if exist ..\dependencies64\ffmpeg\include rd /q /s ..\dependencies64\ffmpeg\include
if exist ..\dependencies64\freeimage\include rd /q /s ..\dependencies64\freeimage\include
if exist ..\dependencies64\glew\include rd /q /s ..\dependencies64\glew\include
if exist ..\dependencies64\gtest\include rd /q /s ..\dependencies64\gtest\include
if exist ..\dependencies64\mainconcept\include rd /q /s ..\dependencies64\mainconcept\include
if exist ..\dependencies64\sfml\include rd /q /s ..\dependencies64\sfml\include
if exist ..\dependencies64\tbb\include rd /q /s ..\dependencies64\tbb\include
if exist ..\common\CMakeLists.txt del /f /q ..\common\CMakeLists.txt
if exist ..\modules\ffmpeg\CMakeLists.txt del /f /q ..\modules\ffmpeg\CMakeLists.txt
if %v% equ 1 if exist v.txt del /f /q v.txt
if %v% equ 1 goto :eof

:: dependencies64自动匹配
cd ..\dependencies64\boost
mklink /j boost boost-win
cd ..\ffmpeg
mklink /j include include-win
cd ..\freeimage
mklink /j include include-win
cd ..\glew
mklink /j include include-win
cd ..\gtest
mklink /j include include-win
cd ..\mainconcept
mklink /j include include-win
cd ..\sfml
mklink /j include include-win
cd ..\tbb
mklink /j include include-win
cd ..\..\common
copy CMakeLists.txt.centos CMakeLists.txt
cd ..\modules\ffmpeg
copy CMakeLists.txt.centos CMakeLists.txt
cd ..\..\build-scripts
if %windev% equ 1 goto :eof

:: 读取路径, setlocal EnableDelayedExpansion, endlocal
set fn=vcvarsall.bat
set v=""
if exist v.txt for /f "delims=" %%a in ('findstr "\<%fn%\>" v.txt') do set v=%%a
set v=%v:*>=%
echo 读到%fn%为: %v%
if not exist "%v%" echo 搜索%fn%...
if not exist "%v%" for %%a in (c d e f g h i j k l m n o p q r s t u v w x y z) do if exist %%a:\ pushd %%a:\ & (for /r %%b in (*%fn%) do if /i "%%~nxb" equ "%fn%" set v=%%b & echo 搜到%fn%为: %%b) & popd
set BUILD_VCVARSALL=%v%
set fn=7z.exe
set v=""
if exist v.txt for /f "delims=" %%a in ('findstr "\<%fn%\>" v.txt') do set v=%%a
set v=%v:*>=%
echo 读到%fn%为: %v%
if not exist "%v%" echo 搜索%fn%...
if not exist "%v%" for %%a in (c d e f g h i j k l m n o p q r s t u v w x y z) do if exist %%a:\ pushd %%a:\ & (for /r %%b in (*%fn%) do if /i "%%~nxb" equ "%fn%" set v=%%b & echo 搜到%fn%为: %%b) & popd
set BUILD_7ZIP=%v%
echo 路径缓存, 如果手动修改请保持格式且路径中没有换行符>v.txt
echo ^<vcvarsall.bat^>%BUILD_VCVARSALL%>>v.txt
echo ^<7z.exe^>%BUILD_7ZIP%>>v.txt

set BUILD_ARCHIVE_NAME="famous"
set BUILD_PARALLEL_THREADS=12

build-windows.bat

