
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

set_exits(([
"southwest" : MOUNT"5",
"southeast" : MOUNT"9",

]));

}

