//generic inheritable tobacco storage
#include <std.h>
inherit ROOM;
void create()
{
    ::create();
    set_properties((["light" : 1, "indoors" : 1]));
    set("short", "tobacco vendor's cart");
    set("long", "Supplies and such are stored here.\n");
}

void reset()
{
    ::reset();
    if (!present("pirate's booty tobacco")) {
        new("/d/common/obj/misc/tobacco/pirates_booty_tobacco")->move(this_object());
    }
    if (!present("pirate's booty tobacco 2")) {
        new("/d/common/obj/misc/tobacco/pirates_booty_tobacco")->move(this_object());
    }
    if (!present("white dragon tobacco")) {
        new("/d/common/obj/misc/tobacco/white_dragon_tobacco")->move(this_object());
    }
    if (!present("white dragon tobacco 2")) {
        new("/d/common/obj/misc/tobacco/white_dragon_tobacco")->move(this_object());
    }
    if (!present("tsarven tobacco")) {
        new("/d/common/obj/misc/tobacco/tsarven_tobacco")->move(this_object());
    }
    if (!present("tsarven tobacco 2")) {
        new("/d/common/obj/misc/tobacco/tsarven_tobacco")->move(this_object());
    }
    if (!present("hafling's homeblend tobacco")) {
        new("/d/common/obj/misc/tobacco/halflings_homeblend_tobacco")->move(this_object());
    }
    if (!present("hafling's homeblend tobacco 2")) {
        new("/d/common/obj/misc/tobacco/halflings_homeblend_tobacco")->move(this_object());
    }
    if (!present("dwarf's pride tobacco")) {
        new("/d/common/obj/misc/tobacco/dwarfs_pride_tobacco")->move(this_object());
    }
    if (!present("dwarf's pride tobacco 2")) {
        new("/d/common/obj/misc/tobacco/dwarfs_pride_tobacco")->move(this_object());
    }
    if (!present("luxury of tharis tobacco")) {
        new("/d/common/obj/misc/tobacco/luxury_of_tharis_tobacco")->move(this_object());
    }
    if (!present("pipe")) {
        new("/d/common/obj/misc/pipe")->move(this_object());
    }
    if (!present("pipe 2")) {
        new("/d/common/obj/misc/pipe")->move(this_object());
    }
}

void call_reset()
{
    reset();
}
