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
#include "hrkgame-board.hh"
using namespace hrkgame;
hrkgame::Board::Board(int X,int Y,int Z) {
     this->X = X; this->Y = Y; this->Z = Z;
}
bool hrkgame::Board::inside(int x,int y,int z) {
     if(x >= X || x < 0) return false;
     if(y >= Y || y < 0) return false;
     if(z >= Z || z < 0) return false;
     return true;
}
Token *hrkgame::Board::get(int x,int y,int z,bool start) {
     Token *ret = NULL;
     if(!inside(x,y,z)) return ret;
     if(start) it = pieces.begin();
     for(;it != pieces.end() && ret == NULL;it++) {
	  if(it->pos[0] != x) continue;
	  if(it->pos[1] != y) continue;
	  if(it->pos[2] != z) continue;
	  ret = &(*it);
     }
     return ret;
}
Token *hrkgame::Board::getRelative(Token *t,int x,int y,int z,bool start) {
     return get(t->pos[0]+x,t->pos[0]+y,t->pos[0]+z);
}


void hrkgame::Board::set(Token *piece,int x,int y,int z) {
     if(!inside(x,y,z))
	  throw std::runtime_error("Out of bounds.");
     if(piece->type != SYMBOL_TOKEN_TYPE)
	  throw std::runtime_error("Piece.");
     piece->pos[0] = (x>0)?x:0;
     piece->pos[1] = (y>0)?y:0;
     piece->pos[2] = (z>0)?z:0;
}
void hrkgame::Board::add(Token *piece,int x,int y,int z) {
     set(piece,x,y,z);
     pieces.push_back(*piece);
}
std::string hrkgame::Board::str() {
     std::string ret;
     for(int y=2;y>=0;y--) {
	  ret += std::to_string(y)+"|";
	  for(int x=0;x<3;x++) {
	       Token *t = get(x,y,0);
	       ret += std::string((t)?t->name:" ") + "|";
	  }
	  ret += "\n";
     }
     ret += "  ";
     for(int x=0;x<3;x++) {
	  ret += std::to_string(x)+":";
     }
     ret += "\n";
     return ret;
}
