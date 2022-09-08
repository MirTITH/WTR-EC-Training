cmake_minimum_required(VERSION 3.12)

project(multi_files_project) # 项目名称

add_executable(${PROJECT_NAME}
	main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
	.
)
