#include "../../undead.h"
inherit INH+"street";

void create() {
    ::create();
    set_long(::query_long() +"  All along the western edge of the road spreads "
"the sprawling bulk of a %^RED%^military barracks%^RESET%^, with soldiers "
"constantly coming and going.\n");

    set_exits(([
        "north":TOWN"street16",
"west" : "/d/islands/graez/rooms/city/smith",
        "east":TOWN"street14",
    ]));
}
