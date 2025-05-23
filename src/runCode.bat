@echo off
setlocal enabledelayedexpansion

echo Compiling project with caching...

:: Create build directory if it doesn't exist
if not exist "build" (
    mkdir build
)

:: Compile each .cpp to .o only if it's newer than its .o file
for %%f in (*.cpp) do (
    set "cpp=%%f"
    set "obj=build\%%~nf.o"

    if not exist "!obj!" (
        echo Compiling: !cpp!
        g++ -c "!cpp!" -o "!obj!"
    ) else (
        for %%i in (!cpp!) do set "cppTime=%%~ti"
        for %%i in (!obj!) do set "objTime=%%~ti"

        if "!cppTime!" GTR "!objTime!" (
            echo Recompiling: !cpp!
            g++ -c "!cpp!" -o "!obj!"
        ) else (
            echo Up-to-date: !cpp!
        )
    )
)

:: Link all .o files into the final executable
echo Linking object files...
g++ build\*.o -o hostelManagement

if %errorlevel% neq 0 (
    echo Linking failed!
    pause
    exit /b %errorlevel%
)

echo Build successful! Output: hostelManagement.exe
pause
