cmake_minimum_required(VERSION 3.0.0)
project(vsc_sfml VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories("C:/SFML/lib/")
add_executable(vsc_sfml main.cpp)
# find_library(SFML 
# 	NAMES sfml-graphics sfml-window sfml-system
# 	PATHS "C:/SFML/lib"
# )
# target_link_libraries(vsc_sfml PUBLIC $(SFML))
target_link_libraries(vsc_sfml sfml-graphics sfml-window sfml-system)
target_include_directories(vsc_sfml PUBLIC "C:/SFML/include")
set_property(TARGET vsc_sfml PROPERTY CXX_STANDARD 23)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
