
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"58",
"northeast" : ROOMS"69",
"southwest" : ROOMS"67",
"southeast" : ROOMS"78",


]));


}

