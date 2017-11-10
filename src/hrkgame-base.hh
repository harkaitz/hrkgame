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
#ifndef _HRKGAME_BASE_CC_
#define _HRKGAME_BASE_CC_
#include <list>
#include <string>
#include <map>
namespace hrkgame {
     class Token {
     public:
#         define PLAYER_TOKEN_TYPE   'p'
#         define POSITION_TOKEN_TYPE 'P'
#         define SYMBOL_TOKEN_TYPE   'S'
	  int  pos[3];
#         define INVALID_POSITION -1
	  char name[40];
	  char type;
	  Token(int x,int y,int z);
	  Token(int count,const char *word);
	  bool equal(Token *other);
	  std::string str();
     };
     class Command {
     public:
	  std::list<Token> tokens;
	  Command(const char *player);
	  int  count();
	  void add(Token token);
	  void add(const char *token);
	  Token *get(int n);
	  bool equal(Command *other);
	  std::string str();
     };
     class Game {
     public:
	  const char **players;
	  Game(const char *players[]);
	  std::list<Command>      commands;
	  bool isAllowed(Command *command);
	  bool isTurn   (const char *player);
	  virtual ~Game();
	  virtual void        updateCommands();
	  virtual bool        execute(Command *command); /* Return true when found. */
	  virtual std::string str    (const char *player);
	  virtual int         value (const char *player);
	  virtual Game       *copy() = 0;
	  void print(const char *player,FILE *fp1,FILE *fp2,int flags);
	  bool start(const char *player,FILE *fp0,FILE *fp1,FILE *fp2,int flags);
#         define HRKGAME_DEBUG    0x01
#         define HRKGAME_PROMPT   0x02
#         define HRKGAME_COMMANDS 0x04
#         define HRKGAME_MINIMAX  0x08
	  int minimax(Command *command,const char *player,int depth = 10,int alpha = -1000,int beta = 1000);
	  bool start(const char *player,FILE *fp1,FILE *fp2,int flags);
     };
     
}


#endif /* _HRKGAME_ */
