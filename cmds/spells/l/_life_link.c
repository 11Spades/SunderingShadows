#include <std.h>
#include <clock.h>
#include <magic.h>

inherit SPELL;

int duration;

void create(){
    ::create();
    set_spell_name("life link");
    set_spell_level(([ "innate" : 3 ]));
    set_spell_sphere("healing");
    set_mystery("life");
    set_syntax("cast CLASS life link on TARGET");
    set_damage_desc("Periodically transfer 5% of your max health to target if injured");
    set_description("This ability will tether your target's life force to your own, turning you into a well of latent healing energy for that person. If the target is below full health, you will periodically transfer 5% of your health, as positive energy, to them. This spell will not perform a transfer if your health is below 50%.");
    set_verbal_comp();
    set_property("magic",1);
    set_target_required(1);
	set_helpful_spell(1);
}

string query_cast_string(){
   tell_object(caster,"%^ORANGE%^With a touch of your holy symbol, you "+
      "begin a worshipful prayer to "+(string)caster->query_diety()+" "+
      "to help heal you.%^RESET%^");
   tell_room(place,"%^ORANGE%^"+caster->QCN+" touches "+caster->QP+" "+
      "holy symbol and calls upon "+caster->QP+" deity's "+
      "blessings!%^RESET%^",caster);
    return "display";
}

int preSpell()
{
    if(target == caster)
    {
        tell_object(caster, "You can't target yourself with this ability.");
        return 0;
    }
    if(target->query_property("life link") || caster->query_property("life link"))
    {
        tell_object(caster,"%^BOLD%^%^WHITE%^You feel your spell repelled...");
        return 0;
    }
    return 1;
}

void spell_effect(int prof){
    int duration = clevel * ROUND_LENGTH * 10;
    
    ::spell_effect();

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

    tell_room(place,"%^BOLD%^%^ORANGE%^A radiant light bathes "+target->QCN+" briefly.");
    target->set_property("spelled",({TO}));
    target->set_property("life link",1);
    addSpellToCaster();
    spell_duration = duration;
    set_end_time();
    call_out("heal_pulse", ROUND_LENGTH);
    call_out("dest_effect",spell_duration);
}

void heal_pulse()
{
    int amount;
    
    if(!objectp(caster) || !objectp(target))
    {
        dest_effect();
        return;
    }
    
    if(caster->query_hp() > caster->query_max_hp() / 2 && target->query_hp() < target->query_max_hp())
    {
        amount = caster->query_max_hp() / 20;
        tell_object(caster, "%^GREEN%^You feel some of your health transfer to " + target->query_cap_name() + ".");
        tell_object(target, "%^GREEN%^You feel yourself healed by the life link.");
        caster->add_hp(-amount);
        target->cause_typed_damage(target, "torso", amount, "positive energy");
    }
    call_out("heal_pulse", ROUND_LENGTH);
}
        
void dest_effect()
{
    if(objectp(target))
    {
        tell_object(target,"%^BOLD%^%^ORANGE%^You feel the life link fade.%^RESET%^");
        target->remove_property_value("spelled", ({TO}) );
        target->remove_property("life link");
    }
    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
