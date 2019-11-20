cmake_minimum_required(VERSION 3.7)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 777)
endif()

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(matrix main.cpp matrix.h)


set_target_properties(matrix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

# set_target_properties(test_print_ip PROPERTIES
#     COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#     INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
# )

target_link_libraries(matrix
    ${Boost_LIBRARIES}
    Threads::Threads
)

# target_link_libraries(test_print_ip
#     ${Boost_LIBRARIES}
# )

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "SergeiNA at github.com")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

# enable_testing()

# add_test(print_ip_tests test_print_ip)

