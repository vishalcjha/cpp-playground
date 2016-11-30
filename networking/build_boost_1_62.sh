#!/bin/bash
if [ ! -f ./boost_1_62_0.tar.gz ]; then
  echo "Get boost_1_62_0.tar.gz from sourceforge..."
  wget -O boost_1_62_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.62.0/boost_1_62_0.tar.gz
fi

if [ ! -d ./1.62.0 ]; then
  tar -xzf boost_1_62_0.tar.gz
  mv boost_1_62_0 1.62.0
fi

cd 1.62.0
./bootstrap.sh --with-libraries=chrono,date_time,log,system,thread,filesystem,iostreams,regex,serialization,program_options --prefix=./
./b2 --prefix=./ cxxflags=-fPIC variant=release link=static threading=multi install
cd ..
ln -sf 1.62.0 boost
