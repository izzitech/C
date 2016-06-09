@echo off 
mkdir .\build
pushd .\build
cl winMain.c /link ? /nologo
popd .\