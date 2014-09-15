cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-gettouches-android )

set ( PLUGIN_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

set ( MOAI_GETTOUCHES_ANDROID_INCLUDES 
    ${PLUGIN_ROOT}/
)

# Use all cpp files in directory as source code
file ( GLOB_RECURSE MOAI_GETTOUCHES_ANDROID_SRC "${PLUGIN_ROOT}/*.cpp" )
file ( GLOB_RECURSE MOAI_GETTOUCHES_ANDROID_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_library ( moai-gettouches-android STATIC ${MOAI_GETTOUCHES_ANDROID_SRC} ${MOAI_GETTOUCHES_ANDROID_HEADERS} )
target_include_directories( moai-gettouches-android PUBLIC ${MOAI_GETTOUCHES_ANDROID_INCLUDES})
target_link_libraries (moai-gettouches-android moai-core)