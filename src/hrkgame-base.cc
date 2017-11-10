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
#include "hrkgame-base.hh"
#include <string.h>
/* -------------------------------- TOKEN --------------------------------- */
hrkgame::Token::Token(int x,int y,int z) {
     type   = POSITION_TOKEN_TYPE;
     pos[0] = x;
     pos[1] = y;
     pos[2] = z;
     sprintf(name,"%i,%i,%i",pos[0],pos[1],pos[2]);
}
hrkgame::Token::Token(int count,const char *word) {
     char *s,*r; unsigned int i;
     // Copy to temporary buffer, only on word.
     bool numeric = true;
     for(i=0;word[i] && i < (sizeof(name)-1);i++) {
	  name[i] = tolower(word[i]);
	  if(name[i] == ',') continue;
	  if(name[i] <= '9' && name[i] >= '0') continue;
	  numeric = false;
     }
     name[i] = '\0';
     // Copy temporary position.
     pos[0] = 0; pos[1] = 0; pos[2] = 0;
     
     switch(count) {
     case 0:
	  type = PLAYER_TOKEN_TYPE;
	  break;
     default:
	  if(numeric) {
	       type = POSITION_TOKEN_TYPE;
	       // Set position.
	       for(i=0,s=strtok_r(name,",",&r);i<3 && s;i++,s=strtok_r(NULL,",",&r))
		    pos[i] = atoi(s);
	       for(;i<3;i++) pos[i] = 0;
	       // Set string.
	       sprintf(name,"%i,%i,%i",pos[0],pos[1],pos[2]);
	  } else {
	       type = SYMBOL_TOKEN_TYPE;
	  }
	  break;
     }
}
bool hrkgame::Token::equal(Token *other) {
     if(this->type != other->type) return false;
     switch(this->type) {
     case PLAYER_TOKEN_TYPE:
     case SYMBOL_TOKEN_TYPE:
	  return !strcasecmp(other->name,this->name);
     case POSITION_TOKEN_TYPE:
	  if(other->pos[0] != this->pos[0]) return false;
	  if(other->pos[1] != this->pos[1]) return false;
	  if(other->pos[2] != this->pos[2]) return false;
	  return true;
     default:
	  throw std::runtime_error("Unknown token.");
     }
}
std::string hrkgame::Token::str() {
     std::string str;
     str += "("; 
     switch(type) {
     case PLAYER_TOKEN_TYPE  : str += "Player   "; break;
     case SYMBOL_TOKEN_TYPE  : str += "Symbol   "; break;
     case POSITION_TOKEN_TYPE: str += "Position "; break;
     }
     str += name; str += ")";
     return str;
}

/* ------------------------ COMMAND ----------------------- */
hrkgame::Command::Command(const char *player) {
     add(hrkgame::Token(0,player));
}
void hrkgame::Command::add(Token token) {
     tokens.push_back(token);
}
void hrkgame::Command::add(const char *token) {
     add(hrkgame::Token(tokens.size(),token));
}
int  hrkgame::Command::count() {
     return tokens.size();
}
bool hrkgame::Command::equal(Command *other) {
     int l1 = this->count();
     int l2 = other->count();
     if(l1 != l2) return false;
     for(auto a = tokens.begin(),b = other->tokens.begin() ;
	 a != tokens.end() && b != other->tokens.end();
	 ++a,++b) {
	  if(!a->equal(&(*b))) return false;
     }
     return true;
}
std::string hrkgame::Command::str() {
     std::string ret;
     for(auto t : tokens) {
	  ret += " ";
	  ret += t.str();
     }
     return ret;
}
hrkgame::Token *hrkgame::Command::get(int n) {
     int i = 0;
     for(auto it=tokens.begin(); it != tokens.end(); it++,i++) {
	  if(n == i) return &(*it);
     }
     return NULL;
}



/* ----------------------------- GAME ------------------------------- */
hrkgame::Game::Game(const char *players[]) {
     this->players = players;
     updateCommands();
}
bool hrkgame::Game::isAllowed(Command *command) {
     if(command->count()<=1) return true;
     for(auto cmd : commands) {
	  if(cmd.equal(command)) return true;
     }
     return false;
}
void hrkgame::Game::updateCommands() {
     commands.clear();
}
bool hrkgame::Game::execute(Command *command) {
     if(!isAllowed(command)) {
	  throw std::runtime_error("Command not allowed.");
     }
     return false;
}
std::string hrkgame::Game::str(const char *player) {
     return std::string("<No-view>");
}
bool hrkgame::Game::isTurn (const char *player) {
     for(auto cmd : commands) {
	  Token *p = cmd.get(0);
	  if(p->type == PLAYER_TOKEN_TYPE)
	       if(!strcmp(player,p->name))
		    return true;
     }
     return false;
}
int  hrkgame::Game::value(const char *player) {
     return 0;
}
void hrkgame::Game::print(const char *player,FILE *fp1,FILE *fp2,int flags) {
     /* Show the game. */
     std::string sgame = str(player);
     fprintf(fp1,"%s\n",sgame.c_str());
     
     /* Show the moves. */
     if(flags & HRKGAME_COMMANDS) {
	  for(auto c : commands) {
	       std::string sc = c.str();
	       if(flags & HRKGAME_MINIMAX) {
		    fprintf(fp2,"Minimax=%-4i ",minimax(&c,player));
	       }
	       fprintf(fp2,"%s\n",sc.c_str());
	  }
     }
}
bool hrkgame::Game::start(const char *player,FILE *fp0,FILE *fp1,FILE *fp2,int flags) {
     char buffer[512] = { 0 }; char *t,*r;
     
     if(!isTurn(player)) return false;
     do {

	  print(player,fp1,fp2,flags);
	  
	  /* Prompt. */
	  if(flags & HRKGAME_PROMPT)
	       fprintf(fp2,"hrkgame (%s) > ",player);

	  /* Read newline. */
	  if(!fgets(buffer,sizeof(buffer)-1,fp0)) return false;

	  /* Forge command. */
	  Command *cmd = new Command(player);
	  for(t=strtok_r(buffer," \t\n\r",&r);t;t=strtok_r(NULL," \t\n\r",&r)) {
	       cmd->add(t);
	  }

	  /* Execute command. */
	  try {
	       if(flags & HRKGAME_DEBUG) {
		    std::string scmd = cmd->str();
	  	    fprintf(fp2,"Execute: %s\n",scmd.c_str());
	       }
	       execute(cmd);
	  } catch (std::exception &err) {
	       fprintf(fp2,"Error: %s\n",err.what());
	  }

	  /* Clear command. */
	  delete cmd;
     } while(isTurn(player));
     return true;
}
bool hrkgame::Game::start(const char *player,FILE *fp1,FILE *fp2,int flags) {
     if(!isTurn(player)) return false;
     do {
	  print(player,fp1,fp2,flags);
	  /* Select the best one. */
	  Command *cmd = NULL; int best = -1000;
	  for(auto i = commands.begin(); i != commands.end(); i++) {
	       if(strcmp(player,i->get(0)->name)) continue;
	       int val = minimax(&(*i),player);
	       if(val>best || cmd == NULL) {
		    best = val;
		    cmd = &(*i);
	       }
	  }
	  /* Execute the best option. */
	  if(flags & HRKGAME_DEBUG) {
	       std::string scmd = cmd->str();
	       fprintf(fp2,"AI: %s\n",scmd.c_str());
	  }
	  execute(cmd);
     } while(isTurn(player));
     return true;
}
int hrkgame::Game::minimax(Command *command,const char *player,int depth,int alpha,int beta) {
     /* Execute command. */
     Game *child = copy();
     child->execute(command);
     /* Recursion bottom. */
     if(depth == 0 || child->commands.size() == 0) {
	  int val = child->value(player);
	  //fprintf(stderr,"val=%i ",val);
	  return val;
     }
     /* This is Min or Max? */
     bool isMax = child->isTurn(player);
     /* Calculate Minimax value. */
     for(auto cmd : child->commands) {
	  /* When our turn, skip others. */
	  if(isMax && strcmp(cmd.get(0)->name,player)) continue;
	  /* Calculate value. */
	  int temp = child->minimax(&cmd,player,depth-1,alpha,beta);
	  if(isMax) {
	       alpha = std::max(alpha,temp);
	       if(beta <= alpha) return beta;
	  } else {
	       beta  = std::min(beta,temp);
	       if(beta <= alpha) return alpha;
	  }
     }
     delete child;
     return (isMax)?alpha:beta;
}
hrkgame::Game::~Game() { }
