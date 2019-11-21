cmake_minimum_required(VERSION 3.7)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 777)
endif()

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(matrix main.cpp matrix.h)
add_executable(test_access test_access.cpp matrix.h)
add_executable(test_access_sq test_access_sq.cpp matrix.h)
add_executable(test_loop test_loop.cpp matrix.h)
add_executable(test_op test_op.cpp matrix.h)


set_target_properties(matrix test_access test_access_sq test_loop test_op PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)


set_target_properties(matrix test_access test_access_sq test_loop test_op PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(matrix test_access test_access_sq test_loop test_op PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

# 

target_link_libraries(matrix
    ${Boost_LIBRARIES}
    Threads::Threads
)

target_link_libraries(test_access
    Threads::Threads
    ${Boost_LIBRARIES}
)

target_link_libraries(test_access_sq
    Threads::Threads
    ${Boost_LIBRARIES}
)

target_link_libraries(test_loop
    Threads::Threads
    ${Boost_LIBRARIES}
)

target_link_libraries(test_op
    Threads::Threads
    ${Boost_LIBRARIES}
)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "SergeiNA at github.com")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(test_access test_access)
add_test(test_access_sq test_access_sq)
add_test(test_loop test_loop)
add_test(test_op test_op)

