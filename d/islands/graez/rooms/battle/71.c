
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"61",
"northeast" : ROOMS"72",
"southeast" : ROOMS"81",


]));


}

