#!/usr/bin/env fish
#!/usr/bin/env bash

echo
echo ./build.sh --boost-root=/home/raf12/develop/c++/boost
echo BOOST_ROOT=~/develop/c++/boost ./build.sh
echo 
#bjam -j$nproc --dump-tests $@
env toolset= bjam -j$nproc --dump-tests $argv
