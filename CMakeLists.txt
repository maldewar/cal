#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 2.8)

set(APP_NAME Calaveras)
project (${APP_NAME})

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)

# libcocos2d
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua-tests")
add_subdirectory(${COCOS2D_ROOT})

# Some macro definitions
if(WINDOWS)
  if(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  else()
    ADD_DEFINITIONS (-DCC_STATIC)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()


# Compiler options
if(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  set(CMAKE_C_FLAGS_DEBUG "-g -O0 -v -Q --enable-checking -Wall -DCOCOS2D_DEBUG=1")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
  if(CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif(MSVC)



set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)
if(MACOSX OR APPLE)
set(PLATFORM_SPECIFIC_SRC
  proj.ios_mac/ios/main.m
  proj.ios_mac/ios/RootViewController.mm
  proj.ios_mac/ios/AppController.mm
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.ios_mac/ios/RootViewController.h
  proj.ios_mac/ios/AppController.h
)
elseif(LINUX) #assume linux
set(PLATFORM_SPECIFIC_SRC
  proj.linux/main.cpp
)
elseif ( WIN32 )
set(PLATFORM_SPECIFIC_SRC
  proj.win32/main.cpp
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.win32/main.h
  proj.win32/resource.h
)
endif()

include_directories(
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/audio/include
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/platform/desktop
  ${COCOS2D_ROOT}/cocos/platform/linux
  ${COCOS2D_ROOT}/cocos/editor-support
  ${COCOS2D_ROOT}/extensions
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/external/edtaa3func
  ${COCOS2D_ROOT}/external/jpeg/include/linux
  ${COCOS2D_ROOT}/external/tiff/include/linux
  ${COCOS2D_ROOT}/external/webp/include/linux
  ${COCOS2D_ROOT}/external/tinyxml2
  ${COCOS2D_ROOT}/external/unzip
  //${COCOS2D_ROOT}/external/chipmunk/include/chipmunk
  ${COCOS2D_ROOT}/external/freetype2/include/linux
  ${COCOS2D_ROOT}/external/websockets/include/linux
  ${COCOS2D_ROOT}/external/spidermonkey/include/linux
  ${COCOS2D_ROOT}/external/linux-specific/fmod/include/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/xxhash
  Classes
)

set(GAME_SRC
  Classes/AppDelegate.cpp
  Classes/LevelScene.cpp
  Classes/util/jsoncpp.cpp
  Classes/util/b2dJson.cpp
  Classes/util/b2dJsonImage.cpp
  Classes/util/Box2DDebugDraw.cpp
  Classes/util/CMath.cpp
  Classes/util/PathUtil.cpp
  Classes/util/IdUtil.cpp
  Classes/util/IdUtil.cpp
  Classes/util/CppTweener.cpp
  Classes/engine/RayCastTool.cpp
  Classes/engine/Timer.cpp
  Classes/component/DraggableComponent.cpp
  Classes/component/ContactComponent.cpp
  Classes/component/AIComponentCmd.cpp
  Classes/component/AIComponentWanderCmd.cpp
  Classes/component/AIComponentGoToCmd.cpp
  Classes/component/AIComponentSeekCmd.cpp
  Classes/component/AIComponent.cpp
  Classes/model/ImageNode.cpp
  Classes/model/ImageBody.cpp
  Classes/model/Entity.cpp
  Classes/model/EntityElem.cpp
  Classes/model/Entry.cpp
  Classes/model/Exit.cpp
  Classes/model/Unit.cpp
  Classes/model/Area.cpp
  Classes/model/Gravitron.cpp
  Classes/model/Flux.cpp
  Classes/model/DraggableEntity.cpp
  Classes/model/ctrl/WheelCtrl.cpp
  Classes/model/LayerDef.cpp
  Classes/model/WorldLayerDef.cpp
  Classes/model/BgLayerDef.cpp
  Classes/model/SceneDef.cpp
  Classes/model/ActSceneDef.cpp
  Classes/model/LevelSceneDef.cpp
  Classes/model/Level.cpp
  Classes/model/Branch.cpp
  Classes/engine/GraphNode.cpp
  Classes/engine/ChoiceGraph.cpp
  Classes/system/ContactSystem.cpp
  Classes/system/AISystem.cpp
  Classes/layer/BaseLayer.cpp
  Classes/layer/UILayer.cpp
  Classes/layer/BasicUILayer.cpp
  Classes/layer/MainMenuUILayer.cpp
  Classes/layer/ActMenuLayer.cpp
  Classes/layer/WorldActLayer.cpp
  Classes/layer/BackgroundLayer.cpp
  Classes/layer/BasicRUBELayer.cpp
  Classes/layer/WorldLevelLayer.cpp
  Classes/layer/WorldLevelCtrlLayer.cpp
  Classes/layer/GravityCtrlLayer.cpp
  Classes/layer/SelectCtrlLayer.cpp
  Classes/layer/WorldLevelUILayer.cpp
  Classes/layer/WorldLevelDebugLayer.cpp
  Classes/layer/WorldLevelStatisticsLayer.cpp
  Classes/scene/BaseScene.cpp
  Classes/scene/MainMenuScene.cpp
  Classes/scene/ActMenuScene.cpp
  Classes/scene/ActScene.cpp
  Classes/scene/WorldLevelScene.cpp
  Classes/manager/StorageManager.cpp
  Classes/manager/ConfigurationManager.cpp
  Classes/manager/UnitManager.cpp
  Classes/factory/BodyFactory.cpp
  Classes/factory/EntityFactory.cpp
  Classes/factory/SceneFactory.cpp
  ${PLATFORM_SPECIFIC_SRC}
)

set(GAME_HEADERS
  Classes/AppDelegate.h
  ${PLATFORM_SPECIFIC_HEADERS}
)

#if(GAME_HEADERS)
#add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
#else()
add_executable(${APP_NAME} ${GAME_SRC})
#endif()

target_link_libraries(${APP_NAME} box2d cocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
  COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
  )
else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )

endif()
