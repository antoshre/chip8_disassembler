cmake_minimum_required(VERSION 3.15)
project(external_deps)

include(FetchContent)

FetchContent_Declare(
		fmt
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)
find_package(fmt QUIET)
if (NOT TARGET fmt)
	message(STATUS "fmt not found, pulling from remote")
	FetchContent_MakeAvailable(fmt)
endif ()

find_package(cppitertools QUIET)
if (NOT TARGET cppitertools)
	message(STATUS "cppitertools not found, pulling from remote")
	set(ENV{cppitertools_INSTALL_CMAKE_DIR} INTERNAL)
	FetchContent_Declare(
			cppitertools
			GIT_REPOSITORY https://github.com/ryanhaining/cppitertools.git
	)
	FetchContent_MakeAvailable(cppitertools)
endif ()

#if (NOT TARGET frozen)
#    FetchContent_Declare(
#            frozen
#            GIT_REPOSITORY https://github.com/serge-sans-paille/frozen.git
#    )
#    FetchContent_MakeAvailable(frozen)
#endif()
#
#if (NOT TARGET ctre)
#	FetchContent_Declare(
#			ctre
#			GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
#	)
#	FetchContent_MakeAvailable(ctre)
#	#CTRE requires C++20
#	target_compile_features(ctre INTERFACE cxx_std_20)
#endif ()