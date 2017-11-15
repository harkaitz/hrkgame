# lic:#
# lic:#    Copyright (C) 2017  Harkaitz Agirre Ezama
# lic:#
# lic:#    This file is part of hrkgame.
# lic:#
# lic:#    hrkgame is free software: you can redistribute it and/or modify
# lic:#    it under the terms of the GNU Lesser General Public License as published by
# lic:#    the Free Software Foundation, either version 3 of the License, or
# lic:#    (at your option) any later version.
# lic:#
# lic:#    hrkgame is distributed in the hope that it will be useful,
# lic:#    but WITHOUT ANY WARRANTY; without even the implied warranty of
# lic:#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# lic:#    GNU Lesser General Public License for more details.
# lic:#
# lic:#    You should have received a copy of the GNU Lesser General Public License
# lic:#    along with hrkgame.  If not, see <http://www.gnu.org/licenses/>.
# lic:#
set(HRKGAME_HEADERS
  hrkgame.hh
  hrkgame-tictactoe.hh
  hrkgame-board.hh
  hrkgame-base.hh
  hrkaux.h
  )
set(HRKGAME_SOURCES

  hrkgame.cc            
  hrkgame-tictactoe.cc  
  hrkgame-board.cc      
  hrkgame-base.cc       
  hrkaux.c              
  )

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()
add_executable(tictactoe main.cc)
add_executable(hrkgamex  main.cc)
add_library(hrkgame  STATIC ${HRKGAME_SOURCES})

target_link_libraries(tictactoe hrkgame)
target_link_libraries(hrkgamex  hrkgame)


install(TARGETS hrkgame   DESTINATION lib)
install(TARGETS tictactoe DESTINATION bin)
install(TARGETS hrkgamex  DESTINATION bin)
install(FILES ${HRKGAME_HEADERS} DESTINATION include/hrkgame)

