#include <std.h>
#include <spell.h>
#include <daemons.h>

inherit SPELL;

create() {
    ::create();
    set_spell_name("inspiring recovery");
    set_spell_level(([ "psion" : 5 ]));
    set_spell_sphere("psychometabolism");
    set_discipline("egoist");
    set_syntax("cast CLASS inspiring recovery on TARGET");
    set_damage_desc("healing or revive recently deceased");
    set_description("You channel psychic energy into the target, helping their body repair their wounds or resuscitate them if they're deceased. Does not work on undead creatures or constructs.

This spell accepts the recognized player's name or their corpse as the TARGET if they are deceased.
");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_non_living_ok(1);
	set_helpful_spell(1);
}

string what_alignment(int align)
{
    string alignment;
    switch(align)
    {
    case 1: alignment = "Lawful Good"; break;
    case 2: alignment = "Lawful Neutral"; break;
    case 3: alignment = "Lawful Evil"; break;
    case 4: alignment = "Neutral Good"; break;
    case 5: alignment = "True Neutral"; break;
    case 6: alignment = "Neutral Evil"; break;
    case 7: alignment = "Chaotic Good"; break;
    case 8: alignment = "Chaotic Neutral"; break;
    case 9: alignment = "Chaotic Evil"; break;
    }
    return alignment;
}

spell_effect(int prof) {
    string what, theirname, dam_type;
    object corpse, targ;

    ::spell_effect();

    if(!objectp(target))
    {
        theirname = caster->realName(lower_case(arg));
        target = find_player(theirname);
    }

    if(!objectp(target))
    {
        tell_object(caster,"The target is needed.");
        dest_effect();
    }

    if(target->is_corpse()||target->query_ghost())
    {
        if(target->is_corpse())
            corpse = target;
        else
            corpse = present("corpse of $&$"+target->query_true_name()+"$&$",place);

        if (!interactive(target)) {
            tell_object(caster,"You can only revive interactive players.");
            dest_effect();
            return;
        }
        if (interactive(caster) ) {
            set_cast_string(caster->QCN+" calls upon the magic!\n");
            tell_object(caster, "%^ORANGE%^You attempt to resuscitate "+capitalize(arg)+".");
            tell_room(environment(CASTER), "%^ORANGE%^"+caster->QCN+" tries to resuscitate "+capitalize(arg)+".", ({ caster, target}));
        } else {
            set_cast_string(caster->QCN+" channels psychic energy into "+capitalize(arg)+", attempting to resuscitate them!\n");
        }
        if (!target->query_ghost()) {
            tell_object(caster,capitalize(arg)+" does not need to be revived.");
            dest_effect();
            return;
        }
        if (!objectp(corpse)) {
            tell_object(caster,capitalize(arg)+"'s corpse is not here.");
            tell_object(target,"You think you feel a faint pull on your soul, but it is gone as soon as it begins.");
            dest_effect();
            return;
        }
        tell_object(caster,"%^ORANGE%^You can feel psychic energy flow out to "+target->QCN+"'s body, and know that "+target->QP+" life is in "+target->QP+" own hands now.");
        tell_room(environment(caster),"The power of "+caster->QCN+"'s psychic energy flows through the area as "+caster->QS+" tries to bring "+target->QCN+" back to life!",caster);
        target->set("RaisingPriestGod",caster->query_property("hidden deity")||caster->query_diety());
        target->set("RaisingPriestAlignment",caster->query_alignment());
        target->set("RaisingRoom",base_name(environment(caster)));
        target->set("RaisingExpLoss",(-10+(random(2)+random(3)+1)));
        target->set("RaisingType","raise dead");
        tell_object(target,"%^RESET%^%^WHITE%^%^BOLD%^You can feel a pull on your soul. You sense that psychic energy is trying to return you to consciousness!\nType %^ORANGE%^<accept>%^WHITE%^ to return to life, or %^ORANGE%^<cancel>%^WHITE%^ to die.%^RESET%^");
        corpse->remove();
    }
    else
    {
        if(target->is_undead() || USER_D->is_valid_enemy(target->query_race(), "constructs"))
        {
            tell_room(place,"%^BLUE%^"+caster->QCN+" places "+caster->QP+" hand on "+target->QCN+" and channels psychic energy into them, but nothing happens!", caster);
        }
        else
        {
            tell_room(place,"%^ORANGE%^"+caster->QCN+" places "+caster->QP+" hand on "+target->QCN+" wills their body to heal!");
            damage_targ(target, "torso", -sdamage, "untyped");
        }
    }
    dest_effect();
}

void dest_effect(){
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
