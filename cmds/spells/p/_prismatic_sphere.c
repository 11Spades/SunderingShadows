/*
  _prismatic_sphere.c

  Creates an invulnerable sphere around the caster. Neither caster
  nor opponents can attack each other.

  --Tlaloc--
*/

#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

#define DELAY 180

object shadow;

void create()
{
    ::create();
    set_spell_name("prismatic sphere");
    set_spell_level(([ "mage" : 9, "cleric" : 9 ]));
    set_domains("protection");
    set_spell_sphere("abjuration");
    set_syntax("cast CLASS prismatic sphere");
    set_save("reflex");
    set_damage_desc("Blindness to enemies on failed reflex save, caster becomes invulnerable.");
    set_description("This spell creates opaque globe of shimmering, multicolored light that surrounds you and protects you from all forms of attack. The sphere flashes in all colors of the visible spectrum, blinding attackers for 2d4 rounds on a failed reflex save. This sphere prevents all forms of attack between you and your attackers. Be warned, this sphere cuts off the magical weave to your summoned minions, causing them to be destroyed. This spell has a cooldown.");
    set_verbal_comp();
    set_somatic_comp();
    set_helpful_spell(1);
}

string query_cast_string()
{
    return "%^CYAN%^BOLD%^" + caster->QCN+" draws arcane runes in tha air and snaps "+caster->QP+" finger.%^RESET%^";
}

int preSpell()
{
    if (caster->query_property("prismatic sphere")) {
        //tell_object(caster, "You are already affected by similar magic.");
        message("failure", "You are already affected by similar magic.", caster);
        return 0;
    }
    
    if(caster->cooldown("prismatic sphere"))
    {
        //tell_object(caster, "You can't use prismatic sphere yet.");
        message("cooldown", "You can't use prismatic sphere yet.", caster);
        return 0;
    }

    return 1;
}

void spell_effect(int prof)
{
    int roll;
    object *attackers, *minions;

    spell_successful();

    attackers = caster->target_selector();

    //tell_object(caster, "%^BOLD%^A globe of flashing prismatic colors forms around you, protecting you from harm!%^RESET%^");
    message("my spells", "%^BOLD%^A globe of flashing prismatic colors forms around you, protecting you from harm!%^RESET%^", caster);
    //tell_room(place, "%^BOLD%^" + caster->QCN + " forms a globe of prismatic colors around " + caster->QO + " with a flash of light!%^RESET%^", ({ caster }));
    message("other spells", "%^BOLD%^" + caster->QCN + " forms a globe of prismatic colors around " + caster->QO + " with a flash of light!%^RESET%^", place, ({ caster }));
    if(sizeof(attackers))
    {
        foreach(object ob in attackers)
        {
            if(clevel < ob->query_level())
                continue;

            if(do_save(ob, 0))
                continue;

            //tell_room(place, "%^BOLD%^" + ob->QCN + " is blinded by the flash!%^RESET%^", ({ ob }));
            message("status effect", "%^BOLD%^" + ob->QCN + " is blinded by the flash!%^RESET%^", place, ({ ob }));
            //tell_object(ob, "%^BOLD%^You are blinded by the flash!%^RESET%^");
            message("status effect", "%^BOLD%^You are blinded by the flash!%^RESET%^", ob);
            ob->set_temporary_blinded(roll_dice(2, 4));
        }
    }

    minions = caster->query_protectors();

    if(sizeof(minions))
    {
        //tell_object(caster, "Your connection to your minions is severed!");
        message("my spells", "Your connection to your minions is severed!", caster);

        foreach(object ob in minions)
        {
            if(ob->query_property("spell_creature") || ob->query_race() == "outsider" || ob->is_undead())
            {
                ob->move("/d/shadowgate/void");
                ob->remove();
            }
        }
    }

    if(!objectp(shadow = new("/cmds/spells/obj/sphere_shadow.c")))
    {
        //tell_object(caster, "There has been an error! Contact a DEV.");
        message("failure", "There as been an error! Submit a bug report.", caster);
        return;
    }
    
    shadow->start_shadow(caster);
    
    addSpellToCaster();
    caster->set_property("spelled", ({TO}));
    caster->set_property("prismatic sphere", 1);
    caster->add_cooldown("prismatic sphere", DELAY);
    caster->set_property("added short",({"%^BOLD%^MAGENTA%^ (surrounded in a magical shell)%^RESET%^"}));

    spell_duration = (2 + (clevel / 10)) * ROUND_LENGTH;
    set_end_time();
    call_out("dest_effect",spell_duration);
}
/*
void execute_attack()
{
    object *attackers,room;
    int i;

    ::execute_attack();
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    room      = environment(caster);
    attackers = caster->query_attackers();
    attackers = filter_array(attackers,"is_non_immortal",FILTERS_D);
    attackers = target_filter(attackers);
    for(i=0;i<sizeof(attackers)&&i<6;i++)
    {
        if(do_save(attackers[i],4))
            continue;
        tell_room(room,"%^CYAN%^"+attackers[i]->QCN+" is pushed away by the prismatic sphere from "+caster->QCN+".%^RESET%^",({attackers[i]}));
        tell_object(attackers[i],"%^CYAN%^You are pushed away by the prismatic sphere around "+caster->QCN+".%^RESET%^");
        attackers[i]->remove_attacker(caster);
        caster->remove_attacker(attackers[i]);
    }
    prepend_to_combat_cycle(room);
}
*/

void dest_effect()
{
    int chance;
    remove_call_out("dest_effect");
    
    objectp(shadow) && shadow->end_shadow();
    
    if (!objectp(caster))
    {
        TO->remove();
        return;
    }

    //tell_object(caster, "%^BOLD%^%^MAGENTA%^The prismatic sphere fades from around you.");
    message("my spells", "%^BOLD%^%^MAGENTA%^The prismatic sphere fades from around you.", caster);
    //tell_room(environment(caster), "%^BOLD%^%^MAGENTA%^The sphere around "+caster->QCN+" fades away.",caster);
    message("other spells", "%^BOLD%^%^MAGENTA%^The sphere around "+caster->QCN+" fades away.", environment(caster), ({ caster }));

    caster->remove_property("prismatic sphere");
    caster->remove_property_value("added short",({"%^BOLD%^MAGENTA%^ (surrounded in a magical shell)%^RESET%^"}));
    caster->remove_property_value("spelled", ({TO}) );
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
