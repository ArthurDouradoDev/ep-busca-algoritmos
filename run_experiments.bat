@echo off
echo === BASIC LISTA === > results.txt
ep.exe basic.txt lista < input_commands.txt >> results.txt
echo. >> results.txt

echo === BASIC ARVORE === >> results.txt
ep.exe basic.txt arvore < input_commands.txt >> results.txt
echo. >> results.txt

echo === MEDIUM LISTA === >> results.txt
ep.exe medium.txt lista < input_commands.txt >> results.txt
echo. >> results.txt

echo === MEDIUM ARVORE === >> results.txt
ep.exe medium.txt arvore < input_commands.txt >> results.txt
echo. >> results.txt

echo === LONG LISTA === >> results.txt
ep.exe long.txt lista < input_commands.txt >> results.txt
echo. >> results.txt

echo === LONG ARVORE === >> results.txt
ep.exe long.txt arvore < input_commands.txt >> results.txt
echo. >> results.txt