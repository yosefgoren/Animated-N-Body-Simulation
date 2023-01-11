cmake_minimum_required(VERSION 3.0.0)
project(nbody VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories("C:/SFML/lib/")
add_executable(nbody main.cpp Space.cpp)
# find_library(SFML 
# 	NAMES sfml-graphics sfml-window sfml-system
# 	PATHS "C:/SFML/lib"
# )
# target_link_libraries(nbody PUBLIC $(SFML))
target_link_libraries(nbody sfml-graphics sfml-window sfml-system)
target_include_directories(nbody PUBLIC "C:/SFML/include")
set_property(TARGET nbody PROPERTY CXX_STANDARD 23)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
