@echo on
rem Usage: build_elog <version> like "build 100"
rem Build ELOG distribution

set version=%1

cd nt
nmake -f elog.mak CFG="elog - Win32 Release"
nmake -f elogd.mak CFG="elogd - Win32 Release"
nmake -f elconv.mak CFG="elconv - Win32 Release"
cd ..

"\program files\NSIS\makensis" /DVERSION=%version% elog.nsi

scp elog%version%.exe midas@midas:html/elog/download/windows/
scp elog%version%.exe midas@midas:html/elog/download/windows/elog-latest.exe

