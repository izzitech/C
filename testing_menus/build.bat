@echo off 

mkdir .\build
pushd .\build
pwd
cl ..\winMain.c /nologo
popd