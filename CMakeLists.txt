cmake_minimum_required(VERSION 3.8)

###################
#                 #
# Variables setup #
#                 #
###################

set(WHACK_A_STOODENT_SERVER_PROJECT "WhackAStoodentServer")
if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/dependencies")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/dependencies")

###########
#         #
# Project #
#         #
###########

project(${WHACK_A_STOODENT_SERVER_PROJECT})

##################
#                #
# Compiler check #
#                #
##################

if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	message(FATAL_ERROR
		"${WHACK_A_STOODENT_SERVER_PROJECT} only supports the Clang compiler.\n"
		"Please use Clang to build this project."
	)
endif()

################
#              #
# Dependencies #
#              #
################

add_subdirectory("dependencies")

###########################
#                         #
# Whack-A-Stoodent server #
#                         #
###########################

add_executable(${WHACK_A_STOODENT_SERVER_PROJECT} "")

add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("dependencies/enet")

set_property(TARGET ${WHACK_A_STOODENT_SERVER_PROJECT} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${WHACK_A_STOODENT_SERVER_PROJECT} PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(${WHACK_A_STOODENT_SERVER_PROJECT} PUBLIC "include")

####################################
#                                  #
# Find and link packages to target #
#                                  #
####################################

#find_package(enet 1.3.17 REQUIRED)
find_package(nlohmann_json 1.3.17 REQUIRED)

# stduuid from conan.io is broken, because GSL has issues
# find_package(stduuid 1.0 REQUIRED)
target_include_directories(${WHACK_A_STOODENT_SERVER_PROJECT} PUBLIC "dependencies/stduuid/include")
target_include_directories(${WHACK_A_STOODENT_SERVER_PROJECT} PUBLIC "dependencies/enet")

if (WIN32)
	target_link_libraries(${WHACK_A_STOODENT_SERVER_PROJECT} PUBLIC
		winmm
		ws2_32
	)
endif()

unset(WHACK_A_STOODENT_SERVER_PROJECT)
