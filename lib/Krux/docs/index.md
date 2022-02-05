<!--
 Copyright 2022 Kai D. Gonzalez
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
     http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
-->

# Krux

Krux was built to bring C++ Functions and standard Unix APIs into Lua for modern application programming.

Kux contained so many libraries that could be used for multiple tasks, this is a portable 1 file version of 
every single Kux library minus the ones that require a lot of other libaries.

## Library

### krux

The base Krux module

### krux.cp(src, dest)

Copies `src`'s bytes to `dest`.

### krux.exists(dir)

Checks if directory exists. This is using the C++ std::ifstream method, there are traditional
io.open == nil methods, this is a pure C++ implementation.

### krux.getcwd()

Gets the current working directory using std::filesystem.

### krux.mkdir(name)

Creates a directory.

### [EXCLUSIVE] krux.read(prompt)

> krux.read() is a part of the READLINE API, normal Krux installations don't have this installed by default.
> CYGWIN users can use this as long as they have the Cygwin-built readline library installed.

Prompts "prompt" and gathers text, then sends it to the function return value.

### [EXCLUSIVE] krux.addhistory(text)

> krux.addhistory() is a part of the READLINE API, normal Krux installations don't have this installed by default.
> CYGWIN users can use this as long as they have the Cygwin-built readline library installed.

Adds "text" to readline-history.

### [EXCLUSIVE] [UNSAFE] krux.usingrl() 

> Using krux.usingrl() is unsafe if you are using without READLINE API installed.
> The workaround is to use `krux.usingrl == nil` as A PROPERTY, to prevent any unwanted errors and memory leaks.

A placeholder function to indicate READLINE_API_USAGE.

### krux.rm(src)

> This can only remove files and empty folders, to remove every file and folder(s) in a folder,
> use `krux.rmall`

Remove a file or empty folder.

### krux.rmall(src)

Remove a file, or a folder (recursively)

### krux.sleep(secs)

> Functions like this make Krux incompatible with base windows, a mask POSIX library such as
> Cygwin is required to run functions like this.

Uses the unistd.h SLEEP function to delay functionality for `secs` second(s).

### krux.symlink(src, dest)

> This function is implemented differently on different POSIX standards, please check your version KRUX
> is built for, the functionality here may not be the same.

Create a symlink from src to dest.

### [BUILD] krux.uname()

> Different POSIX standards handle this differently.

This function returns the name of the Operating system krux was built for.

### [UNSAFE] krux.tickMemoryLua()

> Warning: memory functions override Lua's base memory handling.
> Only use memory functions if you know what you are doing.

Flips the "UnsafeMemsetsAllowed" boolean.

### [UNSAFE] krux.palloc(num, string)

> This function allocates memory, only use if you know what you're doing.
> This destroys the barrier from the `print()` function builtin.

Allocate memory and print the "string".

### krux.untickMemoryLua()

> This DISABLES any usage of memory functions, and warning messages can be thrown.

Flips the "UnsafeMemsetsAllowed" boolean back to false.

### krux.parseentries(dir)

> NOT WHAT YOU EXPECT!
> This function returns a parsable string separated by the only character not allowed in file names (/)
> You can parse by using the Krux split function, found in test.lua.

Returns a parsable string containing all of the filesystem files (including . and ..).

A basic implementation of a parser is as follows:

```lua

function lsplit(s, delimiter)
    result = {};
    for match in (s..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match);
    end
    return result;
end

function split(string, d)
    local tblt = {}
    local lns = lsplit(string, d)
    i = 0
    -- works!

    for _,V in ipairs(lns) do
        tblt[i] = V;
        i = i + 1
    end
    return tblt
end

-- Now we're going to get a parseable entry string.

local ps = krux.parseentries(".")

local files = split(ps, "/")

```