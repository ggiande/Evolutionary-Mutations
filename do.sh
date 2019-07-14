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
python3 TestingAnalysis.py
echo
echo "Python script executed."
echo
echo
#echo "Compressing images to video."
cd ~/Desktop/Sim/images
#sudo ffmpeg -r 60 -f image2 -start_number 0 -i test%01d.png -vcodec libx264 -crf 25  -pix_fmt yuv444p ../Preview.mov
echo
echo
echo "Completed all processes."