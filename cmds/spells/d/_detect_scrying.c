// Detect Scrying
// Informs players if they are being viewed
// by a scrying device
// Thorn@ShadowGate
// 5 January 2001
#include <spell.h>
#include <magic.h>
#include <daemons.h>
#define SCRY_D "/daemon/ic_scry_locate_d"
inherit SPELL;

object detector;

void create()
{
    ::create();
    set_spell_name("detect scrying");
    set_spell_level(([ "mage" : 4, "bard" : 4, "inquisitor" : 4, "cleric" : 4 ]));
    set_domains("knowledge");
    set_spell_sphere("divination");
    set_syntax("cast CLASS detect scrying");
    set_description("The caster of this spell creates a protective weave around themselves that serves as an alarm, warning the caster when they are being scried through magical or psionic means. Anyone scrying the caster must make an opposed spell check, pitting this spell against their scry spell. If they fail the check, their scry STILL succeeds. However, their scry is detected and the detecting caster is given a warning, showing them the location of the scryer in question. This spell cannot run concurrently with other scry protection spells.");
    set_verbal_comp();
    set_somatic_comp();
    set_peace_needed(1);
    set_helpful_spell(1);
}

string query_cast_string()
{
    if (spell_type == "bard") {
        return "%^BOLD%^%^GREEN%^" + caster->QCN + " recites a short rhyme.%^RESET%^";
    }
    return "%^BOLD%^CYAN%^" + caster->QCN + " places " +
           "a tiny hearing trumpet up against a small piece of glass "
           "and places " + caster->QP + " ear to the trumpet!";
}

void spell_effect(int prof)
{
    int num, bonus, power;
    int duration;
    object temp;

    ::spell_effect();

    /*
    if (temp = caster->query_property("detect scrying")) {
        if (!objectp(temp)) {
            caster->remove_property("detect scrying");
        } else {
            tell_object(caster, "%^BOLD%^RED%^You are already detecting "
                        "scrying attempts!");
            if (objectp(TO)) {
                TO->remove();
            }
            return;
        }
    }
    */
    if(caster->query_property("scry detect power") || caster->query_property("scry block power") || caster->query_property("block scrying") || caster->query_property("false vision"))
    {
        tell_object(caster, "There is already scry protection magic on you.");
        dest_effect();
        return;
    }
    tell_room(place, "%^BOLD%^GREEN%^For a brief moment, the air around " +
              "" + caster->QCN + " shimmers with a magical aura!");

    caster->set_property("spelled", ({ TO }));
    bonus = calculate_bonus(caster->query_stats(get_casting_stat()));
    //power = clevel + bonus + random(6);
    power = bonus + clevel + query_spell_level(spell_type);
    /*
    detector = SCRY_D->add_detect_scrying(caster);
    if (!objectp(detector)) {
        tell_object(caster, "%^BOLD%^RED%^Something is wrong that "
                    "a wiz might want to look at!");
        dest_effect();
        return;
    }
    detector->set_detect_power(power);
    */
    caster->set_property("scry detect power", power);
    spell_duration = (clevel + roll_dice(1, 20)) * ROUND_LENGTH * 6;
    set_end_time();
    call_out("dest_effect",spell_duration);
    addSpellToCaster();
    return;
}

void dest_effect()
{
    if (objectp(caster)) {
        tell_object(caster, "%^CYAN%^%^BOLD%^The magic detecting scrying fades from around you.%^RESET%^");
        caster->remove_property_value("spelled", ({ TO }));
        caster->remove_property("scry detect power");
    }
    if (objectp(detector)) {
        detector->self_destruct();
    }
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
