cmake_minimum_required(VERSION 2.6)

project(Salamancer)

if(WIN32)
  set(CEF3_DIRECTORY "C:/Users/nathanial/Libraries/cef_binary_3.2078.1780_windows32")
  set(Boost_INCLUDE_DIR "C:/Users/nathanial/Libraries/boost_1_56_0")
	set(OGRE_HOME "C:/Users/nathanial/Libraries/OgreSDK_vc11_v1-9-0")
	set(CMAKE_MODULE_PATH "${OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH ${OGRE_HOME}/Samples/include)
	set(LIBNOISE_LIBRARY "C:/Users/nathanial/Libraries/libnoisedll-1.0.0/bin/libnoise.lib")
	set(CEF3_LIBCEF ${CEF3_DIRECTORY}/Debug/libcef.lib)
	set(CEF3_LIBCEF_DLL_WRAPPER ${CEF3_DIRECTORY}/out/Debug/lib/libcef_dll_wrapper.lib)
	set(LIBNOISE_INCLUDE_DIR "C:/Users/nathanial/Libraries/libnoiseheaders-1.0.0/include")
endif(WIN32)

if(UNIX)
	set(CEF3_DIRECTORY "/home/nathan/Sources/cef_binary_3.2078.1761_linux64")

	if(EXISTS "/usr/lib/OGRE/cmake")
		set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
		set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/")
		set(OGRE_VOLUME_INCLUDEPATH "/usr/include/OGRE/Volume/")
	else()
		message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/lib/OGRE")

	set(LIBNOISE_LIBRARY "/usr/lib/libnoise.so")

	set(CEF3_LIBCEF ${CEF3_DIRECTORY}/out/Release/libcef.so)
	set(CEF3_LIBCEF_DLL_WRAPPER ${CEF3_DIRECTORY}/out/Release/obj.target/libcef_dll_wrapper.a)
endif(UNIX)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

find_package(OGRE REQUIRED)

find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS")
endif()

if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FINDSAMPLE_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)

	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

add_definitions(-DOS_LINUX)

include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Overlay_INCLUDE_DIRS}
	${OGRE_VOLUME_INCLUDEPATH}
  ${CEF3_DIRECTORY}
	${LIBNOISE_INCLUDE_DIR}
  ./src
)

add_subdirectory(src)

add_executable(Salamancer src/SalamancerApplication.cpp)

set_target_properties(Salamancer PROPERTIES DEBUG_POSTFIX _d)

if(UNIX)
  target_link_libraries(
      Salamancer
      X11
      ICE
      SM
      ${OGRE_LIBRARIES}
      ${OIS_LIBRARIES}
      ${OGRE_Overlay_LIBRARIES}
      ${LIBNOISE_LIBRARY}
      ${CEF3_LIBCEF}
      ${CEF3_LIBCEF_DLL_WRAPPER}
      src
  )
endif(UNIX)
if(WIN32)
  target_link_libraries(
      Salamancer
      ${OGRE_LIBRARIES}
      ${OIS_LIBRARIES}
      ${OGRE_Overlay_LIBRARIES}
      ${LIBNOISE_LIBRARY}
      ${CEF3_LIBCEF}
      ${CEF3_LIBCEF_DLL_WRAPPER}
      src
  )
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)

install(TARGETS Salamancer
	RUNTIME DESTINATION bin
	CONFIGURATIONS All)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
	DESTINATION ./
	CONFIGURATIONS Release RelWithDebInfo Debug
)

install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
	${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
	DESTINATION bin
	CONFIGURATIONS Release RelWithDebInfo Debug
)

ADD_DEFINITIONS(
    -std=c++11
)
