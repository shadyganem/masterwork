@echo off
set sourcePath=C:\dev\cpp\masterwork\vs\bin\x64\Release\masterwork.exe
set destinationPath=C:\masterwork\masterwork.exe

echo Copying file...
copy /Y "%sourcePath%" "%destinationPath%"

if errorlevel 1 (
    echo Error occurred during copy.
) else (
    echo File copied successfully.
)