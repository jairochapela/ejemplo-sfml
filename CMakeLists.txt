cmake_minimum_required(VERSION "3.7")

project("EjemploSFML")
set(CMAKE_PREFIX_PATH ${SFML_DIR} ${CMAKE_PREFIX_PATH})
add_executable(${PROJECT_NAME} "src/main.cpp")
find_package(SFML 2.5 REQUIRED network audio graphics window system)

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics)

#install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
#set(SFML_STATIC_LIBRARIES TRUE)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${EjemploSFML_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${EjemploSFML_VERSION_MINOR}")
include(CPack)