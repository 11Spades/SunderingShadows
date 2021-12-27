#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
inherit SPELL;

int mod, is_sm;

void dest_effect();

void create() {
    ::create();
    set_spell_name("stunning finale");
    set_spell_level(([ "bard" : 5 ]));
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS stunning finale on TARGET");
    set_damage_desc("paralysis, or, staggered for one round on successful save.");
    set_description("With this spell the bard sings a beautiful melody, ending their performance with a stunning finale. The target, and possibly those around it are awe struck by this finale. Those who fail a fortitude save will be utterly paralyzed by this finale, while those who pass their save will be staggered for one round. This spell will end your current performance or inspiration. You must have an inspiration active to use this spell.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    mental_spell();
    set_save("fort");
    splash_spell(1);
}

string query_cast_string() {
    return "%^BOLD%^%^CYAN%^"+caster->query_cap_name() + " begins to sing a stunning refrain.";
}

void spell_effect(int prof)
{
    object *targets, inspire, stagger;
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    
    if(!objectp(target) || !present(target, place))
    {
        tell_object(caster, "Your target is no longer here");
        dest_effect();
        return;
    }
    
    inspire = present("inspiration_obj", caster);
    
    if(!objectp(inspire) || !inspire->query_active_inspiration())
    {
        tell_object(caster, "You don't have an active inspiration.");
        dest_effect();
        return;
    }
    
    spell_successful();
    targets = target_selector();
    
    tell_object(caster, CRAYON_D->color_string("You sing a beautiful melody and, with a flourish, deliver a stunning finale!", "sierra"));
    tell_room(place, CRAYON_D->color_string(caster->query_cap_name() + " sings a beautiful melody and with a flourish, delivers a stunning finale!", "sierra"), caster);
    
    stagger = load_object("/std/effect/status/staggered.c");
    
    foreach(object ob in targets)
    {
        if(!objectp(ob))
            continue;
        
        if(!do_save(ob, 0))
        {
            tell_object(ob, "%^MAGENTA%^BOLD%^The beautiful sound leaves you awe struck!%^RESET%^");
            tell_room(place, "%^MAGENTA%^BOLD%^The beautiful sound leaves " + target->query_cap_name() + " awe struck!%^RESET%^", ob);
            ob->set_paralyzed(ROUND_LENGTH * 3, "You are awe struck by the finale!");
        }
        
        if(!objectp(stagger))
            continue;
        
        tell_object(ob, "%^MAGENTA%^BOLD%^You are staggered by the stunning finale!%^RESET%^");
        tell_room(place, "%^MAGENTA%^BOLD%^The stunning finale staggers " + target->query_cap_name() + "!%^RESET%^", ob);
        stagger->apply_effect(ob, 1);
    }
    
    inspire->remove();
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
