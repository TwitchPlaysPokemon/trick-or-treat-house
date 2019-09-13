.macro puzzle_info name:req, author:req
.byte MAP_SCRIPT_PUZZLE_HEADER_NAME
.4byte \name
.byte MAP_SCRIPT_PUZZLE_HEADER_AUTHOR
.4byte \author
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

.macro puzzle_quip string:req
.byte MAP_SCRIPT_PUZZLE_HEADER_QUIP
.4byte \string
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
.byte MAP_SCRIPT_PUZZLE_SETUP_SCRIPT
.4byte \pointer
.endm

.macro puzzle_teardown_script pointer:req
.byte MAP_SCRIPT_PUZZLE_TEARDOWN_SCRIPT
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
.endm