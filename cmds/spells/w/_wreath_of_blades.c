/*
  _wreath_of_blades.c
  
  Used 4 mithral daggers in the casters inventory to create
  a travelling AOE effect that does silver damage.
  
  -- Tlaloc --
*/

#include <magic.h>
#include <spell.h>

inherit SPELL;

int timer,flag,stage,toggle,counter,num;
object *daggers;

void create()
{
    ::create();
    set_spell_name("wreath of blades");
    set_spell_level(([ "mage" : 7, "magus" : 6 ]));
    set_spell_sphere("abjuration");
    set_syntax("cast CLASS wreath of blades");
    set_damage_desc("silver damage to attackers");
    set_description("With this arcane incantation, the caster animates mithral daggers in their inventory, causing them to spin around the caster in a protective barrier, striking all enemies who venture too close with silver damage. The damage amount scales with the number of daggers in the caster's inventory, up to four. The damage also scales with the enchantment on those daggers. The amount of enchantment used is based on the casters level. This spell does not utilize things like poison or spell enchantments on the daggers. A dagger can be occasionally lost under certain conditions (like if you die while the spell is active). Mithral daggers can be purchased in a magic shop.");
    set_property("magic",1);
    set_casting_time(1);
    set_helpful_spell(1);
    traveling_aoe_spell(1);
}

string query_cast_string()
{
    tell_object(caster,"%^BOLD%^%^CYAN%^You draw arcane runes in the air and mutter an incantation.");
    tell_room(place,"%^BOLD%^%^CYAN%^" + caster->query_cap_name() + " draws arcane runes in the air and mutters an incantation.",caster);
    return "display";
}

int preSpell()
{
    if(!present("mithral dagger", caster))
    {
        tell_object(caster, "You must have at least one mithral dagger in your inventory to use this spell.");
        return 0;
    }
    
    return 1;
}

void spell_effect(int prof)
{
    object ob;
    ::spell_effect();
    
    daggers = ({  });
    
    if(ob = present("mithral dagger 4", caster))
        daggers += ({ ob });
    if(ob = present("mithral dagger 3", caster))
        daggers += ({ ob });
    if(ob = present("mithral dagger 2", caster))
        daggers += ({ ob });
    if(ob = present("mithral dagger 1", caster))
        daggers += ({ ob });
    
    tell_room(place, "%^BOLD%^" + caster->query_cap_name() + " waves " + caster->query_possessive() + " hand and a wreath of spinning daggers appears around " + caster->query_objective() + "!", caster);
    tell_object(caster, "%^BOLD%^You wave a hand and a wreath of spinning daggers appears around you!");
   
    foreach(object dagger in daggers)
        dagger->move("/d/magic/room/space");
        
    caster->set_property("spelled", ({TO}));
    caster->set_property("added short",({"%^CYAN%^ (wreathed by daggers)%^RESET%^"}));
    addSpellToCaster();
    counter = 8 * clevel;
    spell_duration = counter * ROUND_LENGTH;
    set_end_time();
    execute_attack();
    call_out("room_check",ROUND_LENGTH);
}

void room_check()
{
    if(!objectp(caster) || !objectp(environment(caster)))
    {
        dest_effect();
        return;
    }

    prepend_to_combat_cycle(environment(caster));

    call_out("room_check",ROUND_LENGTH * 2);
    return;
}

void execute_attack(){
    object *foes, targ;
    int i, dam, enchant;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    if(!objectp(caster))
    {
        dest_effect();
        return;
    }

    if(!objectp(environment(caster)))
    {
        dest_effect();
        return;
    }

    place = environment(caster);

    if(!objectp(place) || counter<0)
    {
        dest_effect();
        return;
    }

    foes = caster->query_attackers();

    if (sizeof(foes))
    {
        define_base_damage(0);    //reroll each turn
            
        dam = sdamage / 4;        
        dam *= sizeof(daggers);
        
        foreach(object ob in daggers)
        {
            if(!objectp(ob))
                continue;
            
            enchant = min( ({ ob->query_property("enchantment"), caster->query_character_level() / 5 }) );
            dam += enchant;
        }
        
        tell_object(caster, "%^BOLD%^Your wreath of blades %^RED%^slices%^WHITE%^ your enemies as they get close!");
        tell_room(place, "%^BOLD%^" + caster->query_cap_name() + "'s wreath of blades tears into " + caster->query_possessive() + " enemies as they get too close!", caster);
        
        foreach(object foe in foes)
            foe && foe->cause_typed_damage(foe, "torso", dam, "silver");
    }
    
    prepend_to_combat_cycle(place);
    counter--;
}

void dest_effect()
{
    remove_call_out("room_check");
    if (objectp(caster))
    {
        foreach(object dagger in daggers)
            objectp(dagger) && dagger->move(caster);
            
        tell_room(environment(caster), "%^CYAN%^The spinning wreath of blades around " + caster->query_cap_name() + " slows down and disappears.", caster);
        tell_object(caster, "%^CYAN%^The spinning wreath of blades around you slows down and disappears.");
        caster->remove_property_value("added short", ({ "%^CYAN%^ (wreathed by daggers)%^RESET%^" }));
    }
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
