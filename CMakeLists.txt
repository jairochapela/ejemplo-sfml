cmake_minimum_required(VERSION "3.7")

project("EjemploSFML")

add_executable(${PROJECT_NAME} "src/main.cpp")
find_package(SFML 2.5 REQUIRED network audio graphics window system)

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics)

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
