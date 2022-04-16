#include <spell.h>
#include <magic.h>
#include <daemons.h>

#define SCRY_D "/daemon/ic_scry_locate_d"

inherit SPELL;

object blocker, temp, temp2;
int FLAG;

void create()
{
    ::create();
    set_spell_name("mind blank");
    set_spell_level(([  "mage" : 8 ]));
    set_spell_sphere("abjuration");
    set_syntax("cast CLASS mind blank on TARGET");
    set_damage_desc("protection from mental spells, scry protection");
    set_bonus_type("resistance");
    set_description("This power shields the character's mind. The mental fortress provides the same benefits as the Escape Detection or Protection from scrying power as well as offering additional protection against mind-affecting spells and powers.");
    set_helpful_spell(1);
    set_target_required(1);
}


int preSpell()
{
    if(temp2 = target->query_property("mind blank"))
    {
        if(!objectp(temp))
        {
            target->remove_property("mind blank");
        }
        else
        {
            tell_object(caster,"%^BOLD%^%^MAGENTA%^That target is already "
                "protected by mind blank!%^RESET%^");
        }
        return 0;
    }

    if(target->query_property("scry block power") || target->query_property("scry detect power"))
    {
        tell_object(caster, "%^BOLD%^MAGENTA%^You are already protected by blocking magic!");
        return 0;
    }
    
    /*
    if(temp = target->query_property("block scrying"))
    {
        if(!objectp(temp))
        {
            target->remove_property("block scrying");
        }
        else
        {
            tell_object(caster,"%^BOLD%^%^MAGENTA%^You are already "
                "protected by blocking magic!%^RESET%^");
        }
        return 0;
    }
    */
    return 1;
}


string query_cast_string()
{
    tell_room(environment(caster),"%^BOLD%^%^BLACK%^"+caster->QCN+" lifts a hand, and "
        "c%^RESET%^%^CYAN%^r%^BOLD%^y%^GREEN%^st%^CYAN%^a%^RESET%^"
        "%^CYAN%^l%^BOLD%^%^BLACK%^s s%^RESET%^w%^BOLD%^i%^RESET%^r"
        "%^BOLD%^%^BLACK%^l over "+caster->QP+" palm, growing and "
        "multiplying into a miniature u%^RESET%^%^CYAN%^n%^BOLD%^i"
        "%^GREEN%^ve%^CYAN%^r%^RESET%^%^CYAN%^s%^BOLD%^%^BLACK%^e.%^RESET%^", caster);
    tell_object(caster,"%^BOLD%^%^BLACK%^You lift a hand, and "
        "c%^RESET%^%^CYAN%^r%^BOLD%^y%^GREEN%^st%^CYAN%^a%^RESET%^"
        "%^CYAN%^l%^BOLD%^%^BLACK%^s s%^RESET%^w%^BOLD%^i%^RESET%^r"
        "%^BOLD%^%^BLACK%^l over your palm, growing and "
        "multiplying into a miniature u%^RESET%^%^CYAN%^n%^BOLD%^i"
        "%^GREEN%^ve%^CYAN%^r%^RESET%^%^CYAN%^s%^BOLD%^%^BLACK%^e.%^RESET%^");
    return "display";
}


void spell_effect(int prof)
{
    int num, int_bonus,power, mylevel;
    int duration;
    object temp;
    string *TmpFeats;
    ::spell_effect();

    if(temp = target->query_property("block scrying"))
    {
        if(!objectp(temp))
        {
            target->remove_property("block scrying");
        }
        else
        {
            tell_object(caster,"%^BOLD%^%^MAGENTA%^There is already blocking "
                "magic working for that target!%^RESET%^");
            dest_effect();
            return;
        }
    }

    mylevel = clevel;

    tell_room(place,"%^RESET%^%^MAGENTA%^The %^RESET%^s%^BOLD%^w%^CYAN%^i%^RESET%^"
        "%^CYAN%^rl%^BOLD%^i%^WHITE%^n%^RESET%^g %^MAGENTA%^crystals blossom into a "
        "brilliant expanse of %^BOLD%^%^BLACK%^n%^RESET%^i%^CYAN%^g%^BOLD%^ht %^RESET%^"
        "%^CYAN%^s%^RESET%^k%^BOLD%^%^BLACK%^y %^RESET%^%^MAGENTA%^before coalescing "
        "around "+target->QCN+", bathing "+target->QO+" in %^CYAN%^i%^BOLD%^%^CYAN%^r%^RESET%^"
        "%^CYAN%^id%^RESET%^e%^CYAN%^s%^BOLD%^c%^BLACK%^e%^RESET%^%^CYAN%^n%^RESET%^c"
        "%^CYAN%^e %^MAGENTA%^before winking out of existence.%^RESET%^",caster);
    tell_object(caster,"%^RESET%^%^MAGENTA%^The %^RESET%^s%^BOLD%^w%^CYAN%^i%^RESET%^"
        "%^CYAN%^rl%^BOLD%^i%^WHITE%^n%^RESET%^g %^MAGENTA%^crystals blossom into a "
        "brilliant expanse of %^BOLD%^%^BLACK%^n%^RESET%^i%^CYAN%^g%^BOLD%^ht %^RESET%^"
        "%^CYAN%^s%^RESET%^k%^BOLD%^%^BLACK%^y %^RESET%^%^MAGENTA%^before coalescing "
        "around " + target->QCN + ", bathing " + target->QO + " in %^CYAN%^i%^BOLD%^%^CYAN%^r%^RESET%^"
        "%^CYAN%^id%^RESET%^e%^CYAN%^s%^BOLD%^c%^BLACK%^e%^RESET%^%^CYAN%^n%^RESET%^c"
        "%^CYAN%^e %^MAGENTA%^before winking out of existence.%^RESET%^");

    TmpFeats = target->query_temporary_feats();
    if(!sizeof(TmpFeats)) TmpFeats = ({});

    if(member_array("unyielding soul",TmpFeats) != -1 || FEATS_D->usable_feat(target,"unyielding soul") ||
    member_array("presence of mind",TmpFeats) != -1 || FEATS_D->usable_feat(target,"presence of mind") ||
    member_array("mind partition",TmpFeats) != -1 || FEATS_D->usable_feat(target,"mind partition"))
    {
        FLAG = 0;
    }
    else
    {
        tell_object(target,"%^BOLD%^%^CYAN%^You feel the fortification of your mind "
            "slide into place.%^RESET%^");
        target->add_temporary_feat("unyielding soul");
        FLAG = 1;
    }

    caster->set_property("spelled",({TO}));
    target->set_property("mind blank",1);
    //blocker = SCRY_D->add_block_scrying(target);

    /*
    if(!objectp(blocker))
    {
        tell_object(caster,"%^BOLD%^RED%^Something is wrong that "
            "a wiz might want to look at!%^RESET%^");
        dest_effect();
        return;
    }
    */

    int_bonus = calculate_bonus(caster->query_stats(get_casting_stat()));
    //power = mylevel + int_bonus + random(6);
    power = clevel + int_bonus + query_spell_level(spell_type);
    //blocker->set_block_power(power);
    duration = 5 * mylevel * ROUND_LENGTH;
    spell_successful();
    addSpellToCaster();
    target->set_property("scry block power", power);
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect",spell_duration);
    return;
}

void dest_effect() {
    if(objectp(blocker)) blocker->self_destruct();
    if(objectp(target))
    {
        target->remove_property_value("spelled", ({TO}) );
        target->remove_property("scry block power");
        if(FLAG)
        {
           target->remove_temporary_feat("unyielding soul");
        }
        target->remove_property("mind blank");
        tell_object(target,"%^RESET%^%^MAGENTA%^Your mind blank fades away, "
        "leaving you vulnerable to prying eyes.%^RESET%^");
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
