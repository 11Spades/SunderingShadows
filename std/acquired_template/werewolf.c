#include <std.h>


/*
  Based on rules in Lords of the wild
  Werewolf lycanthropy powers are in werewolf shapes
*/

string *races_allowed()
{
    return ({"human", "elf", "half-elf", "drow", "half-drow", "half-orc", "beastkin", "dwarf", "half-dwarf"});
}

mapping innate_spells()
{
    return ([ "commune with nature" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
        "darkvision" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
        "heart of the wild" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
        "werewolf shape" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
        ]);
}


int apply_template(object ob)
{
    ob->set("werewolf",1);
    return 1;
}

int remove_template(object ob)
{
    ob->delete("werewolf");
    return 1;
}
