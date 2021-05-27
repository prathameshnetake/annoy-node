project(annoy-node)
cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 14)

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})        
set(CMAKE_BUILD_TYPE Debug)


include_directories(annoy/src ${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
add_compile_definitions(NAPI_VERSION=${napi_build_version})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

add_definitions( -DANNOYLIB_MULTITHREADED_BUILD -DNAPI_DISABLE_CPP_EXCEPTIONS)

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=6)
