

#include <std.h>
#include "../outpost.h"

inherit STORAGE"lot.c";


void create() {
    ::create();

set_exits(([
"north" : ROOMS"36",
"south" : ROOMS"34",

]));

}

