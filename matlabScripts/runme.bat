@echo off
echo Kalman runner
::you'll probably need to change this location
set PATH=%PATH%;D:\Programy\Octave-4.0.0

if "%1"=="" goto usage
if "%2"=="" goto usage

app -s %1
octave --silent --eval %2

goto normal_exit

:usage
echo Usage: %0 (python_script_from_map_dir) (matlab_function(arg))
::for example: runme.bat ../maps/standard_acc.py script(1000)
exit /B 1

:normal_exit
exit /B 0