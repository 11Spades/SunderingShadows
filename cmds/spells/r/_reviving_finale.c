#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
inherit SPELL;

int mod, is_sm;

void dest_effect();

void create() {
    ::create();
    set_spell_name("reviving finale");
    set_spell_level(([ "bard" : 3 ]));
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS reviving finale");
    set_damage_desc("positive energy on entire party");
    set_description("With this spell the bard sings a beautiful melody, ending their performance with a revitalizing melody. All members of the bard's party and their followers are healed with positive energy. This spell will end your current performance or inspiration. You must have an inspiration active to use this spell.");
    set_helpful_spell(1);
    set_verbal_comp();
    set_somatic_comp();
}

string query_cast_string() {
    return "%^BOLD%^%^CYAN%^"+caster->query_cap_name() + " begins to sing a restorative refrain.";
}

void spell_effect(int prof)
{
    object *targets, *followers, inspire;
    
    if(!objectp(caster))
    {
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
    
    spell_succesful();
    
    targets = ({  });
    targets = ob_party(caster);
    followers = ({  });
    
    foreach(object ob in targets)
        followers += ob->query_followers();
        
    targets += followers;
    targets = distinct_array(targets);
    
    tell_object(caster, CRAYON_D->color_string("You sing a beautiful melody and, with a flourish, deliver a revitalizing finale!", "sierra"));
    tell_room(place, CRAYON_D->color_string(caster->query_cap_name() + " sings a beautiful melody and with a flourish, delivers a revitalizing finale!", "sierra"), caster);
    
    
    foreach(object ob in targets)
    {
        if(!objectp(ob))
            continue;
        
        tell_object(ob, "%^GREEN%^BOLD%^The beautiful sound soothes your pain!%^RESET%^");
        tell_room(place, "%^GREEN%^BOLD%^The beautiful sound soothes" + target->query_cap_name() + "'s pain!%^RESET%^", ob);
        ob->cause_typed_damage(ob, "torse", sdamage, "positive energy");
    }
    
    inspire->dest_all_effects();
    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
