cmake_minimum_required(VERSION 3.15.4)

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

# require opengl
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

# for #include "stdafx.h"
include_directories(../../source/common)

# window system
if (WIN32)
	set(window windows)
	set(srcdir ${srcdir} ../../source/engine/driver/direct3d)
	set(srcdir ${srcdir} ../../source/engine/window/windows)
elseif(UNIX)
	set(window x)
	set(srcdir ${srcdir} ../../source/engine/window/x)
elseif(APPLE)
	set(window osx)
	set(srcdir ${srcdir} ../../source/engine/window/osx)
endif ()
include_directories("../../source/window/${window}")

# gbEngine 源文件目录
set(srcdir
	../../source/common
	../../source/engine/core
	../../source/engine/driver/opengl
	../../source/engine/env
	../../source/engine/math
	../../source/engine/window
)

foreach(dir ${srcdir})
	aux_source_directory(${dir} gbEngine_SOURCE)	
endforeach(dir)
message(STATUS "======== [source files] ========")
	messages(${gbEngine_SOURCE})
message(STATUS "================================")

add_library(gbEngine SHARED ${gbEngine_SOURCE})

# demo-basic