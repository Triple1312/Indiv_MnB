cmake_minimum_required(VERSION 3.16)

project(indiv)

set(CMAKE_CXX_STANDARD 14)

set( Libs libs/json.hpp )

set(TM src/TM.cc src/TM.h src/State.cc src/State.h src/CYK.cc src/CYK.h)

include_directories(libs)


add_executable(indiv ${Libs} main.cpp ${TM} src/CYK.cc src/CYK.h src/CFG.cc src/CFG.h libs/PPP.hh)