# Krux

Krux Development System V0.0.4

A Lua library providing access to multiple STD APIs and Unix calls.

## Requirements

- A POSIX-Standard compatible interface (MSYS, Cygwin, Normal POSIX, Linux (LIBC/GLIBC))
- Lua 5.4-5.2 compatible header paths.
- A Lua interpreter.
- `make`.

## Description

Krux is a fully featured Lua Library written in C++ that provides (some) POSIX functionalities, as well as utility
functions to ease Lua development.

All Krux requires is a POSIX-compatible interface such as Cygwin for windows, or just general Unix. Cygwin
has been the only tested Krux windows system, but that doesn't mean other systems don't work.

Cygwin users may need to continuously build and pull updates to maintain an active Krux library.