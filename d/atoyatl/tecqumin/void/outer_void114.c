#include <std.h>
#include <move.h>
#include "../tecqumin.h"

inherit TECVOID + "outer_void_base.c";
int vacuum;

string long_desc();

void create()
{
    ::create();
    vacuum = 1;
    set_exits(([     "left" : TECVOID + "outer_void113",
                     "up" : TECVOID + "inner_void107",
                     "right" : TECVOID + "outer_void115",
                     "backward" : TECVOID + "outer_void14"  ]));
    set_heart_beat(1);
}
