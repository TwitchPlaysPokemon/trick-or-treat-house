.macro puzzle_info name:req, author:req, flags=0, author2=NULL
.byte MAP_SCRIPT_PUZZLE_HEADER_NAME
.4byte \name
.byte MAP_SCRIPT_PUZZLE_HEADER_AUTHOR
.4byte \author
.byte MAP_SCRIPT_PUZZLE_HEADER_FLAGS
.4byte \flags
.byte MAP_SCRIPT_PUZZLE_HEADER_AUTHOR_INTRO
.if \author2 == NULL
	.4byte \author
.else
	.4byte \author2
.endif
.endm

.macro puzzle_item_prereqs list:req
.byte MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST
.4byte \list
.endm

.macro puzzle_remove_after list:req
.byte MAP_SCRIPT_PUZZLE_HEADER_POST_LIST
.4byte \list
.endm

.macro puzzle_adjective string:req
.byte MAP_SCRIPT_PUZZLE_HEADER_ADJECTIVE
.4byte \string
.endm

.macro puzzle_quip string:req, speaker=NULL
.byte MAP_SCRIPT_PUZZLE_HEADER_QUIP
.4byte \string
.if \speaker != NULL
	.byte MAP_SCRIPT_PUZZLE_HEADER_QUIP_SPEAKER
	.4byte \speaker
.endif
.endm

.macro puzzle_custom_intro string:req
.byte MAP_SCRIPT_PUZZLE_CUSTOM_INTRO
.4byte \string
.endm

.macro puzzle_metavars pointer:req
.byte MAP_SCRIPT_PUZZLE_META_VARIABLES
.4byte \pointer
.endm

.macro puzzle_setup_script pointer:req
.byte MAP_SCRIPT_ON_PUZZLE_SETUP
.4byte \pointer
.endm

.macro puzzle_teardown_script pointer:req
.byte MAP_SCRIPT_ON_PUZZLE_TEARDOWN
.4byte \pointer
.endm

.macro puzzle_candylist pointer:req
.byte MAP_SCRIPT_PUZZLE_CANDY_LIST
.4byte \pointer
.endm

.macro puzzle_devcommentary pointer:req
.byte MAP_SCRIPT_PUZZLE_DEV_COMMENTARY
.4byte \pointer
.endm

.macro puzzle_friendcommentary pointer:req
.byte MAP_SCRIPT_PUZZLE_FRIEND_COMMENTARY
.4byte \pointer
.endm

@ -----------------------------------------------------

GATE_SHAPE_L1 = 0
GATE_SHAPE_L2 = 1
GATE_SHAPE_L3 = 2
GATE_SHAPE_L4 = 3
GATE_SHAPE_T1 = 4
GATE_SHAPE_T2 = 5
GATE_SHAPE_T3 = 6
GATE_SHAPE_T4 = 7
GATE_SHAPE_T5 = 8 	@ normally unused
GATE_SHAPE_T6 = 9   @ normally unused
GATE_SHAPE_T7 = 10  @ normally unused
GATE_SHAPE_T8 = 11  @ normally unused

GATE_ORIENTATION_0   = 0
GATE_ORIENTATION_90  = 1
GATE_ORIENTATION_180 = 2
GATE_ORIENTATION_270 = 3

.macro gate_puzzle_config x:req, y:req, shape:req, orientation:req
.2byte \x
.2byte \y
.byte \shape
.byte \orientation
.2byte 0 @ padding
.endm

@ -----------------------------------------------------

.macro do_rotating_tile x:req
playse SE_SWITCH
waitse
playse SE_REPEL
initrotatingtilepuzzle 1
moverotatingtileobjects \x
waitmovement 0
turnrotatingtileobjects
waitmovement 0
freerotatingtilepuzzle
.endm

@ -----------------------------------------------------

.macro set_meta_visited_flag flag:req
setflag FLAG_PUZZLE_20 + (\flag & 0xFF)
.endm

.macro check_meta_visited_flag flag:req
checkflag FLAG_PUZZLE_20 + (\flag & 0xFF)
.endm
