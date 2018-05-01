#!/bin/bash

if [ -d "build" ]; then
    rm -r build
fi

mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DQT_PLUGIN_INSTALL_DIR=`kf5-config --qt-plugins`
make
sudo make install
kquitapp5 krunner
kstart5 krunner
