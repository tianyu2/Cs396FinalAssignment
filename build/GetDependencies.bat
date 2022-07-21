@echo OFF
setlocal enabledelayedexpansion
cd %cd%
set GAME_PATH=%cd%

rem --------------------------------------------------------------------------------------------------------
rem Set the color of the terminal to blue with yellow text
rem --------------------------------------------------------------------------------------------------------
COLOR 8E
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore Cyan Welcome I am your GAME dependency updater bot, let me get to work...
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
echo.

:DOWNLOAD_DEPENDENCIES
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White GAME - DOWNLOADING DEPENDENCIES
powershell write-host -fore White ------------------------------------------------------------------------------------------------------

echo.
rmdir "../dependencies/xecs" /S /Q
git clone https://github.com/LIONant-depot/xECS.git "../dependencies/xecs"
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd ../dependencies/xecs
git checkout Lesson09_Prefabs
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd build
call GetDependencies.bat "return"
if %ERRORLEVEL% GEQ 1 goto :ERROR
cd /d %GAME_PATH%


:DONE
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White GAME - DONE!!
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
goto :PAUSE

:ERROR
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------
powershell write-host -fore Red GAME - ERROR!!
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------

:PAUSE
rem if no one give us any parameters then we will pause it at the end, else we are assuming that another batch file called us
if %1.==. pause