#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();
   has_a_clue=2;

set_exits(([
"southwest" : BONE"8",
"southeast" : BONE"6",

]));

}

