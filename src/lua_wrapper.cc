extern "C"
{
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
int luaopen_sentencepiece(lua_State *L);
}

#include <string>
#include <unordered_map>
#include <iostream>

#include <sentencepiece_processor.h>


static std::unordered_map<std::string, sentencepiece::SentencePieceProcessor*> processor_cache;
static std::mutex processor_cache_mutex;

static sentencepiece::SentencePieceProcessor* load_processor(const std::string& processor_model_path)
{
  std::lock_guard<std::mutex> lock(processor_cache_mutex);

  auto it = processor_cache.find(processor_model_path);
  if (it != processor_cache.end())
    return it->second;

  sentencepiece::SentencePieceProcessor* processor = new sentencepiece::SentencePieceProcessor();
  bool success = processor->Load(processor_model_path);
  if (!success) {
    std::cerr<<"Cannot load: "<<processor_model_path<<std::endl;
    exit(0);
  }
  processor_cache[processor_model_path] = processor;
  return processor;
}

static int encode(lua_State *L) {
  std::vector<std::string> pieces;
  sentencepiece::SentencePieceProcessor *processor = load_processor(lua_tostring(L, -2));
  processor->Encode(lua_tostring(L, -1), &pieces);
  lua_pop(L, 2);
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
  sentencepiece::SentencePieceProcessor *processor = load_processor(lua_tostring(L, -2));
  for(int i=1; true; i++) {
    lua_rawgeti(L, -1, i);
    if (lua_isnil(L, -1)) break;
    std::string a = lua_tostring(L, -1);
    pieces.push_back(a);
    lua_pop(L,1);
  }
  lua_pop(L, 3);
  std::string v;
  processor->Decode(pieces, &v);
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

  lua_pushcfunction(L, encode);
  lua_setfield(L, -2, "encode");

  lua_pushcfunction(L, decode);
  lua_setfield(L, -2, "decode");

  return 1;
}
