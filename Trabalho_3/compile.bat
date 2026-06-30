@echo off
echo Compilando o Gerenciador de Fila de Impressao...
gcc -Wall -Wextra -std=c99 -o impressao main.c
if %errorlevel% equ 0 (
    echo Compilacao concluida com sucesso!
    echo.
    echo Executando o programa...
    echo.
    impressao.exe
) else (
    echo Erro durante a compilacao!
)
pause
