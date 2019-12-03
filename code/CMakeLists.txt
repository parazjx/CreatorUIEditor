# reader lib for creator to cocos2d-x plugin
set(LIB_NAME creator_reader)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COCOS2DX_ROOT_PATH}/cocos/editor-support
)

set(READER_HEADER
    CreatorReader_generated.h
    CreatorReader.h
    Macros.h
    ui/RichtextStringVisitor.h
    ui/PageView.h
)

set(READER_SOURCE
    CreatorReader.cpp
    ui/PageView.cpp
    ui/RichtextStringVisitor.cpp
)

if(BUILD_LUA_LIBS)
    list(APPEND READER_HEADER
        lua-bindings/reader/lua_creator_reader_auto.hpp
        lua-bindings/reader/lua_creator_reader_manual.hpp
        lua-bindings/creator_reader_bindings.hpp
    )
    list(APPEND READER_SOURCE
        lua-bindings/creator_reader_bindings.cpp
        lua-bindings/reader/lua_creator_reader_auto.cpp
        lua-bindings/reader/lua_creator_reader_manual.cpp
    )
endif()


add_library(${LIB_NAME} ${READER_SOURCE} ${READER_HEADER})

set_target_properties(${LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "Internal"
)

add_subdirectory(dragonbones)
target_link_libraries(${LIB_NAME} dragonbones)

if(XCODE OR VS)
    cocos_mark_code_files(${LIB_NAME})
endif()
