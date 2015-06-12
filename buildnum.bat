@echo off
REM increase build number
set /p build= < buildnum.h > nul:
set build=%build:* =%
set build=%build:* =%
set build=%build:*      =%
set build=%build:*      =%
set /a build=build+1
set cdate=%DATE%
set cdate=%cdate:* =%
set ctime=%TIME%
set ctime=%ctime:~0,5%
echo #define BUILD_NUM %build% > buildnum.h
echo #define BUILD_DATE _T("%cdate: =% %ctime: =0%") >> buildnum.h
