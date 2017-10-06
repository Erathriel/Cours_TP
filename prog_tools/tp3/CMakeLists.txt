cmake_minimum_required(VERSION 3.0)

project(Hello)

set( SRCS
	hello_world.cpp
)

message(${CMAKE_SYSTEM_NAME})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_executable(main ${SRCS})
	target_link_libraries(main /afs/deptinfo-st.univ-fcomte.fr/users/gnoro/Documents/Outils_prog/tp3/lib/libDisplayMessage.a)
	target_link_libraries(main /afs/deptinfo-st.univ-fcomte.fr/users/gnoro/Documents/Outils_prog/tp3/dll/libDisplayMessage.so)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_executable(main ${SRCS})
	target_link_libraries(main /afs/deptinfo-st.univ-fcomte.fr/users/gnoro/Documents/Outils_prog/tp3/dll/libDisplayMessage.dll)
else()
	message(FATAL_ERROR "Error")
endif()
