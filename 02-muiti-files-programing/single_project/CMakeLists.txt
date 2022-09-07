cmake_minimum_required(VERSION 3.12)

project(multi_files_project) # 项目名称

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS false)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
	main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
	.
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	# 对 MSVC 开启 utf-8 支持
	"$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>"
	"$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	m
)

target_link_options(${PROJECT_NAME} PRIVATE
	# -static
)
