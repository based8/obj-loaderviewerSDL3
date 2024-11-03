#!/bin/bash

export SDL_VIDEODRIVER=x11
export LD_LIBRARY_PATH="$(pwd)/libs"
echo $LD_LIBRARY_PATH
echo $SDL_VIDEODRIVER
./window
