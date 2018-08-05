@echo off
g++ -v -Wwrite-strings -fpermissive -I ../../ -c Lexa.cpp -o lexa.o -Wfatal-errors -Wcpp
PAUSE
g++ -v -Wwrite-strings -c ../../include/download.cpp -o download.o
windres icon.rc icon.o
g++ -v -static -static-libgcc -static-libstdc++ -o Lexa.exe lexa.o download.o icon.o -lcrypt32 -lws2_32 -ldnsapi -lwinmm -lwininet -lopencv_core340.dll -lopencv_highgui340.dll -lopencv_imgproc340.dll -lopencv_imgcodecs340.dll -lopencv_videoio340.dll -lopencv_video340.dll -lboost_system -lboost_serialization -lboost_atomic -lboost_chrono -lboost_thread
PAUSE
rm -v *.o