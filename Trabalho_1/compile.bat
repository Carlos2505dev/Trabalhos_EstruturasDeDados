@echo off
echo Compilando o programa...
gcc -Wall -Wextra -std=c99 -o playlist main.c
if %errorlevel% equ 0 (
    echo Compilacao concluida com sucesso!
    echo.
    echo Executando o programa...
    echo.
    playlist.exe
) else (
    echo Erro durante a compilacao!
)
pause
