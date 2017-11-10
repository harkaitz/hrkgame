# lic:#
# lic:#    Copyright (C) 2017  Harkaitz Agirre Ezama
# lic:#
# lic:#    This file is part of hrk-package.
# lic:#
# lic:#    hrk-package is free software: you can redistribute it and/or modify
# lic:#    it under the terms of the GNU Lesser General Public License as published by
# lic:#    the Free Software Foundation, either version 3 of the License, or
# lic:#    (at your option) any later version.
# lic:#
# lic:#    hrk-package is distributed in the hope that it will be useful,
# lic:#    but WITHOUT ANY WARRANTY; without even the implied warranty of
# lic:#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# lic:#    GNU Lesser General Public License for more details.
# lic:#
# lic:#    You should have received a copy of the GNU Lesser General Public License
# lic:#    along with hrk-package.  If not, see <http://www.gnu.org/licenses/>.
# lic:#
cmake_minimum_required(VERSION 3.0)
project(hrkgame VERSION 0.1)
if ( CMAKE_COMPILER_IS_GNUCC )
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -std=c++11")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif ( MSVC )
if (EXISTS ${CMAKE_SOURCE_DIR}/cmake/hrkconfig.cmake)
  include(${CMAKE_SOURCE_DIR}/cmake/hrkconfig.cmake)
endif()
if (EXISTS ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt)
  add_subdirectory(${CMAKE_SOURCE_DIR}/src)
endif()
