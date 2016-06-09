cmake_minimum_required(VERSION 3.3)
project(program4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES  classic.cpp classic.h comedy.cpp comedy.h customer.h customer.cpp drama.cpp drama.h history.cpp history.h
        inventory.cpp inventory.h main.cpp movie.cpp movie.h moviestore.cpp moviestore.h transaction.h borrow.h borrow.cpp return.h return.cpp)
add_executable(program4 ${SOURCE_FILES})