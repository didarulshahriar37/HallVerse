@echo off
cd /d "e:\ISLAMIC UNIVERSITY OF TECHNOLOGY\3rd SEMESTER\3-1\SPL\HallVerse\HallVerse"
g++ -std=c++17 -Isrc -Isrc/managers -Isrc/models -Isrc/services -Isrc/utils -O2 -g src/main/Main.cpp src/managers/*.cpp src/models/*.cpp src/services/*.cpp src/utils/*.cpp -o build/HallVerse.exe
echo Compilation complete!
pause
