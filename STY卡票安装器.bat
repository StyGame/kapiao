chcp 936
cls
@echo off
title STY卡票安装器
if  exist %SystemDrive%\Flags.txt (
del /f /q %SystemDrive%\Flags.txt
)
cd /d "%~dp0"
color B
setlocal enabledelayedexpansion
FOR /F "TOKENS=*" %%I IN ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Tencent\QQ飞车\Sys" /v "PathRoot"') DO ( SET "GamePath=%%I" )
if "%GamePath%" == "" (
   echo 未能找到飞车安装目录
   goto stop
)

set GamePath=%GamePath:~18%
for /f "tokens=*" %%i in ("%GamePath%") do SET GamePath=%%i

:loop
echo GamePathRoot：%GamePath%
echo 1.安装卡票文件
echo 2.卸载卡票文件
echo 3.直接退出
set /p op=输入操作选项:
if %op% equ 1 (
   copy "%~dp0EventReport.dll" "%GamePath%\Releasephysx27\EventReport.dll"
   echo 安装卡票完成
   goto stop
)  else  (
   if %op% equ 2 (
	   copy "%~dp0EventReport_original.dll" "%GamePath%\Releasephysx27\EventReport.dll"
	   echo 卸载卡票完成
	   goto stop
   )  else  (
       if %op% equ 3 (
	     goto stop
	   )
	   cls
       echo 输入错误
	   echo =================
	   goto loop
   )
)
:stop
echo 按任意键关闭
pause>nul
