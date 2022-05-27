//Octothorpe (12/15/16)
//Shadow, Dock 3

#include <std.h>
#include "../defs.h"
inherit INH+"dock";

void create()
{
   ::create();
   set_exits(([
      "north" : ROOMS"dolanco3",
      "south" : "/d/shadow/virtual/river/shadow.dock",
   ]));
   set_long(::query_long()+" Looking down into the water, you see roof of a sunken %^BOLD%^%^BLACK%^black tower%^RESET%^ peering just above the sea level.");
   add_item(({"tower","black tower"}),"Remnants of an ancient bastion submerged under the water can be seen here. This tower has a trapdoor on top of it. People walking by the dock turn their eyes, either on intent not to be seen seeing it or by compulsion of magic. You think if you brave enough you could <swim to tower> from this spot...");
}

void init()
{
    ::init();
    add_action("swim_to","swim");
}

int swim_to(string str)
{
    tell_room(TO,"%^BLUE%^"+TP->QCN+" quickly descends into the water and swims away.",TP);
    write("%^BLUE%^You quickly descend into the water and make your way to the tower.");
    TP->move(ROOMS+"/assassinoutside");
    TP->force_me("look");
    return 1;
}

void reset(){
    object cargo;
    ::reset();
    if(!present("crates")) new("/d/dagger/islands/wailing_isle/obj/cargo")->move(this_object());
    cargo = present("crates");
    cargo->refresh_cargo();
}

