#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();
   has_a_clue=1;

set_exits(([
"southwest" : BONE"3",
"southeast" : BONE"5",

]));

}
