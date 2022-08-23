//      Armor
//      Thorn@Shadowgate w/ lots of help from Melnmarn
//      1/19/95
//      Wizard Spells
//      armor.c
//      Modified and updated by Vashkar
#include <spell.h>
#include <daemons.h>
inherit SPELL;

int benchmark,tally,bonus;

void create()
{
    ::create();
    set_spell_name("armor of shadows");
    set_spell_level(([ "warlock" : 1 ]));
    set_bonus_type("armor");
    set_heritage("gloom");
    set_spell_sphere("illusion");
    set_syntax("cast CLASS armor of shadows [on TARGET]");
    set_damage_desc("+4 to AC");
    set_description("Calling on their bond to their patron, the warlock draws upon the shadows to bolster their defenses.");
    set_verbal_comp();
    set_somatic_comp();
    set_property("keywords", ({ "defensive", "targeted", "personal" }));
    set_helpful_spell(1);
    set_arg_needed(1);
}

int preSpell()
{
    if (!target) target = caster;
    /*
    if(target->query_property("armoured"))
    {
        tell_object(caster,"%^BOLD%^%^BLACK%^You feel your spell repelled...");
        return 0;
    }
    */
    return 1;
}

void spell_effect(int prof)
{
    bonus = 4;

    if (!target) target = caster;

    if (!present(target,environment(caster)))
    {
        tell_object(caster,"%^RESET%^%^CRST%^%^C110%^Your target is not in this area.\n%^CRST%^");
        TO->remove();
        return;
    }

    benchmark = target->query_hp();
    tally = 0;

    /*
    if (!target->is_ok_armour("mage"))
    {
        tell_object(caster,"The spell can not offer protection to those wearing armor.");
        if(objectp(TO)) { TO->remove(); }
        return;
    }
    */

    spell_successful();

    if (target == caster)
    {
        tell_object(caster,"%^RESET%^%^CRST%^%^C110%^Focusing your will, the nearby %^C059%^shadows %^C243%^s%^C245%^l%^C247%^i%^C249%^t%^C243%^h%^C245%^e%^C247%^r %^RESET%^%^C110%^towards you, encasing your body before seeming to solidify and %^C104%^bolster %^C110%^you.%^CRST%^");
        tell_room(place,"%^RESET%^%^CRST%^%^C110%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ closes their eyes for a moment as the nearby %^C059%^shadows %^C243%^s%^C245%^l%^C247%^i%^C249%^t%^C243%^h%^C245%^e%^C247%^r %^RESET%^%^C110%^towards and encase their body.%^CRST%^", caster );
    }

    else
    {
        tell_object(caster,"%^RESET%^%^CRST%^%^C110%^Focusing your will, the nearby %^C059%^shadows %^C243%^s%^C245%^l%^C247%^i%^C249%^t%^C243%^h%^C245%^e%^C247%^r %^RESET%^%^C110%^towards "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^, encasing their body.%^CRST%^");
        tell_object(target,"%^RESET%^%^CRST%^%^C110%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ closes their eyes for a moment as the nearby %^C059%^shadows %^C243%^s%^C245%^l%^C247%^i%^C249%^t%^C243%^h%^C245%^e%^C247%^r %^RESET%^%^C110%^towards you, encasing your body before seeming to solidify and %^C104%^bolster %^C110%^you.%^CRST%^");
        tell_room(place,"%^RESET%^%^CRST%^%^C110%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ closes their eyes for a moment as the nearby %^C059%^shadows %^C243%^s%^C245%^l%^C247%^i%^C249%^t%^C243%^h%^C245%^e%^C247%^r %^RESET%^%^C110%^towards "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ and encase their body.%^CRST%^",({caster, target}) );
    }

    target->add_ac_bonus(bonus);
    target->set_property("spelled", ({TO}) );
    //target->set_property("armoured",1);
    addSpellToCaster();
    call_out("test", 7);
}


void test()
{
    int max_damage, add_tally, thp;

    if (!objectp(target))
    {
        remove();
        return;
    }

    /*if (!target->is_ok_armour("mage"))
    {
        tell_object(caster,"The spell can not offer protection to those wearing armor.");
        TO->dest_effect();
        return;
    }*/

    if (!objectp(target))
    {
        dest_effect();
        return;
    }

    call_out("test", 7);
    return 0;
}


void dest_effect()
{
    if (find_call_out("test") != -1) remove_call_out("test");

    if(objectp(target))
    {
        target->add_ac_bonus(-1 * bonus);
        target->remove_property_value("spelled", ({TO}) );
        tell_object(target, "%^RESET%^%^CRST%^%^C110%^The %^C059%^shadows %^C110%^wreathed about you disperse, leaving you exposed.%^CRST%^");
        tell_room(environment(target),"%^RESET%^%^CRST%^%^C110%^The %^C059%^shadows %^C110%^wreathed about "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ disperse.%^CRST%^", target );
        //target->remove_property("armoured");
    }

    ::dest_effect();
    if(objectp(TO)) TO->remove();
}


string query_cast_string() { return "%^RESET%^%^CRST%^%^C110%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C110%^ murmurs beseeching words, their hands outstretched to the nearby %^C059%^shadows%^C110%^.%^CRST%^"; }
