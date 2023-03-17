cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

option(BUILD_SHARED_LIBS "" ON)

project(gdszmod) # :>

file(GLOB_RECURSE SOURCE_FILES src/*.cpp libraries/DiscordRPCSDK/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# this is so stupid
set(CMAKE_SIZEOF_VOID_P 4)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  # ensure 32 bit on clang
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
  add_definitions("--target=i386-pc-windows-msvc")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
  libraries/minhook/include
  libraries/fmod
  ../../curly-eureka/gd.h/include
  ../../curly-eureka/gd.h/
  libraries/DiscordRPCSDK/Includes
  libraries/DiscordRPCSDK/SourceFiles
)
target_include_directories(${PROJECT_NAME} PRIVATE libraries/fmod)
add_subdirectory(libraries/minhook)
add_subdirectory(libraries/cocos-headers)
 
target_link_libraries(${PROJECT_NAME} minhook cocos2d)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libraries/fmod/fmod.lib)
target_link_libraries(${PROJECT_NAME} opengl32 ${CMAKE_SOURCE_DIR}/libraries/glew32.lib)