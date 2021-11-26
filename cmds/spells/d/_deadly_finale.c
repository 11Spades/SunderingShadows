#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
inherit SPELL;

int mod, is_sm;

void dest_effect();

void create() {
    ::create();
    set_spell_name("deadly finale");
    set_spell_level(([ "bard" : 6 ]));
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS deadly finale on TARGET");
    set_damage_desc("sonic damage to target and splash. rend on failed fort save.");
    set_description("With this spell the bard sings a discordant melody, ending their performance with a deadly finale. The target, and possibly those around it are struck with painful sonic energy. If the affected targets do not make a fortitude save, they are also afflicted with the rend condition as their ears, nose and eyes bleed. This spell will end your current performance or inspiration. You must have an inspiration active to use this spell.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_immunities( ({"sonic"}) );
    set_save("fort");
    splash_spell(1);
}

string query_cast_string() {
    return "%^BOLD%^%^CYAN%^"+caster->query_cap_name() + " begins to sing a deadly refrain.";
}

void spell_effect(int prof)
{
    object *targets, inspire;
    
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
    
    tell_object(caster, CRAYON_D->color_string("You sing a discordant melody and, with a flourish, deliver a deadly finale!", "sierra"));
    tell_room(place, CRAYON_D->color_string(caster->query_cap_name() + " sings a discordant melody and with a flourish, delivers a deadly finale!", "sierra"), caster);
    
    foreach(object ob in targets)
    {
        if(!objectp(ob))
            continue;
        
        tell_object(ob, "%^MAGENTA%^BOLD%^The discordant sound causes you intense pain!%^RESET%^");
        tell_room(place, "%^MAGENTA%^BOLD%^The discordant sound causes " + target->query_cap_name() + " instense pain!%^RESET%^", ob);
        
        if(!do_save(ob, 0))
        {
            tell_object(ob, "%^RED%^BOLD%^You ears, nose, and eyes begin to bleed profusely!%^RESET%^");
            tell_room(place, "%^RED%^BOLD%^" + ob->query_cap_name() + "'s ears, nose and eyes begin to bleed profusely!%^RESET%^", ob);
            ob->set_property("rend", 5);
        }
        
        ob->cause_typed_damage(ob, "torso", sdamage, "sonic");
    }
    
    inspire->remove();
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
