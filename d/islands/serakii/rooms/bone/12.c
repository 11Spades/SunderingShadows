#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();
   has_a_clue=4;

set_exits(([
"southeast" : BONE"11",
"southwest" : BONE"13",

]));

}
