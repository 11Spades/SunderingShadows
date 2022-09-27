#include <magic.h>

inherit SPELL;

void create()
{
    ::create();
    set_spell_name("freedom");
    set_spell_level(([ "cleric" : 9 ]));
    set_domains( ({ "freedom" }) );
    set_spell_sphere("abjuration");
    set_syntax("cast CLASS freedom on TARGET");
    set_damage_desc("removes paralysis, slow, imprisonment, statue, sleep, tripped");
    set_description("The target is freed from spells and effects that restrict movement, including paralysis, slow, sleep, and tripped. This spell also dispells the statue, imprisonment, and slow spells. Due to the nature of the imprisonment spell and time hop spells, you will only be able to cast this on yourself to remove those effects.

%^BOLD%^%^RED%^See also:%^RESET%^ status effects");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_helpful_spell(1);
}  

void spell_effect(int prof)
{
    object * effects;
    
    if(!objectp(target))
        return;
    
    spell_successful();
    
    tell_object(caster, "%^CYAN%^BOLD%^You unravel the magics holding " + target->query_cap_name() + "!");
    tell_room(place, caster->query_cap_name() + " unravels the magics holding " + target->query_cap_name() + "!", caster);

    effects = target->query_property("spelled");
    effects = filter_array(effects, (: $1->query_spell_name() == "slow" || $1->query_spell_name() == "statue" || $1->query_spell_name() == "imprisonment" || $1->query_spell_name() == "time hop" :));
    
    foreach(object ob in effects)
    {
        tell_object(caster, "You unravel the " + ob->query_spell_name() + " spell.");
        ob->dest_effect();
    }

    if(target->query_paralyzed())
    {
        tell_object(caster, "You remove the paralysis.");
        target->remove_paralyzed();
    }
    
    target->set_asleep(0, 0);
    target->set_tripped(0);
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if(objectp(this_object())) this_object()->remove();
}
