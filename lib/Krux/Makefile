# Copyright 2022 Kai D. Gonzalez
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
OUT=krux.so

SPECIAL_READLINE_API=

UNAME:=$(shell uname -o)

FLAGS=

CPP=g++

ifeq ($(UNAME), Cygwin)
    OUT:=krux.dll
endif

ifeq ($(SPECIAL_READLINE_API), yes)
    FLAGS += -lreadline -DKRUX_READLINE_API
endif

all:
	$(CPP) krux/krux.cpp $(FLAGS) -llua -fPIC -shared -o lib/$(OUT)