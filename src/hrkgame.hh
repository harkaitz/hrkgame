/*
 * lic:#
 * lic:#    Copyright (C) 2017  Harkaitz Agirre Ezama
 * lic:#
 * lic:#    This file is part of hrkgame.
 * lic:#
 * lic:#    hrkgame is free software: you can redistribute it and/or modify
 * lic:#    it under the terms of the GNU Lesser General Public License as published by
 * lic:#    the Free Software Foundation, either version 3 of the License, or
 * lic:#    (at your option) any later version.
 * lic:#
 * lic:#    hrkgame is distributed in the hope that it will be useful,
 * lic:#    but WITHOUT ANY WARRANTY; without even the implied warranty of
 * lic:#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * lic:#    GNU Lesser General Public License for more details.
 * lic:#
 * lic:#    You should have received a copy of the GNU Lesser General Public License
 * lic:#    along with hrkgame.  If not, see <http://www.gnu.org/licenses/>.
 * lic:#
 */
#ifndef _HRKGAME_HH_
#define _HRKGAME_HH_
#include "hrkgame-base.hh"
namespace hrkgame {
     struct GameGenerator {
	  const char *name;
	  const char *desc;
	  Game *(*gen) (const char *opts);
     };
     void           add_game(const char *name,Game *(*gen) (const char *opts),const char *desc);
     GameGenerator *has_game(const char *name);
     Game          *get_game(const char *name,const char *opts);
     void           init();
     void           print_games();
}
#endif
