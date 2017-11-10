/**
 * @file main.cc
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
#include <stdio.h>
#include "hrkgame.hh"
#include "hrkaux.h"
#include <unistd.h>
#include <string.h>

const char *help_string =
     "\n"
     " Usage: %s [OPTIONS...]"                                                     "\n"
     ""                                                                            "\n"
     " %s"                                                                         "\n"
     ""                                                                            "\n"
     "%s"                                                                          "\n"  
     " -h : Print this help message."                                              "\n"
     " -d : Print debugging information."                                          "\n"
     " -c : Show move list."                                                       "\n"
     " -m : Show minimax value of moves."                                          "\n"
     ""                                                                            "\n"
     " -x <format> : Specify AI players. Ie; `a-` makes player 1 AI controlled."   "\n"
     " -o <opts>   : Specify options for the game."                                "\n"
     ""                                                                            "\n"
     " Copyright (c) Harkaitz Agirre, 2017. All rights reserved."                  "\n"
     ""                                                                            "\n"
     ;
#define print_help(DESC,EXTRA) printf(help_string,bas,DESC,EXTRA)
#define print_all_help() \
     print_help("A collection of games for the terminal.", \
		" -g <game>|list : Select a game.\n"	   \
		" -l             : List games.\n");

int main(int argc, char *argv[]) {

     hrkgame::init();
     
     /* Calculate game from executable's name. */
     const char *bas = hrkaux_basename(argv[0]);
     const char *sel = bas;
     const char *opt = "";
     char player_is_ai[20] = { 0 }; int flags = HRKGAME_PROMPT,c;
     while((c = getopt(argc,argv,"dcmx:g:hl"))!=-1) {
	  switch (c) {
	  case 'h':
	       if(hrkgame::GameGenerator *gg = hrkgame::has_game(sel)) {
		    print_help(gg->desc,"");
	       } else {
		    print_all_help();
	       }
	       return 0;
	  case 'd': flags |= HRKGAME_DEBUG;                       break;
	  case 'c': flags |= HRKGAME_COMMANDS;                    break;
	  case 'm': flags |= HRKGAME_MINIMAX | HRKGAME_COMMANDS;  break;
	  case 'g': sel = optarg; break;
	  case 'l': sel = "list"; break;
	  case 'o': opt = optarg; break;
	  case 'x':
	       for(int i=0;optarg[i];i++) {
		    if(optarg[i] == 'a') player_is_ai[i] = 'a';
	       }
	       break;
	  default:
	       return 1;
	  }
     }
     if(hrkaux_rootname_equal(sel,"hrkgamex")) {
	  print_all_help();
	  return 0;
     } else if((!strcasecmp(sel,"list"))) {
	  hrkgame::print_games();
	  return 0;
     } else if(!hrkgame::has_game(sel)) {
	  fprintf(stderr,"Error: Game `%s` not found.\n",sel);
	  hrkgame::print_games();
	  return 1;
     }
     
     
     hrkgame::Game * game    = hrkgame::get_game(sel,opt);
     
     bool gameOnGoing;
     do {
	  gameOnGoing = false;
	  for(int i=0;game->players[i];i++) {
	       if(player_is_ai[i]) {
		    gameOnGoing |= game->start(game->players[i],stdout,stderr,flags);
	       } else {
		    gameOnGoing |= game->start(game->players[i],stdin,stdout,stderr,flags);
	       }
	  }
     } while(gameOnGoing);
     printf("\n*****************************************************************\n");
     game->print(game->players[0],stdout,stderr,flags);
     delete game;
     
     return 0;
}
