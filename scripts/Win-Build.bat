@echo off
call D:\Softwares\VS19\VC\Auxiliary\Build\vcvars64.bat
cd ..
msbuild RayTracer.sln /p:Platform=x64 /p:Configuration=Debug
PAUSE