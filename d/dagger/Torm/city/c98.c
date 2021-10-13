//C98
#include <std.h>
#include "../tormdefs.h"

inherit VAULT;

void create()   {
    ::create();
    set_travel(PAVED_ROAD);
    set_terrain(CITY);
    set_property("light",2);
    set_short("%^CRST%^%^RESET%^%^C153%^Outside %^C195%^Th%^C194%^e P%^C188%^ea%^C189%^rl %^C195%^Ne%^C194%^ck%^C188%^la%^C189%^ce%^RESET%^%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C087%^You stand at the entrance of a %^C086%^great mansion%^C087%^. The grounds along the %^C243%^c%^C245%^o%^C247%^b%^C243%^b%^C245%^l%^C247%^e%^C243%^s%^C245%^t%^C247%^o%^C243%^n%^C245%^e p%^C247%^a%^C243%^t%^C245%^h%^RESET%^%^C087%^ are well manicured, the %^C040%^b%^C047%^u%^C040%^sh%^C047%^e%^C040%^s%^RESET%^%^C087%^ and %^C040%^t%^C047%^r%^C040%^e%^C047%^e%^C040%^s%^RESET%^%^C087%^ carefully pruned, and even the %^C040%^i%^C047%^v%^C040%^y%^C087%^ on the walls seems to have been trimmed. The %^C143%^c%^C144%^a%^C143%^rvi%^C144%^ng%^C143%^s%^RESET%^%^C087%^ on the %^C143%^ma%^C144%^ss%^C145%^iv%^C143%^e w%^C144%^al%^C145%^nu%^C143%^t d%^C144%^oo%^C145%^rs%^RESET%^%^C087%^ and the gleaming %^C094%^b%^C100%^ras%^C094%^s h%^C100%^ar%^C094%^dw%^C100%^ar%^C094%^e%^RESET%^%^C087%^ speak of both fine workmanship and a pride in ownership. A %^C245%^sign%^C087%^ hangs over the door, proudly declaring this establishment to be %^C195%^Th%^C194%^e P%^C188%^ea%^C189%^rl %^C195%^Ne%^C194%^ck%^C188%^la%^C189%^ce%^RESET%^%^C087%^.%^CRST%^\n");
    set("night long","The fog creeps up against the doors of this huge mansion but light shines from within. The grounds along the %^C243%^c%^C245%^o%^C247%^b%^C243%^b%^C245%^l%^C247%^e%^C243%^s%^C245%^t%^C247%^o%^C243%^n%^C245%^e p%^C247%^a%^C243%^t%^C245%^h%^RESET%^%^C087%^ are well manicured, the %^C040%^b%^C047%^u%^C040%^sh%^C047%^e%^C040%^s%^RESET%^%^C087%^ and %^C040%^t%^C047%^r%^C040%^e%^C047%^e%^C040%^s%^RESET%^%^C087%^ carefully pruned, and even the %^C040%^i%^C047%^v%^C040%^y%^C087%^ on the walls seems to have been trimmed. The %^C143%^c%^C144%^a%^C143%^rvi%^C144%^ng%^C143%^s%^RESET%^%^C087%^ on the %^C143%^ma%^C144%^ss%^C145%^iv%^C143%^e w%^C144%^al%^C145%^nu%^C143%^t d%^C144%^oo%^C145%^rs%^RESET%^%^C087%^ and the gleaming %^C094%^b%^C100%^ras%^C094%^s h%^C100%^ar%^C094%^dw%^C100%^ar%^C094%^e%^RESET%^%^C087%^ speak of both fine workmanship and a pride in ownership. A %^C245%^sign%^C087%^ hangs over the door, proudly declaring this establishment to be %^C195%^Th%^C194%^e P%^C188%^ea%^C189%^rl %^C195%^Ne%^C194%^ck%^C188%^la%^C189%^ce%^RESET%^%^C087%^.%^CRST%^\n");
    set_smell("default", "%^CRST%^%^RESET%^%^C027%^You smell %^C037%^salt%^C027%^ in the air, and the aroma of %^C193%^f%^C181%^i%^C193%^ne c%^C181%^o%^C193%^ok%^C181%^in%^C193%^g%^RESET%^%^C027%^ from inside.%^CRST%^");
    set_listen("default", "%^CRST%^%^RESET%^%^C030%^The waves of the %^C075%^sea%^C030%^ wash against the %^C101%^docks%^C030%^.%^CRST%^");
    set_items(([
        "mansion" : "%^CRST%^%^RESET%^%^C195%^The %^C175%^mansion%^C195%^ beyond the %^C248%^gates%^C195%^ is incredibly large and impressive. There seems to be a great deal of activity going on inside, and in the city nearby.%^CRST%^",
        "gates" : "%^CRST%^%^RESET%^%^C248%^The gates are made of thick wrought iron. They would be almost impossible to bend. They stand open for all visitors.%^CRST%^",
        "walls" : "%^CRST%^%^RESET%^%^C244%^The walls around the mansion are incredibly high, reaching over thirty feet in height. They are made out of carefully cemented %^C053%^s%^C052%^t%^C058%^o%^C053%^n%^C052%^e %^C058%^b%^C053%^r%^C052%^i%^C058%^c%^C053%^k%^C052%^s%^RESET%^%^C244%^ and there appear to be %^C059%^spikes%^C243%^ on the top of the walls.%^CRST%^",
        "fog" : "%^CRST%^%^RESET%^%^C250%^The %^C255%^fog%^C250%^ has settled around the grounds of the mansion. Although it avoids the building itself, it blankets most of the grass.%^CRST%^",
        "sign" : "%^CRST%^%^RESET%^%^C101%^A fine wooden sign hangs above the door from a %^C244%^decorative %^C059%^black %^C244%^hook%^C101%^. The sign features the %^C059%^silhouette%^C101%^ of a naked woman, lounging with one knee bent in toward her voluptuous chest, while the other is stretched out before her. She plays with a strand of %^C159%^p%^C153%^e%^C159%^arls%^RESET%^%^C101%^ around her neck, her back curved in a delicate arch. Above the image is printed the name of this famous establishment: %^C195%^Th%^C194%^e P%^C188%^ea%^C189%^rl %^C195%^Ne%^C194%^ck%^C188%^la%^C189%^ce%^RESET%^%^CRST%^%^C101%^.%^CRST%^",
        "doors" : "%^RESET%^%^CRST%^%^C101%^These massive doors are solid walnut and have been intricately carved with scenes of sea dragons, nymphs, and other creatures of lore and legend. Heavy brass hinges, knobs, and hardware are burnished to a soft luster.%^CRST%^",
    ]));
    set_exits(([
    "northeast":TCITY+"c10",
    "southwest": "/d/player_houses/lizabelle/entry",
    ]));
    set_door("door","/d/guilds/fist/mansion/entry","southwest");
    set_locked("door",0);
    set_door_description("door", "%^RESET%^%^CRST%^%^C101%^These massive doors are solid walnut and have been intricately carved with scenes of sea dragons, nymphs, and other creatures of lore and legend. Heavy brass hinges, knobs, and hardware are burnished to a soft luster.%^CRST%^");
    set_string("door","open","%^RESET%^%^CRST%^%^C254%^The massive walnut doors swing open soundlessly.%^CRST%^");
    set_string("door","close","%^RESET%^%^CRST%^%^C254%^The massive walnut doors close solidly.%^CRST%^");
}

