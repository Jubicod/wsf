@REM send binary data to tutorial application
@REM for example : send 5331320A will send 'S12' 
@REM for example : send 5331320A540A will send 'S12' followed by 'R'

@echo off 

if not "%~1" == "" goto debugFile 

@echo on 

..\settings\example.Debug.cspy.bat

@echo off 
goto end 

:debugFile 

@echo off 

echo %1> temp.txt
certutil -f -decodehex temp.txt temp.bin
..\settings\example.Debug.cspy.bat < temp.bin

:end