
// --==** /cmds/priest/_heal.c **==--
// Modified by Pator@ShadowGate
// August 25 1995
#include <priest.h>

inherit SPELL;

void create()
{
    ::create();
    set_spell_name("harm");
    set_spell_level(([ "cleric" : 6,"inquisitor":6 ]));
    set_affixed_spell_level(6);
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS harm on TARGET");
    set_damage_desc("negative energy");
    set_description("%^RESET%^This spell will channel huge amount of negative energy into target and will allow the caster to cause massive amount damage. This spell will cure status effects such as blinded, confused, dazzled, paralyzed, fatigued, exhausted, sickened and will clear negative levels.");
    set_save("will");
    set_target_required(1);
    set_helpful_spell(1);
}


string query_cast_string()
{
    string cast;
    if (interactive(caster))
    {
        cast = "%^BOLD%^%^BLACK%^"+caster->QCN+" folds "+caster->QP+" hands as "+caster->QS+" prays for a divine spell!\n";
    }
    else
    {
        cast = "%^BOLD%^%^BLACK%^"+caster->QCN+" calls for a divine spell!\n";
    }
    return "\n"+cast;
}


spell_effect(int prof)
{
    int rnd, wound;

    set_helpful_spell(1);
    if(!(target->query_property("negative energy affinity")))
        set_helpful_spell(0);
    if (interactive(caster))
    {
        if ( caster == target )
        {
            tell_object(caster, "%^BOLD%^%^BLACK%^You reach out and channel fell energy at yourself.");
            tell_room(place, "%^BOLD%^%^BLACK%^"+YOU+" channels fell energy at "+caster->QO+"self.", ({ caster, target}) );
        }
        else
        {
            tell_object(caster, "%^BOLD%^%^BLACK%^You channel fell energy at "+target->QCN+".");
            tell_room(place, "%^BOLD%^%^BLACK%^"+YOU+" channels fell energy at "+target->QCN+".",({ caster}) );
        }
    }
    else
    {
        tell_room(environment(caster), "%^BOLD%^%^BLACK%^"+caster->QCN+" sends a beam of energy to "+target->QCN+".",({ caster, target }) );
        tell_object(target, "%^BOLD%^%^BLACK%^"+caster->QCN+" sends a beam of fell energy at you.");
    }

    rnd = sdamage * 7/6;
    wound = damage_targ(target, target->return_target_limb(), rnd, "negative energy");
    
    if(!help_or_harm && wound > 0 && spell_type == "oracle")
    {
        
        if(caster->query_mystery() == "lunar" && caster->query_class_level("oracle") >= 31)
        {
            set_save("will");
            if(!do_save(target, 0))
            {
                tell_room(place, "%^BOLD%^The pull of the moon assaults " + target->query_cap_name() + "'s mind!", target);
                tell_object(target, "%^BOLD%^The pull of the moon assaults your mind!");
                "/std/effect/status/confused"->apply_effect(target,clevel/5+1,caster);
            }
            set_save();
        }
    }           

    if(query_spell_name()=="harm")
        if(member_array(target,caster->query_attackers())==-1)
            "/std/magic/cleanse"->cleanse(target);

    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
