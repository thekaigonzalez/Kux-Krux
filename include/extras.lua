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

--[[ THIS INIT FILE CONTAINS EXTRA FUNCTIONS, MEANT TO BE USED WITH KRUX!!! ]]

local krux = require 'krux'

local function lsplit(s, delimiter)
    result = {}
    for match in (s..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match)
    end
    return result
end

function krux.Split(string, d)
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

return krux