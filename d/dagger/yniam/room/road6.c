// Chernobog (3/15/22)
// Interior Yniam Road

#include <std.h>
#include "../defs.h"
inherit INH"road2";

void create(){
    ::create();
    set_exits(([
        "northwest" : ROOMS"road5",
        "southeast" : ROOMS"road7",
        ]));
}

