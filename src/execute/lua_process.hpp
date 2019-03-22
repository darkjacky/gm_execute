#ifndef _GM_EXECUTE_LUA_PROCESS_HPP_
#define _GM_EXECUTE_LUA_PROCESS_HPP_

#include <mutex>
#include <thread>
#include <memory>
#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaEvent.h>
#include <GarrysMod/Lua/LuaObject.h>
#include <reproc++/reproc.hpp>

namespace execute {
  using namespace GarrysMod::Lua;

  struct LuaProcessStartOptions {
  public:
    std::string path;
  }; // LuaProcessStartOptions

  class LuaProcess : 
    public LuaEventEmitter<890, LuaProcess>
  {
  public:
    LuaProcess(LuaProcessStartOptions opts) : LuaEventEmitter() {
      AddGetter("id", get_id);
      AddGetter("cwd", get_cwd);
      AddGetter("exitCode", get_exitCode);
      AddGetter("exitTime", get_exitTime);

      AddGetter("stdin", get_stdin);
      AddGetter("stdout", get_stdout);
      AddGetter("stderr", get_stderr);
      
      AddMethod("kill", kill);
      AddMethod("exit", exit);
      AddMethod("waitForExit", waitForExit);
    }
  private:
    LuaProcessStartOptions _opts;
  private:
    static int get_id(lua_State *state);
    static int get_cwd(lua_State *state);
    static int get_env(lua_State *state);
    static int get_exitCode(lua_State *state);
    static int get_exitTime(lua_State *state);

    static int get_stdin(lua_State *state);
    static int get_stdout(lua_State *state);
    static int get_stderr(lua_State *state);

    static int kill(lua_State *state);
    static int exit(lua_State *state);
    static int waitForExit(lua_State *state);
  }; // LuaProcess

} // execute

#endif//_GM_EXECUTE_LUA_PROCESS_HPP_