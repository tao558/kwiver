#!/bin/sh
set -e

# Make a directory for cmake binaries
mkdir -p $HOME/cmake_install
cd $HOME/cmake_install
wget https://cmake.org/files/v3.15/cmake-3.15.7-Linux-x86_64.sh
chmod +x cmake-3.15.7-Linux-x86_64.sh
yes | ./cmake-3.15.7-Linux-x86_64.sh