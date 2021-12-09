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
for /f "tokens=1,2,3,4,*" %%i in ('reg query "HKLM\SOFTWARE\WOW6432Node\Tencent\QQ飞车\Sys" ^| find /i "PathRoot"') do SET "GamePath=%%k"
if "%GamePath%" == "" (
   echo 未能找到飞车安装目录
   goto stop
)
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