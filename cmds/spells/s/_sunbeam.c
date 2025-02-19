#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
inherit SPELL;

void create() {
    ::create();
    set_spell_name("sunbeam");
    set_spell_level(([ "druid" : 7, "oracle" : 7, "cleric" : 7 ]));
    set_domains("sun");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS sunbeam on TARGET");
    set_damage_desc("radiant damage on ranged touch attack");
    set_description("This spell will create a beam of pure light aimed at the target.  A target who fails to avoid the "
        "sunbeam will take damage from the pure sunlight and may be momentarily blinded.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_save("reflex");
}

string query_cast_string() {
    return "%^YELLOW%^"+caster->QCN+" holds "+caster->QP+" hands together and a bright light begins to emanate from them.";
}

void spell_effect(int prof) {
    int num;
    string target_limb;

    spell_successful();

    if (environment(caster) != environment(target)) {
        tell_object(caster,"Your target has left your range.\n");
        dest_effect();
        return;
    }

    target_limb = target->return_target_limb();

    tell_object(caster,"%^CYAN%^The light between your hands grows to an almost blinding level and you fan your hands out in "+target->QCN+"'s direction, sending "
        "a beam of light right at "+target->QO+"!");
    tell_object(target,"%^CYAN%^The light between "+caster->QCN+"'s hands grows to an almost blinding level and "+caster->QS+" fans "+caster->QP+" hands out "
        "in your direction, sending a beam of light right at you!");
    tell_room(place,"%^CYAN%^The light between "+caster->QCN+"'s hands grows to an almost blinding level and "+caster->QS+" fans "+caster->QP+" hands out "
        "in "+target->QCN+"'s direction, sending a beam of light right at "+target->QO+"!",({caster,target}));


    if(BONUS_D->process_hit(caster, target, 1, 0, 0, 1) > 0)
    {
        tell_object(caster,"%^BOLD%^Your beam of light hits "+target->QCN+" head on, burning "+target->QO+" with its intensity!");
        tell_object(target,"%^BOLD%^"+caster->QCN+"'s beam of light hits you head on, burning you with its intensity.");
        tell_room(place,"%^BOLD%^"+caster->QCN+"'s beam of light hits "+target->QCN+" head on, burning "+target->QO+" with its intensity!",({target, caster}));
        target->set_temporary_blinded(1);
        target->cause_typed_damage(target, target_limb, sdamage, "radiant");
    }
    else {
        if(evade_splash(target)) { dest_effect(); return; }
        tell_object(caster,"%^BLUE%^"+target->QCN+" dodges at the last instant, avoiding your beam of light!");
        tell_object(target,"%^BLUE%^You dodge aside at the last instant, avoiding the damage from "+caster->QCN+"'s beam of light!");
        tell_room(place,"%^BLUE%^"+target->QCN+" dodges aside at the last instant, avoiding the damage from "+caster->QCN+"'s beam of light!",({target, caster}));
    }
    //damage_targ(target,target_limb,sdamage,"divine");
    dest_effect();
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
