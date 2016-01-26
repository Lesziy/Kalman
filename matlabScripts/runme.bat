@echo off
echo Kalman runner

set PATH=%PATH%;C:\Octave\Octave-4.0.0

if "%1"=="" goto usage
if "%2"=="" goto usage

app -s %1
octave %2



goto normal_exit

:usage
echo Usage: %0 (python_script_from_map_dir) (matlab_script)
exit /B 1

:normal_exit
exit /B 0
