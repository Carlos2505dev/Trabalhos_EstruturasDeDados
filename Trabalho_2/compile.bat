@echo off
echo Compilando o Simulador de Navegador...
gcc -Wall -Wextra -std=c99 -o navegador main.c
if %errorlevel% equ 0 (
    echo Compilacao concluida com sucesso!
    echo.
    echo Executando o programa...
    echo.
    navegador.exe
) else (
    echo Erro durante a compilacao!
)
pause
