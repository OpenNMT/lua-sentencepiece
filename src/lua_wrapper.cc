extern "C"
{
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
int luaopen_sentencepiece(lua_State *L);
}

#include <sentencepiece_processor.h>
#include <iostream>

sentencepiece::SentencePieceProcessor processor;

static int load(lua_State *L) {

  bool success = processor.Load(lua_tostring(L, -1));
  lua_pop(L, 1);
  lua_pushboolean(L, success);

  return 1;
}

static int encode(lua_State *L) {
  std::vector<std::string> pieces;
  processor.Encode(lua_tostring(L, -1), &pieces);
  lua_pop(L, 1);
  lua_newtable(L);
  for(int i=0; i<pieces.size(); i++) {
    lua_pushnumber(L, i + 1);
    lua_pushstring(L, pieces[i].c_str());
    lua_settable(L, -3);
  }
  return 1;
}

static int decode(lua_State *L) {
  std::vector<std::string> pieces;
  for(int i=1; true; i++) {
    lua_rawgeti(L, -1, i);
    if (lua_isnil(L, -1)) break;
    std::string a = lua_tostring(L, -1);
    pieces.push_back(a);
    lua_pop(L,1);
  }
  lua_pop(L, 2);
  std::string v;
  processor.Decode(pieces, &v);
  lua_pushstring(L, v.c_str());
  return 1;
}


int luaopen_sentencepiece(lua_State *L) {

  lua_getglobal(L, "sentencepiece");
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    lua_newtable(L);
    lua_setglobal(L, "sentencepiece");
    lua_getglobal(L, "sentencepiece");
  }
  else if (!lua_istable(L, -1)) {
    std::cerr<<"Cannot create global namespace"<<std::endl;
    exit(0);
  }

  /* add functions */
  lua_pushcfunction(L, load);
  lua_setfield(L, -2, "load");

  lua_pushcfunction(L, encode);
  lua_setfield(L, -2, "encode");

  lua_pushcfunction(L, decode);
  lua_setfield(L, -2, "decode");

  return 1;
}
