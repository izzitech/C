@echo off 

mkdir .\build
pushd .\build
pwd
cl ..\winMain.c /nologo /wd4047 /wd4024 /wd4028 /wd4133
popd