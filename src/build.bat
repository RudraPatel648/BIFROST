@echo off
chcp 65001 >nul
del bifrost.exe 2>nul

g++ main.cpp Graph.cpp -o bifrost

if %errorlevel% neq 0 exit /b

.\bifrost.exe