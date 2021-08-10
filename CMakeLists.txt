cmake_minimum_required(VERSION 3.16)
project(AxmlParser)

set(CORE_LIB ${CMAKE_PROJECT_NAME}Core)

add_library(${CORE_LIB}
	AxmlParser.c
	)
target_include_directories(${CORE_LIB}
	INTERFACE 	${CMAKE_CURRENT_SOURCE_DIR}
	)

add_library(${CMAKE_PROJECT_NAME} STATIC
	wrapper/AxmlParser.cpp
	)
target_include_directories(${CMAKE_PROJECT_NAME}
	INTERFACE 	wrapper/AxmlParser.hpp
	)
target_link_libraries(${CMAKE_PROJECT_NAME}
	PRIVATE ${CORE_LIB}
	)