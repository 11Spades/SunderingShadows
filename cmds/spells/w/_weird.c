#include <std.h>
#include <daemons.h>
#include <spell.h>
#include <magic.h>


inherit SPELL;

void create() {
    ::create();
    set_spell_name("weird");
    set_spell_level(([ "mage" : 9,"oracle":9 ]));
    set_mystery("whimsy");
    set_spell_sphere("illusion");
    set_syntax("cast CLASS weird");
    set_damage_desc("mental, cowering");
    set_description("With this spell, caster extends fears and horrors of own mind into material plane, causing pain and suffering to everything in sight. Only a strong will can withstand this power, and only to avoid some of the suffering..");
    set_verbal_comp();
    set_somatic_comp();
    splash_spell(1);
    set_save("will");
}

string query_cast_string() {
    return "%^CYAN%^"+caster->QCN+" speaks words of arcane horror.";
}

void spell_effect(int prof){
    object *attackers;
    int i,admg;
    attackers = caster->query_attackers();
    attackers = filter_array(attackers, "is_non_immortal",FILTERS_D);
    attackers = target_filter(attackers);

    tell_room(place,"%^CYAN%^"+caster->QCN+" raises "+caster->QP+" hands and releases waves of horrific images!%^RESET%^");
    if(!sizeof(attackers)){
        tell_object(caster,"%^BOLD%^%^BLUE%^The place is filled with images of horrors, but nothing happens.%^RESET%^");
        dest_effect();
        return;
    }

    for(i=0;i<sizeof(attackers);i++){
        if(!objectp(attackers[i])) continue;
        define_base_damage(0);
        admg=sdamage;
        if(do_save(target))
        {
            if(evade_splash(attackers[i])) continue;
            admg=admg/2;
        }
        else
        {
            "/std/effect/status/cowering"->apply_effect(attackers[i],clevel/18 + 1);
        }
        tell_object(attackers[i],"%^CYAN%^Your mind is filled with images of suffering!%^RESET%^");
        damage_targ(attackers[i],attackers[i]->return_target_limb(),admg,"mental");
    }
    spell_successful();
    dest_effect();
}

void dest_effect(){
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
