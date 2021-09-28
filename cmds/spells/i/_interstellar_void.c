#include <std.h>
#include <daemons.h>

inherit SPELL;

void create() {
    ::create();
    set_spell_name("interstellar void");
    set_spell_level(([ "innate" : 8 ]));
    set_spell_sphere("invocation_evocation");
    set_mystery("heavens");
    set_syntax("cast CLASS interstellar void on TARGET");
    set_damage_desc("void damage, 1/2 on save. exhausted and paralyzed on failed save.");
    set_description("This spell will strike at the target with the dark void energy of the deepest depths of the cosmos. The target must make a fortitude save or be exhausted and paralyzed by the sheer weight and scale of cosmic reality. A sucessful save will reduce the damage by half.");
    set_save("fortitude");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
}

int preSpell(){
    if(!objectp(target)){
        tell_object(caster,"This spell requires a target.");
        return 0;
    }
    return 1;
}

string query_cast_string(){
    tell_object(caster,"%^BOLD%^%^BLACK%^%^You chant in a secretive whisper, and void energies begin to form in your palm.");
    tell_room(place,"%^BOLD%^%^BLACK%^The darkness swirls around " +caster->QCN+ " congregating in "+caster->QP+" palms.",({ caster }) );
    return "display";
}

void spell_effect(int prof){
    int damage, i;
    object *attackers;

    if(!present(target,place))
    {
        tell_object(caster,"Your target has left.");
        dest_effect();
        return;
    }

    tell_object(caster,"%^BOLD%^%^BLACK%^You hurl your fist towards "+target->QCN+" and a beam of "
        "darkness flows forth towards "+target->QO+".");
    tell_object(target,"%^BOLD%^%^BLACK%^A beam of darkness flows forth from "+caster->QCN+"'s "
        "hand towards you!");
    tell_room(place,"%^BOLD%^%^BLACK%^"+ caster->QCN+" hurls "+caster->QP+" fist forth and a beam "
        "of darkness flows towards "+target->QCN+"!",({ caster, target}) );
        
    if(!do_save(target, 0))
    {
        tell_object(target, "%^BLUE%^The void energy tears into you, slowly unmaking you.");
        tell_room(environment(target), "%^BLUE%^The void energy tears into " + target->QCN + ", threatening to unmake " + target->query_objective() + ".", target);
        target->set_paralyzed(roll_dice(2, 4) * 6);
        "/std/effect/status/exhausted"->apply_effect(target, clevel / 14 + 1);
        target->cause_typed_damage(target, "torso", damage, "void");
    }
    else
    {
        tell_object(target, "%^BLUE%^The void energy strikes you, causing serious pain, but you are able to shrug some of it off.");
        tell_room(environment(caster), "%^BLUE%^The void energy strikes " + target->QCN + ", but " + target->query_pronoun() + " is able to shrug some of it off.", target);
        target->cause_typed_damage(target, "torso", damage / 2, "void");
    }
    spell_kill(target, caster);
    spell_successful();
    dest_effect();
}

void dest_effect(){
    ::dest_effect();
    if(objectp(TO)) TO->remove();

}
