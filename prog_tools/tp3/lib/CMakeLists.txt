cmake_minimum_required(VERSION 3.0)

set(SRCS
    DisplayMessage.cpp
    )
    
set(HEADERS
    DisplayMessage.h
    )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions(-D _SYSTEM_LINUX=${CMAKE_SYSTEM_NAME})
	add_library(DisplayMessage STATIC ${SRCS} ${HEADERS})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_definitions(-D _SYSTEM_WINDOWS=${CMAKE_SYSTEM_NAME})
	add_library(DisplayMessage STATIC ${SRCS} ${HEADERS})
else()
	message(FATAL_ERROR "Error")
endif()