include_directories(${PROJECT_SRC_DIR}/src)
add_library(src BaseApplication.cpp SalamancerApplication.cpp)
ADD_DEFINITIONS(
    -std=c++11
)