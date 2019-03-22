#define GMMODULE

#include <GarrysMod/Lua/Interface.h>

int os_execute(lua_State *state) {
  return 1;
}

GMOD_MODULE_OPEN() {
  LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->GetField(-1, "os");
      LUA->PushString("execute");
      LUA->PushCFunction(os_execute);
    LUA->SetTable(-3);
  LUA->Pop();

  return 0;
}

GMOD_MODULE_CLOSE() {
  return 0;
}
