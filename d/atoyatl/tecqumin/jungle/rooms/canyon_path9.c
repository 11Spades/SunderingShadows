#include <std.h>
#include <move.h>
#include "../../tecqumin.h"

inherit CANYON_PATH;

void create() {
  ::create();
  side = "east";
  set_exits((["up"   : JUNG_ROOM + "canyon_path10",
              "south"   : JUNG_ROOM + "canyon_path8"
    ]));
}
