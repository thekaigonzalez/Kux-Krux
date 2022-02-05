#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>

#ifdef KRUX_READLINE_API
    #include <readline/readline.h>
    #include <readline/history.h>
#endif

namespace fs = std::filesystem;

#define KRUX_API(x) static int x(lua_State *L)

bool UnsafeMemsetsallowed = false;

KRUX_API(krux_cpfs) {
    if (std::ifstream(luaL_checkstring(L, 2))) {
        std::cout << "krux: file/folder exists\n";
        return(0);
    } else {
        fs::copy(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
        return(1);
    }
}

KRUX_API(krux_tickMemoryBasedLua) {
    UnsafeMemsetsallowed = true;
    return 1;
}

KRUX_API(krux_untickMemoryBasedLua) {
    UnsafeMemsetsallowed = false;
    return 1;
}



KRUX_API(krux_allocprint) {
     if (UnsafeMemsetsallowed) {
        auto memory = malloc(sizeof luaL_checkinteger(L, 1));

        printf("%s", luaL_checkstring(L, 2));

        free(memory);
    }
    else {
        luaL_error(L, "FastPrint() failed!\nwhat(): Universal C API not allowed\n\nRETURN CODE(): 0x0002");
        return -1;
    }
    return 1;
}

KRUX_API(krux_mkdir) {
    // if (std::filesystem::e)

    if (!std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::create_directory(luaL_checkstring(L, 1));
    } else {
        std::cout << "Directory/File exists\n";
    }
    return (0);
}

KRUX_API(krux_exists) {
    lua_pushboolean(L, (bool)std::ifstream(luaL_checkstring(L, 1)));
    return 1;
}

KRUX_API(krux_rm) {
    if (std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::remove(luaL_checkstring(L, 1));
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

KRUX_API(krux_rma) {
    if (std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::remove_all(luaL_checkstring(L, 1));
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

KRUX_API(krux_sleep) {
    sleep(luaL_checkinteger(L, 1));
    return 1;
}

KRUX_API(krux_getcwd) {
    lua_pushstring(L, std::filesystem::current_path().c_str());
    return 1;
}

KRUX_API(krux_uname) {
#ifdef __CYGWIN__
    lua_pushstring(L, "Cygwin");
#elif __linux__
    lua_pushstring(L, "Linux-based");
#elif __unix__
    lua_pushstring(L, "Unix-based");
#endif
    return 1;
}


KRUX_API(krux_symlink) {
    if (!std::ifstream(luaL_checkstring(L, 2))) {
        if (std::ifstream(luaL_checkstring(L, 1))) {
            std::filesystem::create_symlink(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
        } else {
            std::cout << "krux: error: symlink / file exists\n";
        }
    } else {
        std::cout << "krux: error: file exists.\n";
    }

    return 1;
}
#ifdef KRUX_READLINE_API
KRUX_API(krux_read) {
    lua_pushstring(L, readline(luaL_checkstring(L, 1)));
    return 1;
}

KRUX_API(krux_addhistory) {
    add_history(luaL_checkstring(L, 1));
    return 1;
}

// Placeholder for check.
KRUX_API(krux_usingrl) {
    return 1;
}
#endif


// This is a parseable string.
KRUX_API(krux_returndir) {
    // lua_newtable(L);
// l_pushtablestring(L, "fname", "john");
// l_pushtablestring(L, "lname", "stewart");
    std::string m = "";

    for (const auto& a : std::filesystem::directory_iterator(luaL_checkstring(L, 1))) {
        m += a.path().string() + "/";
    }

    lua_pushstring(L, m.c_str());

    // lua_pushglobaltable(L);

    return 1;
}

static const luaL_Reg krux[] = {
  {"palloc", krux_allocprint},
  {"tickMemoryLua", krux_tickMemoryBasedLua},
  {"untickMemoryLua", krux_untickMemoryBasedLua},
  {"cp", krux_cpfs},
  {"exists", krux_exists},
  {"getcwd", krux_getcwd},
  {"mkdir", krux_mkdir},
#ifdef KRUX_READLINE_API
  {"read", krux_read},
  {"addhistory", krux_addhistory},
  {"usingrl", krux_usingrl},
#endif
  {"parseentries", krux_returndir},
  {"rmall", krux_rma},
  {"rm", krux_rm},
  {"sleep", krux_sleep},
  {"symlink", krux_symlink},
  {"uname", krux_uname},
  {NULL, NULL}
};


extern "C" {
    int luaopen_krux(lua_State *L) {
        luaL_newlib(L, krux);
        return 1;
    }
}