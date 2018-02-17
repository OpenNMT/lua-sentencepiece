cmake_minimum_required(VERSION 3.1)

project(lua-sentencepiece)

set(CMAKE_CXX_STANDARD 11)

find_library(LUA_LIBRARY NAMES luajit lua)
find_path(LUA_INCLUDE_DIR NAMES
  lua.h
  lualib.h
  lauxlib.h
  )

if(NOT LUA_LIBRARY OR NOT LUA_INCLUDE_DIR)
  error("lua not found")
else()
  message(STATUS "Found Lua: ${LUA_LIBRARY}")
endif()

find_library(SP_LIBRARY NAMES sentencepiece)
find_path(SP_INCLUDE_DIR NAMES sentencepiece_processor.h)

if(NOT SP_LIBRARY OR NOT SP_INCLUDE_DIR)
  error("sentencepiece not found")
else()
  message(STATUS "Found sentencepiece: ${SP_LIBRARY}")
endif()

include_directories(
  ${LUA_INCLUDE_DIR}
  ${SP_INCLUDE_DIR}
)

set(LIBRARIES
  ${SP_LIBRARY}
)

if(NOT APPLE)
  # on MacOs - linking with lua library fails at runtime with a double lua_close() call
  list(APPEND LIBRARIES ${LUA_LIBRARY})
endif()

add_library(${PROJECT_NAME} MODULE src/lua_wrapper.cc)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup -all_load")
endif()

install(FILES ${CMAKE_BINARY_DIR}/lua-sentencepiece.so
  DESTINATION ${INSTALL_DEST}
)
