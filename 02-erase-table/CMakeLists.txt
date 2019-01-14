project(erase-table)

cmake_minimum_required(VERSION 3.12)

include_directories(/usr/local/Cellar/eosio.cdt/1.4.1/opt/eosio.cdt/include)
include_directories(/usr/local/include)

add_executable(erase-table erasetable.cpp)