/*
  _harrowstorm.c
  
  Abyssal pact persistent AOE with control.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>
#include <spell.h>
#include <magic.h>

inherit SPELL;

int flag;

void create()
{
    ::create();
    set_spell_name("harrowstorm");
    set_spell_level(([ "warlock" : 4 ]));
    set_heritage("abyssal");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS harrowstorm");
    set_damage_desc("AOE sonic, electicity, force and tripped");
    set_description("You call up a churning cyclone from the Abyss, surrounding your enemies with deafening claps of thunder and powerful strikes of lightning, hurling them about for a short time. Those who don't make a reflex save will be knocked prone.");
    set_save("reflex");
    set_verbal_comp();
    set_somatic_comp();
    aoe_spell(1);
    set_aoe_message("%^C244%^(h%^C059%^a%^C065%^r%^C071%^r%^C077%^o%^C071%^w%^C065%^s%^C059%^t%^C244%^orm)%^CRST%^");
}

void spell_effect(int prof)
{
    tell_object(caster, "%^C065%^You raise curled hands to the sky and utter an invocation wrought from the depths of the abyss.%^CRST%^");
    tell_room(place, "%^C065%^" + caster->query_cap_name() + " raises curled hands to the sky and utters an invocation in an abyssal language.%^CRST%^", caster);
    spell_successful();
    addSpellToCaster();
    execute_attack();
    call_out("dest_effect", clevel * ROUND_LENGTH * 3);
}

void execute_attack()
{
    object *targets;
    
    if(!objectp(caster) || !objectp(place) || environment(caster) != place || !objectp(this_object()))
    {
        dest_effect();
        return;
    }
    
    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }
    
    message("info", "%^C059%^Screeching %^C065%^dark winds, %^C071%^resounding thunder%^C059%^ and %^C077%^powerful lightning%^C059%^ wreak havock on the area.%^CRST%^", place);
    
    targets = target_selector();
    targets -= ({ caster });
    
    foreach(object ob in targets)
    {
        if(!objectp(ob))
            continue;
        
        if(!do_save(ob, 0))
        {
            tell_object(ob, "%^C077%^You are sent sprawling by the vicious fury of the harrowstorm!%^CRST%^");
            tell_room(place, "%^C077%^" + ob->query_cap_name() + " is sent sprawling by the vicious fury of the harrowstorm!%^CRST%^", ob);
            ob->set_tripped(roll_dice(1, 2), "%^BOLD%^You are prone from the effects of the harrowstorm.%^RESET%^");
        }
        
        tell_object(ob, "%^C065%^Clawing winds%^C059%^, %^C071%^vicious thunder%^C059%^ and %^C077%^lightning%^C059%^ tear at your very soul!%^CRST%^");
        ob->cause_typed_damage(ob, ob->return_target_limb(), sdamage / 3, "sonic");
        ob->cause_typed_damage(ob, ob->return_target_limb(), sdamage / 3, "electricity");
        ob->cause_typed_damage(ob, ob->return_target_limb(), sdamage / 3, "force");
    }
    
    place->addObjectToCombatCycle(this_object(),1);
}

void dest_effect()
{
    if(objectp(place))
        tell_room(place, "%^C065%^The harrowstorm fades away.%^CRST%^");
    
    ::dest_effect();
    
    if(objectp(this_object()))
        this_object()->remove();
}
    