@echo off
setlocal enabledelayedexpansion

echo [🔧] Compiling project with smart rebuild...

:: Paths
set "OUTDIR=src\build"
set "SRCDIR=src"
set "DBDIR=Database"
set "EXE=src\hostelManagement.exe"

:: Create build directory if missing
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

:: Recurse through all .cpp files in src/ and Database/
for /R %%f in (%SRCDIR%\*.cpp %DBDIR%\*.cpp) do (
    set "srcfile=%%f"
    set "objfile=%OUTDIR%\%%~nf.o"

    if not exist "!objfile!" (
        echo [🛠️] Compiling: !srcfile!
        g++ -std=c++17 -c "!srcfile!" -o "!objfile!"
    ) else (
        for %%i in (!srcfile!) do set "cppTime=%%~ti"
        for %%i in (!objfile!) do set "objTime=%%~ti"
        if "!cppTime!" GTR "!objTime!" (
            echo [🔄] Recompiling: !srcfile!
            g++ -std=c++17 -c "!srcfile!" -o "!objfile!"
        ) else (
            echo [✅] Up-to-date: !srcfile!
        )
    )
)

:: Link all object files
echo [📦] Linking...
g++ %OUTDIR%\*.o -o %EXE%

if %errorlevel% neq 0 (
    echo [❌] Linking failed!
    pause
    exit /b %errorlevel%
)

echo [🚀] Build successful. Running: hostelManagement.exe
echo ---------------------------------------------------
%EXE%
pause
