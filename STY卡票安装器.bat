chcp 936
cls
@echo off
title STY��Ʊ��װ��
if  exist %SystemDrive%\Flags.txt (
del /f /q %SystemDrive%\Flags.txt
)
cd /d "%~dp0"
color B
setlocal enabledelayedexpansion
FOR /F "TOKENS=*" %%I IN ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Tencent\QQ�ɳ�\Sys" /v "PathRoot"') DO ( SET "GamePath=%%I" )
if "%GamePath%" == "" (
   echo δ���ҵ��ɳ���װĿ¼
   goto stop
)

set GamePath=%GamePath:~18%
for /f "tokens=*" %%i in ("%GamePath%") do SET GamePath=%%i

:loop
echo GamePathRoot��%GamePath%
echo 1.��װ��Ʊ�ļ�
echo 2.ж�ؿ�Ʊ�ļ�
echo 3.ֱ���˳�
set /p op=�������ѡ��:
if %op% equ 1 (
   copy "%~dp0EventReport.dll" "%GamePath%\Releasephysx27\EventReport.dll"
   echo ��װ��Ʊ���
   goto stop
)  else  (
   if %op% equ 2 (
	   copy "%~dp0EventReport_original.dll" "%GamePath%\Releasephysx27\EventReport.dll"
	   echo ж�ؿ�Ʊ���
	   goto stop
   )  else  (
       if %op% equ 3 (
	     goto stop
	   )
	   cls
       echo �������
	   echo =================
	   goto loop
   )
)
:stop
echo ��������ر�
pause>nul