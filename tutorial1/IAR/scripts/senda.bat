@REM send string (ASCII) to tutorial application
@REM for example : "send S12" will send 'S12' 
@REM for example : "send S12 R" will send 'S12' followed by 'R'


@echo off 

if not "%~1" == "" goto debugFile 

@echo on 

..\settings\example.Debug.cspy.bat

@echo off 
goto end 

:debugFile 

@echo off 


@echo %1>temp.bin
shift
:loop
if "%~1" == "" goto finish
@echo %1>>temp.bin
shift
goto loop

:finish
setlocal
cmd /C ..\settings\example.Debug.cspy.bat  < temp.bin

for /F "tokens=5" %%a in ('findstr /R "^main.[0-9]...[0-9]" fprof.log') do echo total %%a cycles
endlocal
:end