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
#include "hrkgame-tictactoe.hh"
#include <string.h>
static const char *tictactoe_players[] = {"x","o",NULL};
namespace hrkgame {
     /* ------------------------- TIC TAC TOE ----------------------------- */
     TicTacToe::TicTacToe() : Game(tictactoe_players),board(3,3,1) {
	  players[0] = "x"; players[1] = "o"; turn = 0;
	  points[0] = 0; points[1] = 0;
	  updateCommands();
     }
     void TicTacToe::updateCommands() {
	  Game::updateCommands();
	  /* Calculate puntuation. */
	  const int pos[8][3][2] = {
	       /* Diagonals. */
	       {{0,0},{1,1},{2,2}} , {{0,2},{1,1},{2,0}} ,
	       /* Horizontals. */
	       {{0,0},{1,0},{2,0}} , {{0,1},{1,1},{2,1}} , {{0,2},{1,2},{2,2}} ,
	       /* Verticals. */
	       {{0,0},{0,1},{0,2}} , {{1,0},{1,1},{1,2}} , {{2,0},{2,1},{2,2}} ,
	  };
	  for(int c = 0; c<8 ; c++) {
	       Token *t1 = board.get(pos[c][0][0],pos[c][0][1]);
	       if(!t1) continue;
	       Token *t2 = board.get(pos[c][1][0],pos[c][1][1]);
	       if(!t2) continue;
	       if(strcmp(t1->name,t2->name)) continue;
	       Token *t3 = board.get(pos[c][2][0],pos[c][2][1]);
	       if(!t3) continue;
	       if(strcmp(t1->name,t3->name)) continue;
	       if(!strcasecmp(t1->name,"x")) {
		    points[0] =  1; points[1] = -1;
	       } else {
		    points[0] = -1; points[1] =  1;
	       }
	  }
	  
	  if(points[0] == 0 && points[1] == 0) {
	       for(int x=0;x<3;x++)
		    for(int y=0;y<3;y++)
			 if(!board.get(x,y)) {
			      Command cmd = Command(players[turn]);
			      cmd.add(Token(x,y,0));
			      commands.push_back(cmd);
			 }
	       
	  }
	  
     }
     bool TicTacToe::execute(Command *command) {
	  if(Game::execute(command)) return true;
	  Token *player   = command->get(0);
	  Token *position = command->get(1);
	  if(!player)   return false;
	  if(!position) return false;
	  if(player->type   != PLAYER_TOKEN_TYPE) return false;
	  if(position->type != POSITION_TOKEN_TYPE) return false;
	  Token piece = Token(1,player->name);
	  board.add(&piece,
		    position->pos[0],
		    position->pos[1],
		    position->pos[2]);
	  turn = (turn+1)%2;
	  updateCommands();
	  return true;
     }
     std::string TicTacToe::str(const char *player) {
	  std::string t = board.str();
	  t += "Count: " + std::to_string(board.pieces.size()) + "\n";
	  t += "x: "; t+= std::to_string(points[0]); t += (isTurn("x")?" Move\n":" Wait\n");
	  t += "o: "; t+= std::to_string(points[1]); t += (isTurn("o")?" Move\n":" Wait\n");
	  return t;
     }
     int TicTacToe::value(const char *player) {
	  if(!strcasecmp(player,"x")) return points[0];
	  if(!strcasecmp(player,"o")) return points[1];
	  throw std::runtime_error("Player unsupported.");
     }
     Game *TicTacToe::copy() {
	  return new TicTacToe(*this);
     }
}
