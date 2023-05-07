cmake_minimum_required(VERSION 3.5)

project(ThugHuntingBackend LANGUAGES C)

add_executable(ThugHuntingBackend
    mongoose.h mongoose.c
    qttubeannotations.h qttubeannotations.c
    thuggallery.h thuggallery.c
    main.c)

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    target_include_directories(ThugHuntingBackend PUBLIC ${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ThugHuntingBackend OpenSSL::SSL OpenSSL::Crypto)
    message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")
else ()
    message(STATUS "OpenSSL not found")
endif ()

find_package(CURL REQUIRED)
if (CURL_FOUND)
    target_include_directories(ThugHuntingBackend PUBLIC ${CURL_INCLUDE_DIR})
    target_link_libraries(ThugHuntingBackend ${CURL_LIBRARIES})
    message(STATUS "Found CURL ${CURL_VERSION_STRING}")
else ()
    message(STATUS "CURL not found")
endif ()

install(TARGETS ThugHuntingBackend
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
