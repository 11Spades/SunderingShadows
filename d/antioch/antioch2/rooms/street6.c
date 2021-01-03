#include <std.h>
#include "../antioch.h"

inherit CVAULT;

void create()
{
    set_monsters(({ "/d/antioch/antioch2/mons/patrol_guard", }), ({ roll_dice(1, 4) + 1, }));
    ::create();
    set_terrain(CITY);
    set_travel(PAVED_ROAD);
    set_property("indoors", 0);
    set_property("light", 2);
    set_short("An intersection");
    set_long(
        "%^WHITE%^You are standing at the intersection of Pine, Cherry, and Apple. To the west is a large building with the %^ORANGE%^sign%^WHITE%^ of a %^BOLD%^%^BLACK%^s%^RESET%^%^ORANGE%^table%^WHITE%^ over the doorway. You can hear animals moving about within it and the smell of horses is strong in the air here. Apple street moves up to the northwest and it turns to the east at what is probably another intersection. %^MAGENTA%^Cherry street%^RESET%^heads east through the main part of town and you can see many shops along the way. There is also a large %^CYAN%^f%^BOLD%^%^CYAN%^o%^RESET%^%^CYAN%^untain%^WHITE%^ in the center of the street up ahead. It crosses over to connect with Crescent, and there appears to be a %^BOLD%^%^ORANGE%^ch%^WHITE%^u%^ORANGE%^rc%^WHITE%^h%^RESET%^%^WHITE%^ at the opposite end of the street. Pine runs to the southeast and meets with Crescent not far from the city gates.
"
        );
    set_smell("default", "There is a smell of horses coming from" +
              " the west.");
    set_listen("default", "You can hear horses neighing and stomping" +
               " in their stalls.");
    set_items(([
                   "street sign" : "You are at the intersection of Apple, Cherry" +
                   " and Pine.",
                   "sign" : "There is a wooden sign with the symbol of a stables" +
                   " hanging over the doorway of the building on the west.",
                   ({ "stables", "building" }) : "This large building appears to be a stables.",
                   "fountain" : "There is a large fountain in the middle of" +
                   " %^MAGENTA%^Cherry street%^RESET%^",
                   "church" : "At the end of %^MAGENTA%^Cherry street%^RESET%^there appears to be" +
                   " a large church.",
                   ({ "street", "cobblestones", "cobbles", "road", "path" }) : "The" +
                   " street is paved with cobblestones.",
                   ]));
    set_exits(([
                   "west" : ROOMS + "stables",
                   "east" : ROOMS + "street18",
                   "north" : ROOMS + "street7",
                   "south" : ROOMS + "street5",
                   ]));
}

void reset()
{
    ::reset();
    if (!present("street_light")) {
        new(OBJ + "street_light")->move(TO);
    }
    if (query_night() == 1) {
        return;
    }else if (!present("citizen")) {
        switch (random(4)) {
        case 0:
            new(MONS + "citizen1")->move(TO);
            break;
        case 1:
            new(MONS + "citizen2")->move(TO);
            break;
        case 2:
            new(MONS + "citizen3")->move(TO);
            break;
        case 3:
            new(MONS + "citizen4")->move(TO);
            break;
        }
    }
}
