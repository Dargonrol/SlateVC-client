@echo off
setlocal enabledelayedexpansion

echo === Installing Conan dependencies for Windows ===

:: Windows 64-Bit
echo --^> Windows x64 (Debug ^& Release)...
conan install . -pr:h=./conan/profiles/windows-x64-msvc -s build_type=Debug -of=build/windows-x64 -b=missing
if %errorlevel% neq 0 exit /b %errorlevel%

conan install . -pr:h=./conan/profiles/windows-x64-msvc -s build_type=Release -of=build/windows-x64 -b=missing
if %errorlevel% neq 0 exit /b %errorlevel%

:: Windows 32-Bit | uncomment for 32-bit builds
::echo --^> Windows x86 (Debug ^& Release)...
::conan install . -pr:h=./conan/profiles/windows-x86-msvc -s build_type=Debug -of=build/windows-x86 -b=missing
::if %errorlevel% neq 0 exit /b %errorlevel%

::conan install . -pr:h=./conan/profiles/windows-x86-msvc -s build_type=Release -of=build/windows-x86 -b=missing
::if %errorlevel% neq 0 exit /b %errorlevel%

echo === Done! You can now use your IDE or 'cmake --preset ^<preset^>' ===