/*
  _resist_death.c
  
  Egoist power that protects from death and negative energy.
  
  -- Tlaloc --
*/

#include <spell.h>
#include <daemons.h>
#include <magic.h>

inherit SPELL;

void create()
{
    ::create();
    
    set_spell_name("resist death");
    set_spell_level(([ "psion" : 4 ]));
    set_spell_sphere("psychometabolism");
    set_discipline("egoist");
    set_syntax("cast CLASS resist death [on TARGET]");
    set_damage_desc("death ward and 25% negative energy resistance");
    set_description("The manifester combines life force and psionic energy into a shield that protects the target from negative energy attacks and death attacks. The target gains immunity to death effects and 25% negative energy resistance.");
    set_helpful_spell(1);
}

int preSpell()
{
    if (!target) {
        target = caster;
    }

    if (target->query_property("no death")) {
        tell_object(caster, "They are already under the influence of a similar effect.");
        return 0;
    }
    return 1;
}

void spell_effect()
{
    if (!objectp(target) || !objectp(place))
    {
        dest_effect();
        return;
    }
    
    spell_successful();
    
    tell_object(caster, "%^CYAN%^BOLD%^You combine your life force with your psionic powers and erect a barrier of protection around " + (caster == target ? "yourself" : target->query_cap_name()) + ".%^RESET%^");
    tell_room(place, "%^CYAN%^BOLD%^" + caster->query_cap_name() + " combines " + caster->query_possessive() + " life force and psionic energy, erecting a barrier of protection around " + target->query_cap_name() + ".", caster);
    
    target->set_property("no death", 1);
    target->set_resistance_percent("negative energy", 25);
    
    if(target != caster)
        addSpellToTarget();
    
    addSpellToCaster();
    spell_duration = (clevel + roll_dice(1, 20)) * ROUND_LENGTH * 12;
    set_end_time();
    call_out("dest_effect",spell_duration);
}

void dest_effect()
{
    if(objectp(target))
    {
        tell_object(target, "%^BOLD%^%^WHITE%^You feel the psionic barrier protecting you from death fade away.%^RESET%^");
        target->set_property("no death", -1);
        target->set_resistance_percent("negative energy", -25);
    }
    
    ::dest_effect();
    
    if (objectp(TO))
        TO->remove();
}
    
    