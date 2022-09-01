#include <std.h>
#include <daemons.h>
#include <spell.h>
#include <magic.h>

inherit SPELL;

void create() {
    ::create();
    set_spell_name("howl of doom");
    set_spell_level(([ "warlock" : 3 ]));
    set_heritage("abyssal");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS howl of doom");
    set_damage_desc("splash sonic damage and shaken");
    set_description("You utter a howl of doom from the abyss causing sonic damage and unspeakable horror on enemies around you. Those who pass the save will take half damage. Those who fail a will save will be shaken.");
    splash_spell(3);
    set_save("will");
}

void spell_effect(int prof){
    object *attackers;
    int i, temp;
    
    attackers = target_selector();

    tell_room(place, "%^C078%^" + caster->query_cap_name() + " lets loose a horrifying howl from the depths of the abyss!%^CRST%^", ({ caster }));
    tell_object(caster, "%^C078%^You let loose a horrifying howl from the depths of the abyss!%^CRST%^");
    
    if(!sizeof(attackers))
    {
        dest_effect();
        return;
    }

    foreach(object ob in attackers)
    {
        if(!ob)
            continue;
        
        temp = sdamage;
        
        tell_object(ob, "%^C078%^An unbearable howl crashes into your ears and mind, threatening to lay you low!%^CRST%^");
        
        if(do_save(ob))
        {
            tell_object(ob, "%^BOLD%^You grit your teeth and force yourself to resist the incessant fear!%^RESET%^");
            tell_room(place, "%^BOLD%^" + ob->query_cap_name() + " resists the howl of doom!%^RESET%^", caster);
            temp /= 2;
        }
        else
        {
            "/std/effect/status/shaken"->apply_effect(target,roll_dice(4,6));
            tell_object(ob, "%^BLACK%^BOLD%^You are shaken to your very core by the abyssal howl.%^RESET%^");
            tell_room(place, "%^BLACK%^BOLD%^" + ob->query_cap_name() + " is shaken to the core by the howl.%^RESET%^", caster);
        }
            
        damage_targ(ob, ob->return_target_limb(), temp, "sonic");
    }
    spell_successful();
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    
    if(objectp(this_object()))
        this_object()->remove();
}
