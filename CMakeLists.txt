cmake_minimum_required(VERSION 3.12)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if (NOT HAS_PARENT)
    project(AVR_Periph)
    add_library(AVR_Periph "")

    if(APPLE)
        include_directories(/usr/local/CrossPack-AVR/include)
    elseif(WIN32)
        include_directories(C://AVR/avr/include)
    else()
        message(WARNING "AVR include directories not set for current operating system")
    endif()
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Accelerometer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IRRangeFinder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ToggleSwitchCollection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LightEmittingDiode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Motor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Servo.cpp)
