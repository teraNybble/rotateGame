cmake_minimum_required(VERSION 3.15)
project(gamename69)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

file(GLOB SOURCE_FILES  *.cpp)

include_directories(/home/dan/CLionProjects/Game2D)
link_directories(/home/dan/CLionProjects/Game2D/cmake-build-debug/)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEV=1)
endif()

add_executable(gamename69 ${SOURCE_FILES} Game.cpp Game.h MainMenu.cpp MainMenu.h GameObject.cpp GameObject.h Player.cpp Player.h Player.cpp Player.h Level.cpp Level.h KeyMap.cpp KeyMap.h InputManager.cpp InputManager.h Enemy.cpp Enemy.h Projectile.cpp Projectile.h LoseScreen.cpp LoseScreen.h OptionsMenu.cpp OptionsMenu.h Debug.cpp Debug.h Boss.cpp Boss.h)

INCLUDE(FindPkgConfig)

find_package(X11 REQUIRED)
find_package(Threads)
find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)#was glfw3
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)

include_directories(${X11_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${PNG_INCLUDE_DIRS})


target_link_libraries(${PROJECT_NAME} /home/dan/CLionProjects/Game2D/cmake-build-debug/libGame2D.so)

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})