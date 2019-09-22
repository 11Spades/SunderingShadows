#include <std.h>
#include <daemons.h>
#include <spell.h>
#include <magic.h>
inherit SPELL;

int bonus;

void create()
{
    ::create();
    set_spell_name("kiss of feywild");
    set_spell_level(([ "druid" : 4, "bard" : 4 ]));
    set_spell_sphere("alteration");
    set_syntax("cast CLASS kiss of feywild [on TARGET]");
    set_damage_desc("on living, fast healing 2 (passive regeneration 2d20 per round)");
    set_description("Lo, Their Endless Host, the Harbingers of Life, Mercy and Kindness Followed Where'er She Walked, Where Her Court Will be Held.");
	set_helpful_spell(1);
}

string query_casting_string()
{
    return "%^GREEN%^With %^CYAN%^b%^BOLD%^ou%^RESET%^%^CYAN%^n%^BOLD%^d%^RESET%^%^CYAN%^l%^BOLD%^es%^RESET%^%^CYAN%^s %^MAGENTA%^j%^BOLD%^o%^RESET%^%^MAGENTA%^y %^GREEN%^a song of l%^BOLD%^if%^RESET%^%^GREEN%^e is sang.%^WHITE%^";
}

int preSpell()
{
    if(!target)
        target = caster;
    if(target->query_property("kiss of feywild") &&
       !target->is_undead())
    {
        tell_object(caster,"The spell is repelled by similar magic.");
        TO->remove();
        return 0;
    }
    return 1;
}

void spell_effect()
{
    if(!target)
        target = caster;

    if(!objectp(target))
    {
        TO->remove();
        return;
    }
    if(!objectp(caster))
    {
        TO->remove();
        return;
    }

    tell_room(place,"%^BOLD%^%^GREEN%^A song of life embraces "+target->QCN+"'s body.");
    if(target->is_undead())
    {
        tell_object(target,"%^BOLD%^%^BLACK%^BUT JOY IS %^WHITE%^NOT%^BLACK%^ YOUR WAY%^RESET%^");
        tell_object(caster,"%^BOLD%^%^BLACK%^You feel your spell repelled...%^RESET%^");
        TO->remove();
    }
    else
    {
        int duration = clevel * ROUND_LENGTH * 5;
        tell_object(target,"%^BOLD%^%^GREEN%^You feel more healthy and joyful.");
        target->set_property("spelled",({TO}));
        target->set_property("fast healing",2);
        spell_successful();
        addSpellToCaster();
        call_out("dest_effect",duration);
    }
}

void dest_effect()
{
    if(objectp(target))
    {
        tell_object(target,"%^BOLD%^%^GREEN%^The elation you felt begins to ebb as life's realities return.%^RESET%^");
        target->remove_property_value("spelled", ({TO}) );
        target->set_property("fast healing",-2);
        target->remove_property("kiss of feywild");
    }
    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
