cmake_minimum_required(VERSION 3.1)
project(KoiRemastered)
set(CMAKE_CXX_STANDARD 11)

add_executable(
	koi
	main.cpp
	utils.cpp
	lexer.cpp
)

target_link_libraries(
	koi
	icuuc
	icui18n
	icudata
	icuio
)
