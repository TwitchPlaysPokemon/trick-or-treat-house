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
