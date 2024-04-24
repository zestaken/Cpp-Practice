cmake_minimum_required(VERSION 3.27)
project(SpeechManger)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpeechManger src/main.cpp
        src/SpeechManger.cpp
        include/SpeechManger.h
        src/Speaker.cpp
        include/Speaker.h)
