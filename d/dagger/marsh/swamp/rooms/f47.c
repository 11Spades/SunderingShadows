#include <std.h>
#include "../marsh.h"

inherit FINH;

void create()
{
    ::create();
    set_exits(([
                "east": RPATH "f46",
                "north": RPATH "f48",
      ]));
}
