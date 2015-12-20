cmake_minimum_required(VERSION 3.3)
project(tic_tac_toe)

find_package(Boost 1.58 REQUIRED COMPONENTS system regex)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_FILES
        server/main.cpp
        server/Server.cpp
        server/Game.cpp
        server/Room.cpp
        server/Session.cpp
        server/Player.cpp
        shared/GameBoard.cpp)
add_executable(ttt_server ${SERVER_FILES})
target_link_libraries(ttt_server ${Boost_LIBRARIES})

set(CLIENT_FILES
        client/main.cpp
        client/Client.cpp
        client/Interface.cpp
        shared/GameBoard.cpp)
add_executable(ttt_client ${CLIENT_FILES})
target_link_libraries(ttt_client ${Boost_LIBRARIES})
