include_directories(${PROJECT_SRC_DIR}/src)

add_library(src
    SalamancerApplication.cpp
    cef/RenderHandler.cpp
    cef/App.cpp
    framework/meshers/GreedyMesher.cpp
    framework/terrain/PerlinTerrainGenerator.cpp
    framework/terrain/noiseutils.cpp
    framework/MeshLoader.cpp
)

if(UNIX)
  add_library(src
    ois/linux/CustomLinuxKeyboard.cpp
    ois/linux/CustomLinuxMouse.cpp
    ois/linux/CustomLinuxInputManager.cpp
  )
endif(UNIX)

ADD_DEFINITIONS(
    -std=c++11
)
