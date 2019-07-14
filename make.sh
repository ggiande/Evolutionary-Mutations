#!/usr/bin/env bash
echo
echo "BEGINNING OF TRANSMISSION"
echo "Commencing the compilation of main2.cpp"
echo
cd ~/Desktop/Sim/
g++ -std=c++11 main2.cpp -o stepstone2.out
echo
echo "Compiled... now opening file extension ./stepstone2.out"
echo
./stepstone2.out
echo
echo "Extension opened, now running Analysis.py, expect images to save or open."
echo
python3 Analysis.py
echo
echo "Python script executed."
echo "END OF TRANSMISSION"
echo