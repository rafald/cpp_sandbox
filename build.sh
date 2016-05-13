echo
echo ./build.sh --boost-root=/home/raf12/develop/c++/boost
echo BOOST_ROOT=~/develop/c++/boost ./build.sh
echo 
bjam -d2 -j4 --dump-tests $@
