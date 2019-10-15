cmake_minimum_required(VERSION 3.13.4)

project(gbEngine)

set(CMAKE_CXX_STANDARD 14)

# 分行打印列表
function(messages args)
	list(LENGTH ARGV argv_len)
	# message(STATUS "length: ${argv_len}")
	set(i 0)
	while( i LESS ${argv_len})
		list(GET ARGV ${i} argv_value)
		message(STATUS ${argv_value})
		math(EXPR i "${i} + 1")
	endwhile()
endfunction()

message(STATUS "**************** build gbEngine ****************")
# require opengl
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

# for #include "stdafx.h"
include_directories(../../source/common)

# platform
if (WIN32)
	set(platform windows)
	set(srcdir ${srcdir} ../../source/engine/driver/direct3d)
	set(srcdir ${srcdir} ../../source/engine/platform/windows)
elseif(UNIX)
	set(platform x)
	set(srcdir ${srcdir} ../../source/engine/platform/x)
elseif(APPLE)
	set(platform osx)
	set(srcdir ${srcdir} ../../source/engine/platform/osx)
endif ()
message(STATUS "!!!! platform is ${platform} !!!!")
include_directories("../../source/platform/${platform}")

# gbEngine 源文件目录
set(srcdir
	../../source/common
	../../source/engine/core
	../../source/engine/driver
	../../source/engine/driver/opengl
	../../source/engine/driver/direct3d
	../../source/engine/env
	../../source/math
	../../source/platform
	../../source/platform/${platform}
)

foreach(dir ${srcdir})
	aux_source_directory(${dir} gbEngine_SOURCE)	
endforeach(dir)
message(STATUS "======== [source files] ========")
	messages(${gbEngine_SOURCE})
message(STATUS "================================")

add_library(gbEngine SHARED ${gbEngine_SOURCE})
target_link_libraries(gbEngine X11 GLX OpenGL)

# demo-basic
message(STATUS "**************** build demo basic ****************")
aux_source_directory(../../source/demo/basic demo_basic_SOURCE)
add_executable(demo-basic ${demo_basic_SOURCE})
target_link_libraries(demo-basic gbEngine)