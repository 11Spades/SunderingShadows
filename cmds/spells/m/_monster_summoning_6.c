#include <spell.h>
#include <magic.h>
#include <rooms.h>
inherit "/cmds/spells/m/_monster_summoning_1.c";

create() {
    ::create();
    set_spell_name("monster summoning 6");
    set_spell_level(([ "mage" : 6, "bard" : 6, "cleric" : 6 ]));
    set_syntax("cast CLASS monster summoning 6");
}
