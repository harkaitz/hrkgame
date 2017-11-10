#ifndef _HRKGAME_BOARD_HH_
#define _HRKGAME_BOARD_HH_
#include "hrkgame-base.hh"
namespace hrkgame {
     class Board {
     public:
	  int X,Y,Z;
	  std::list<Token>  pieces;
	  std::list<Token>::iterator it;
	  Board(int X,int Y,int Z) {
	       this->X = X; this->Y = Y; this->Z = Z;
	  }
	  bool inside(int x,int y,int z) {
	       if(x >= X || x < 0) return false;
	       if(y >= Y || x < 0) return false;
	       if(z >= Z || x < 0) return false;
	       return true;
	  }
	  Token *get(int x = 0,int y = 0,int z = 0,bool start = true) {
	       Token *ret = NULL;
	       if(start) it = pieces.begin();
	       for(;it != pieces.end() && ret == NULL;it++) {
		    if(it->pos[0] != x) continue;
		    if(it->pos[1] != y) continue;
		    if(it->pos[2] != z) continue;
		    ret = &(*ret); break;
	       }
	       return ret;
	  }
	  void   set(Token *piece,int x = 0,int y = 0,int z = 0) {
	       if(!inside(x,y,z))
		    throw std::runtime_error("Out of bounds.");
	       if(piece->type != SYMBOL_TOKEN_TYPE)
		    throw std::runtime_error("Piece.");
	       piece->pos[0] = (x>0)?x:0;
	       piece->pos[1] = (y>0)?y:0;
	       piece->pos[2] = (z>0)?z:0;
	  }
	  void   add(Token *piece,int x = 0,int y = 0,int z = 0) {
	       set(piece,x,y,z);
	       pieces.push_back(*piece);
	  }
	  std::string str() {
	       std::string ret;
	       for(int y=0;y<3;y++) {
		    ret += "|";
		    for(int x=0;x<3;x++) {
			 Token *t = get(x,y,0);
			 ret += (t)?t->name:" "; ret += "|";
			 
		    }
		    ret += "\n";
	       }
	       return ret;
	  }
     };


     
}
#endif

