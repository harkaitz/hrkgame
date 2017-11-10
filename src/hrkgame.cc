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
#include "hrkgame.hh"
#include "hrkaux.h"
#include "hrkgame-tictactoe.hh"
using namespace hrkgame;

std::list<GameGenerator> gameGenerators;

void  hrkgame::add_game(const char *name,Game *(*gen) (const char *opts),const char *desc) {
     GameGenerator g;
     g.name = name; g.gen = gen; g.desc = desc;
     gameGenerators.push_back(g);
}
GameGenerator *hrkgame::has_game(const char *name) {
     for(auto i=gameGenerators.begin(); i != gameGenerators.end(); i++) {
	  if(hrkaux_rootname_equal(name,i->name)) return &(*i);
     }
     return NULL;
}
Game *hrkgame::get_game(const char *name,const char *opts) {
     GameGenerator *gg = has_game(name);
     if(!gg) throw std::runtime_error("Game not found.");
     return gg->gen(opts);
}
static Game *tictactoe(const char *opts) { return new hrkgame::TicTacToe(); }
void  hrkgame::init() {
     add_game("tictactoe",tictactoe,"Tic Tac Toe game.");
}
void  hrkgame::print_games() {
     for(auto g : gameGenerators) {
	  printf("%-20s : %s\n",g.name,g.desc);
     }
}
