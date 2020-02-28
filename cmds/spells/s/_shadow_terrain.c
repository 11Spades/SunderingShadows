#include <spell.h>
#include <magic.h>
inherit SPELL;

string olddesc;

void create()
{
    ::create();
    set_spell_name("shadow terrain");
    set_spell_level(([ "classless":6]));
    set_spell_sphere("illusion");
    set_domains("cold");
    set_syntax("cast CLASS shadow terrain as DESCRIPTION");
    set_description(".");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed(1);
}

spell_effect()
{
    spell_successful();
    place->set_long(arg);
    target->set_property("spelled", ({TO}) );
    addSpellToCaster();
    call_out("dest_effect", ROUND_LENGTH * (clevel * 4 + roll_dice(1, 20)));
}

dest_effect()
{
    if(objectp(place))
    {
        place->set_long(olddesc);
    }
    ::dest_effect();
}
