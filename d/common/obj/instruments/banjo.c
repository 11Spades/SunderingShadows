#include <std.h>
inherit "/d/common/obj/instruments/instrument_inherit.c";

void create(){
    ::create();
    set_name("banjo");
    set_short("A rustic banjo");
    set_id(({"banjo","rustic banjo","instrument"}));
    set_long("This guitar-like instrument is about 24 inches in length.  It has a vellum skin stretched across a round body, much like a tambourine.  Its guitar-like neck stretches away from the body and is fitted with wooden pegs that secure the five metal strings stretched along it.  Some find this music uplifting, while others think the twang of a banjo is appalling.");
   set_weight(5);
   set_value(300);
}

