#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_terrain(ROCKY);
    set_travel(LEDGE);
    set_property("light",3);
    set_property("indoors",0);
    set_short("%^RESET%^%^BOLD%^%^ORANGE%^Descendi%^WHITE%^n%^ORANGE%^g%^BLACK%^ path%^RESET%^%^RESET%^");
    set_long("%^RESET%^%^BOLD%^%^WHITE%^D%^WHITE%^e%^WHITE%^c%^WHITE%^e%^ORANGE%^n%^WHITE%^d%^ORANGE%^ing%^BLACK%^ path%^RESET%^%^RESET%^
%^RESET%^%^BOLD%^%^BLACK%^The %^ORANGE%^pat%^WHITE%^h%^BLACK%^ widens a bit here. You breathe a little easier as you don't feel the threat of falling to your death weighing quite as heavilly on your thoughts.%^RESET%^%^RESET%^");

    set_listen("default","The waves pound against the rocky coastline coating you in a fine mist of seaspray.");
    set_exits(([

       "east" : "/d/attaya/beach15",
       "southwest" : "/d/attaya/beach13",

    ] ));
    set_items(([
         "beach" : "The beach is comprised of large boulders and smaller jagged stones, carved by the powerful forces that continue to shape this island.",
         "path" : "The path, lined by torches, winds away around the southern cliff face.",
    ] ));
}
