//Rewritten by Tlaloc 2021
#include <std.h>
#include <spell.h>
#include <magic.h>
inherit SPELL;

int current;
string target_limb;

void create() {
    ::create();
    set_author("tlaloc");
    set_spell_name("powerword kill");
    set_spell_level(([ "mage" : 9, "cleric" : 9 ]));
    set_domains(({ "war" }));
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS powerword kill on TARGET");
    set_damage_desc("untyped. death on failed save, ~50% current health on successful save, lesser effect splashed");
    set_save("fortitude");
    set_description("The caster utters a word of power which seeks to unravel the very nature of the target. Any target with less than 75% of their maximum health must make a death save or be immediately killed. Otherwise, the target takes the half (modified by level differences) of their current HP in untyped damage. All other enemies must also make a death save if their health is below 25%. They otherwise take a quarter of their current HP as untyped damage.");
    mental_spell();
    set_verbal_comp();
    //set_silent_casting(1);
    set_target_required(1);
    splash_spell(3);
     // school specific mage spell
}

string query_cast_string()
{
    return "%^BOLD%^%^BLACK%^" + caster->QCN + " begins to utter a word of undoing.%^RESET%^";
}

void spell_effect(int prof)
{
    int difflevel, myoutput, mydmg;
    object *targets;

    if (!target || !present(target,environment(caster)))
    {
        tell_object(caster,"%^BOLD%^Your target is not in this area.\n");
        dest_effect();
        return;
    }
    
    tell_object(caster,"%^BOLD%^%^GREEN%^You take in a deep breath and scream the words, 'GRIMMUS MORRTES!!!'");
    tell_room(place,"%^BOLD%^%^GREEN%^"+caster->QCN+" takes in a deep breath and screams the words, 'GRIMMUS MORRTES!!!'",({caster}));
    spell_successful();
    spell_kill(target, caster);

    current = target->query_hp();
    targets = target_selector() - ({ target });
    
    if((current * 100) / target->query_max_hp() < 75 &&
    !combat_death_save(target, 0) &&
    !mind_immunity_damage(target))
    {
        tell_object(target,"%^BOLD%^You reel backward in utter agony, and the world around you goes black!");
        tell_room(place,"%^BOLD%^"+target->QCN+" screams in agony and then falls to the ground, dead!",({target}));
        target->set_hp(-100);
    }
    else
    {
        tell_object(target,"%^BOLD%^You feel a tug at your life force, but with some difficulty you fight it off!");
        tell_room(place,"%^BOLD%^"+target->QCN+" staggers in pain momentarily, but soon recovers.",({target}));
        difflevel = clevel - target->query_base_character_level();
        mydmg = (target->query_hp() * (50 + difflevel)) / 100;
        mydmg = min( ({ mydmg, 600 }) );
        target && target->cause_typed_damage(target, target->return_target_limb(), mydmg, "untyped");
    }
    
    foreach(object ob in targets)
    {
        if(!objectp(ob))
            continue;
        
        if((ob->query_hp() * 100) / ob->query_max_hp() < 25)
        {
            if(!combat_death_save(ob, 0) && !mind_immunity_damage(ob))
            {
                tell_object(ob,"%^BOLD%^You reel backward in utter agony, and the world around you goes black!");
                tell_room(place, "%^BOLD%^" + ob->QCN + " drops dead from the word of power!%^RESET%^", ({ ob }));
                ob->set_hp(-100);
                continue;
            }               
        }
        tell_object(ob,"%^BOLD%^You painfully fight off the word of power!");
        tell_room(place,"%^BOLD%^"+target->QCN+" staggers in pain momentarily, but soon recovers.",({ ob }));
        difflevel = clevel - ob->query_base_character_level();
        mydmg = (ob->query_hp() * (25 + difflevel)) / 100;
        mydmg = min( ({ mydmg, 300 }) );
        ob && ob->cause_typed_damage(ob, ob->return_target_limb(), mydmg,"untyped");
    }
    
    spell_kill(target, caster);
    dest_effect();
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
