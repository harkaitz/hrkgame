## Process this file with hrkrec
## (1) > hrkrec recording.hrkrec.tcl
## (2) > hrkrec recording.hrkrec.ttyrec
## Once you have the GIF file, add it to the readme.
## ![Recording](recording.rec.gif)
##
## @COPYRIGHT@
hrkrec-speed 100
##
## Show help string.
##
hrkrec-clear
hrkrec-msg "The program has a help string, use `-h`."
hrkrec-sh "hrkgamex -h"
after 2000
hrkrec-msg "Note that with `-c` we can list available moves"
hrkrec-msg "And with -m we can even know which Alpha-beta value the move has"
hrkrec-msg "Let's list available games"
hrkrec-sh "hrkgamex -l"
after 1000
hrkrec-msg "Ummm, tictactoe seems fun. Let's play it agaist the A.I"
hrkrec-msg "Lets make A.I. move first with `-x a-` option."



##
## TICTACTOE
##
set fp [hrkrec-open hrkgamex -g tictactoe -x a-]
after 3000
hrkrec-msg "The format is <X AXIS>,<Y AXIS>"
hrkrec-type $fp "2,2"
after 1000
hrkrec-type $fp "0,1"
after 1000
hrkrec-msg "Hell!!! It beat us !!!"
after 5000
hrkrec-type $fp "1,1"
after 1000
hrkrec-msg "The game ended. We lost."
after 1000


close $fp
