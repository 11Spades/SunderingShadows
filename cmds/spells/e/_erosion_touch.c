/*
   _erosion_touch.c

   Nature mystery innate.

   -- Tlaloc --
 */

#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
#include <favored_types.h>

inherit SPELL;

void create()
{
    ::create();
    set_author("tlaloc");
    set_spell_name("erosion touch");
    set_spell_level(([ "innate" : 1 ]));
    set_mystery("nature");
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS erosion touch on TARGET");
    set_damage_desc("Untyped damage on touch attack against construct");
    set_description("With this ability, the caster reaches out and touches a construct. On a successful touch attack, the target becomes more worn and used, and closer to breaking down, causing untyped damage.");
    set_target_required(1);
}

string query_cast_string()
{
    return sprintf("%s extends %s hand and it begins to glow with natural energy.", caster->QCN, caster->QP);
}

void spell_effect(int prof)
{
    string my_name, your_name;


    if (!present(target, environment(caster)))
    {
        tell_object(caster, "Your target is not in this area.\n");
        this_object()->remove();
        return;
    }
    
    if(!USER_D->is_valid_enemy(target->query_race(), "constructs"))
    {
        tell_object(caster, "This spell only works on constructs.");
        dest_effect();
        return;
    }

    my_name = caster->query_cap_name();
    your_name = target->query_cap_name();
    
    spell_successful();

    if(!BONUS_D->process_hit(caster, target, 1, 0, 0, 1))
    {
        tell_object(caster, sprintf("You reach out to touch %s but miss!", your_name));
        tell_object(target, sprintf("%s reaches out to touch you, but misses!", my_name));
        tell_room(place, sprintf("%s reaches out to touch %s, but misses!", my_name, your_name), ({ target, caster }));
        TO->remove();
        return;
    }

    tell_object(caster, "%^ORANGE%^" + sprintf("You reach out with a glowing hand and touch %s, causing wear and tear!", your_name) + "%^RESET%^");
    tell_object(target, "%^ORANGE%^" + sprintf("%s reaches out with a glowing hand and touches you, causing a blast of vapor to erupt!", my_name) + "%^RESET%^");
    tell_room(place, sprintf("%s reaches out with a glowing hand and touches %s, causing a blast of vapor to erupt!", my_name, your_name) + "%^RESET%^", ({ target, caster }));

    damage_targ(target, "chest", sdamage, "untyped");
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
