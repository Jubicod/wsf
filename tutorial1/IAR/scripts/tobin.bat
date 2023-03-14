@REM call tobin.py script

@echo off 

cmd /C python tobin.py %*

..\settings\example.Debug.cspy.bat < temp.bin

