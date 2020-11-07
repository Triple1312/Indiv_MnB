cmake_minimum_required(VERSION 3.16)

project(indiv)

set(CMAKE_CXX_STANDARD 17)

set( Libs libs/json.hpp )

set(src/CYK.cc src/CYK.h)

include_directories(libs)


add_executable(indiv ${Libs} main.cpp src/CYK.cc src/CYK.h src/CFG.cc src/CFG.h libs/PPP.hh src/PDA2CFG.cc src/PDA2CFG.h src/PDA.cc src/PDA.h)