//Holy Orb
#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;


string query_cast_string() { return caster->QCN+" holds "+caster->QP+" hands out in front of "+caster->QO+" and calls upon the heavens."; }


void create()
{
   ::create();
    set_spell_name("spray of shooting stars");
    set_spell_level(([ "oracle" : 6 ]));
    set_spell_sphere("invocation_evocation");
    set_mystery("heavens");
    set_syntax("cast CLASS spray of shooting stars");
    set_damage_desc("radiant damage on attackers, half on reflex save");
    set_description("With this spell, the caster calls upon the power of the heavens to unleash a burst of shooting stars on her foes. This spell will attempt to hit all current attackers, causing radiant damage, or half damage on a successful reflex save.");
    set_verbal_comp();
    set_somatic_comp();
    splash_spell(2);
    set_save("reflex");
}


void spell_effect(int prof)
{
    int damage;
    int i,j;
    object limb;
    object *foes;
    object *party;

    foes = target_selector();
    party = ob_party(caster);

    tell_room(place,"%^BOLD%^A spray of shooting stars erupts from "+caster->QCN+"'s hands!%^RESET%^",caster);
    tell_object(caster,"%^BOLD%^A spray of shooting stars erupts from your hands.%^RESET%^");
    j = sizeof(foes);

    for(i=0;i<j;i++)
    {
        if(!objectp(foes[i])) continue;
        if(foes[i] == caster) continue;
        if(interactive(foes[i]) && foes[i]->query_level() < 6) continue;
        limb = foes[i]->return_target_limb();
        define_base_damage(0);
        damage = sdamage;

        tell_object(caster,"%^BOLD%^%^CYAN%^The radiant energy from your shooting star burns "+foes[i]->QCN+".%^RESET%^");
        tell_room(place,"%^BOLD%^%^CYAN%^The radiant energy from "+caster->QCN+"'s shooting star burns brightly as it engulfs "+foes[i]->QCN+"."+"%^RESET%^",({foes[i],caster}));
        if(!do_save(foes[i],0))
            foes[i]->cause_typed_damage(foes[i], "torso", sdamage, "radiant");
        else
            foes[i]->cause_typed_damage(foes[i], "torso", sdamage, "radiant");
    }
    dest_effect();
}


void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
