cmake_minimum_required(VERSION 3.10)
project(vss_software)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") 

find_package(Boost REQUIRED COMPONENTS system)
find_package(CGAL REQUIRED)

include_directories("include"
                    "${CMAKE_SOURCE_DIR}/ext/RxCpp/Rx/v2/src"
                    "${CMAKE_SOURCE_DIR}/ext/json/include"
                    ${Boost_INCLUDE_DIRS})

set(SRCS
    "src/io/serial_message.cc"
    "src/io/serial_sender.cc"
    "src/system/ball.cc"
    "src/system/robot.cc"
    "src/system/system.cc")

add_library(vss_software_srcs
            ${SRCS})

add_executable(vss_software "src/main.cpp")

target_link_libraries(vss_software
                    vss_software_srcs
                    CGAL::CGAL
                    ${Boost_LIBRARIES})