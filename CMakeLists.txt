cmake_minimum_required(VERSION 3.10)

project(lua-sentencepiece)

find_package (Torch REQUIRED)

include_directories(
  ${TORCH_INCLUDE_DIR}
)

set(LIBRARIES
  sentencepiece
)

list(APPEND SOURCES src/lua_wrapper.cc)
if(NOT APPLE)
  # on MacOs - linking with lua library fails at runtime with a double lua_close() call
  list(APPEND LIBRARIES lua)
endif()

add_library(${PROJECT_NAME} MODULE ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")

if(APPLE)
  SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup -all_load")
endif()
  
install(FILES ${CMAKE_BINARY_DIR}/lua-sentencepiece.so
  DESTINATION ${INSTALL_DEST}
)
