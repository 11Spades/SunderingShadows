#include <spell.h>

inherit SPELL;

create()
{
    ::create();
    set_spell_name("modify memory");
    set_spell_level(([ "assassin" : 4, "bard" : 4, "psion" : 4 ]));
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS modify memory on TARGET");
    set_description("This spell alters the victim's immediate memory so they will not recognize who you are. Should their will falter they will forget your name and will be momentarily dazed.
                    
%^BOLD%^%^RED%^N.B.%^RESET%^ This spell is only meant to modify memory short term, it is not meant to wipe out long term roleplay. The connection between your face and name is removed from the victim, but they still remember that you exist and can recall any past interactions. The victim can also recognize you by name again once an in character event happens that merits doing so, such as an introduction, or being addressed by another player by name.");
    mental_spell();
    diminish_returns();
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_silent_casting(1);
    set_save("will");
}

int preSpell()
{
    /*
    if(caster->cooldown("modify memory"))
    {
        tell_object(caster, "You have to wait to cast this spell again.");
        return 0;
    }
    */
    return 1;
}

string query_cast_string()
{
    tell_room("%^RESET%^%^BLUE%^" + caster->QCN + "%^RESET%^%^BLUE%^ looks at " + target->QCN + "%^RESET%^%^BLUE%^ intently.");
    return "display";
}

void spell_effect(int prof)
{
    if (!present(target, place)) {
        tell_object(caster, "Your target has left.");
        dest_effect();
        return;
    }

    if (!userp(target)) {
        tell_object(caster, "Your target is weird.");
        dest_effect();
        return;
    }

    if (!(do_save(target, -4) && mind_immunity_damage(target) && !caster->query_time_delay("modify_memory", 600))) {
        string caster_profile = caster->query("relationship_profile");

        if (!caster_profile) {
            caster_profile = "default";
        }

        spell_successful();
        
        tell_object(caster, "%^BLUE%^You sense your memory attempt succeeded, and your victim is momentarily dazed.%^RESET%^");
        target->set_paralyzed(roll_dice(1, 3) * 8, "%^RESET%^%^BLUE%^You feel oblivious and momentarily distracted... As if you have forgotten something.%^RESET%^");
        target->remove_relationship_profile(caster->query_true_name(), caster_profile);
        caster->set_time_delay("modify_memory");
    }else {
        tell_object(caster, "%^BLUE%^You sense your memory altering attempt failed. You will have to wait before using modify memory again.%^RESET%^");
        tell_object(target, "You feel someone trying to invade your mind, but you shrug it off.");
        //caster->add_cooldown("modify memory", 60);
    }

    dest_effect();
}

void dest_effect()
{
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
