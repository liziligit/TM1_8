#!/bin/bash
g++ -o 1frame_pd1Draw2DX0 1frame_pd1Draw2DX0.cpp -pthread -m64 -I/opt/root/include -L/opt/root/lib -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic 
#-L/usr/lib/i386-linux-gnu -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic
