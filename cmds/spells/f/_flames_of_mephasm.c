#include <spell.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

int num;
string my_name, your_name;

void create()
{
    ::create();
    set_spell_name("flames of mephasm");
    set_spell_level(([ "warlock" : 2 ]));
    set_heritage("infernal");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS flames of mephasm on TARGET");
    set_damage_desc("fire damage over time");
    set_description("You unleash the very fires of the nine hells upon your target, spraying them with flowing, blackened flames that instantly catch them alight. The target can make a reflex save to avoid the flames altogether. If the target fails, they will be caught on fire and will continue to burn for several rounds.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_save("reflex");
}

string query_cast_string()
{
    return "%^C244%^" + caster->query_cap_name() + " utters a %^C166%^f%^C172%^o%^C178%^u%^C166%^l i%^C172%^n%^C178%^v%^C184%^o%^C178%^c%^C166%^ation%^C244%^ and " + caster->query_possessive() + " eyes begin to glow %^C166%^red hot%^C244%^.%^CRST%^";
}

void spell_effect()
{   
    spell_successful();
    
    my_name = caster->query_cap_name();
    your_name = target->query_cap_name();
    
    tell_object(caster, "%^C166%^You extend your palm towards %^C172%^" + your_name + "%^C166%^ and unleash a wave of %^C244%^b%^C246%^l%^C248%^a%^C250%^c%^C184%^k%^C178%^e%^C172%^n%^C166%^e%^C244%^d%^C166%^ %^C244%^h%^C246%^e%^C248%^l%^C178%^l%^C172%^i%^C166%^s%^C244%^h%^C166%^ %^C244%^f%^C246%^l%^C248%^a%^C178%^m%^C172%^e%^C166%^s upon %^C172%^" + target->query_objective() + ".%^CRST%^");
    tell_object(target, "%^C166%^" + my_name + " extends a palm towards %^C172%^you%^C166%^ and unleashes a wave of %^C244%^b%^C246%^l%^C248%^a%^C250%^c%^C184%^k%^C178%^e%^C172%^n%^C166%^e%^C244%^d%^C166%^ %^C244%^h%^C246%^e%^C248%^l%^C178%^l%^C172%^i%^C166%^s%^C244%^h%^C166%^ %^C244%^f%^C246%^l%^C248%^a%^C178%^m%^C172%^e%^C166%^s.%^CRST%^");
    tell_room(place, "%^C166%^" + my_name + " extends a palm towards %^C172%^" + your_name + "%^C166%^ and unleashes a wave of %^C244%^b%^C246%^l%^C248%^a%^C250%^c%^C184%^k%^C178%^e%^C172%^n%^C166%^e%^C244%^d%^C166%^ %^C244%^h%^C246%^e%^C248%^l%^C178%^l%^C172%^i%^C166%^s%^C244%^h%^C166%^ %^C244%^f%^C246%^l%^C248%^a%^C178%^m%^C172%^e%^C166%^s upon %^C172%^" + target->query_objective() + ".%^CRST%^", ({ target, caster }));
    
    if(do_save(target, 0))
    {
        tell_room(place, "%^BOLD%^" + your_name+ " manages to avoid the flames!%^RESET%^", target);
        tell_object(target, "%^BOLD%^You manage to avoid the flames!%^RESET%^");
        dest_effect();
        return;
    }
    else
    {
        tell_room(place, "%^C166%^" + your_name + " is engulfed in hellish flames!%^CRST%^", target);
        tell_object(target, "%^C166%^You are engulfed in hellish flames!%^CRST%^");
        damage_targ(target, target->return_target_limb(), sdamage, "fire");
    }
    
    num = clevel / 8 + 1;
    call_out("burn_me", ROUND_LENGTH);
}

void burn_me()
{
    if(!objectp(target))
    {
        dest_effect();
        return;
    }
    
    place = environment(target);
    define_base_damage(0);
    
    tell_room(place, "%^C184%^" + your_name + " burns with h%^C178%^e%^C172%^l%^C166%^l%^C248%^i%^C246%^s%^C244%^h%^C184%^ f%^C178%^i%^C172%^r%^C184%^e!%^CRST%^", target);
    tell_object(target, "%^C184%^You burn with h%^C178%^e%^C172%^l%^C166%^l%^C248%^i%^C246%^s%^C244%^h%^C184%^ f%^C178%^i%^C172%^r%^C184%^e!%^CRST%^");
    damage_targ(target, target->return_target_limb(), sdamage / 6, "fire");
    
    if(num-- <= 0)
        dest_effect();
    else
        call_out("burn_me", ROUND_LENGTH);
}

void dest_effect()
{
    remove_call_out("burn_me");
    
    if(objectp(target))
    {
        place = environment(target);
        tell_object(target, "%^C166%^The hellish flames subside.%^CRST%^");
        tell_room(place, "%^C166%^The hellish flames on " + your_name + " subside.%^CRST%^", target);
    }
    
    ::dest_effect();
    if(objectp(this_object()))
        this_object()->remove();
}
    