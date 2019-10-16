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

# platform
if (WIN32)
	set(defaultPlatform Windows)
elseif(UNIX)
	set(defaultPlatform X)
elseif(APPLE)
	set(defaultPlatform OSX)
endif ()
set(platform ${defaultPlatform} CACHE STRING
  "select platform for build target")
set_property(
	CACHE platform PROPERTY STRINGS
	Windows X OSX Qt Android iOS Wasm
)
message(STATUS "!!!! Target platform: ${platform} !!!!")

# renderer
set(renderer "OpenGL" CACHE STRING "select renderer")
set_property(
	CACHE renderer PROPERTY STRINGS
	"OpenGL" "Direct3D"
)
message(STATUS "!!!! Renderer: ${renderer} !!!!")
message(STATUS "--------------------------------------------------------")

message(STATUS "**************** [module] build gbEngine ****************")
if (${renderer} STREQUAL "OpenGL")
	find_package(OpenGL REQUIRED)
	include_directories(${OpenGL_INCLUDE_DIRS})
	link_directories(${OpenGL_LIBRARY_DIRS})
	add_definitions(${OpenGL_DEFINITIONS})
elseif (${renderer} STREQUAL "Direct3D")
	# 
endif()

include_directories("../../source/platform/${platform}")
include_directories("../../source/engine/${platform}")
include_directories("../../source/common")		# for source code #include "stdafx.h"

# gbEngine 源文件目录
set(srcdir
	../../source/common
	../../source/engine/core
	../../source/engine/driver
	../../source/engine/driver/${renderer}
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
add_library(gbEngine SHARED ${gbEngine_SOURCE})

if (${platform} STREQUAL Windows)
elseif (${platform} STREQUAL X)
	set(libs ${libs} X11)
elseif (${platform} STREQUAL OSX)
elseif (${platform} STREQUAL Android)
elseif (${platform} STREQUAL iOS)
elseif (${platform} STREQUAL Qt)
elseif (${platform} STREQUAL Wasm)
endif()

if (${renderer} STREQUAL OpenGL)
	set(libs ${libs} GL)
elseif (${renderer} STREQUAL Direct3D)
endif()
message(STATUS "======== [libraries] ========")
messages(${libs})

target_link_libraries(gbEngine ${libs})

# demo-basic
message(STATUS "**************** [module] demo basic ****************")
aux_source_directory(../../source/demo/basic demo_basic_SOURCE)
add_executable(demo-basic ${demo_basic_SOURCE})
target_link_libraries(demo-basic gbEngine)

message(STATUS "********************************")