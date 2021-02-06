#include <std.h>
inherit "/std/bag_logic";

void create() {
    set_id( ({"backpack","pack","bag"}) );
    set_name("backpack");
    set("short", "%^RESET%^%^ORANGE%^A leather backpack%^RESET%^");
    set_weight(5);
    set("long", "This is a simple leather backpack that you could put things in.\n");
    set_value(2);
    set_property("treasure_type", "5A");
    set_max_internal_encumbrance(35);
    set_property("repairtype",({ "leatherwork","tailor" }));
}

int is_sack() {
    return 1;
}