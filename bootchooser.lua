-- Copyright 2022 Kai D. Gonzalez
-- 
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
-- 
--     http://www.apache.org/licenses/LICENSE-2.0
-- 
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

package.cpath = "/usr/local/include54/?.so;/usr/local/include54/?.dll"

local krux = require("krux")

-- check if Krux supports the READLINE api
local cndinp = false

if krux.usingrl ~= nil then cndinp = true end

local function input(prompt)
    if cndinp == true then
        local s = krux.read(prompt)

        krux.addhistory(s)

        return s
    else
        io.write(prompt)
        return io.read()
    end
end

print("What do you want to do?")

local wtd = input("> ")

if wtd == "install" then
    print("Installing bootloader...")

    krux.cp("loaders/default", "./boot/")
    
elseif wtd == "load" then
    print("Checking for existing loader...")
    krux.sleep(1)
    if krux.exists("./boot") then
        print("Found an existing installation! loading..")

        loadfile("./boot/BOOT64.lua")():init()
    end
end