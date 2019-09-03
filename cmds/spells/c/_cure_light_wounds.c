#include <std.h>

inherit "/cmds/spells/h/_heal";

void create() {
    ::create();
    set_author("pator");
    set_spell_name("cure light wounds");
    set_spell_level(([ "cleric" : 1, "bard" : 1, "paladin" : 1, "ranger" : 2, "druid" : 1,"paladin":1 ]));
    set_spell_sphere("healing");
    set_syntax("cast CLASS cure light wounds on TARGET");
    set_description("This spell heals wounds on a limb of the target.  It is a nice spell to quickly heal little damages "
"but don't expect too much out of it.  The spell will grow with the caster as he gains in power.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_non_living_ok(1);
	set_helpful_spell(1);
}
