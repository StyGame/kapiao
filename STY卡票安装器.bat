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
for /f "tokens=1,2,3,4,*" %%i in ('reg query "HKLM\SOFTWARE\WOW6432Node\Tencent\QQ�ɳ�\Sys" ^| find /i "PathRoot"') do SET "GamePath=%%k"
if "%GamePath%" == "" (
   echo δ���ҵ��ɳ���װĿ¼
   goto stop
)
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