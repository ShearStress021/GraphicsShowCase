@echo off

set "BUILD=build"

if exist "%BUILD%\" (
	echo "%BUILD" exists

)else (
	mkdir "%BUILD%" || exit /b 1
	cmake -B "%BUILD%" 

)

cmake --build "%BUILD%"  || exit /b 1

"%BUILD%\res.exe"
exit /b 1

