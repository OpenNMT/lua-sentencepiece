package = "lua-sentencepiece"
version = "scm-1"
source = {
   url = "git://github.com/OpenNMT/lua-sentencepiece",
   tag = "master"
}
description = {
   summary = "Lua wrapper for sentencepiece library",
   detailed = [[
      This is a simple lua wrapper for sentencepiece https://github.com/google/sentencepiece
   ]],
   homepage = "http://github.com/OpenNMT/lua-sentencepiece",
   license = "MIT"
}
dependencies = {
   "lua >= 5.1, < 5.4"
}
external_dependencies = {
   LIBSENTENCEPIECE = {
      header = "sentencepiece_processor.h"
   }
}
build = {
   type = "cmake",
   variables = {
      INSTALL_DEST="$(LIBDIR)",
      CMAKE_BUILD_TYPE="Release",
      CMAKE_PREFIX_PATH="$(LUA_BINDIR)/..",
      CMAKE_INSTALL_PREFIX="$(PREFIX)"
   }
}