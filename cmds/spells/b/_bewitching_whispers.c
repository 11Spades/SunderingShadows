#include <spell.h>
#include <magic.h>
#include <daemons.h>
#include <magic_effects.h>
inherit SPELL;

int counter = 0;

void create()
{
    ::create();
    set_spell_name("bewitching whispers");
    set_spell_level(([ "warlock" : 3 ]));
    set_heritage("fey");
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS bewitching whispers [on TARGET]");
    set_damage_desc("continuously confuses target");
    set_description("Dark and seductive voices emerge from the feywild to torment and befuddle your opponent. The weak minded are sent into a frenzy, attacking friend and foe alike. This spell seeks to continuously apply confusion to the target. If they fail a will save, they will gain the confused condition. This effect repeats every round until a will save is made.");
    set_verbal_comp();
    set_somatic_comp();
    //set_target_required(1);
    set_save("will");
}

string query_cast_string()
{
    return "%^C077%^" + caster->query_cap_name() + "%^C244%^ utters a d%^C029%^ar%^C244%^k i%^C029%^n%^C035%^v%^C041%^o%^C035%^c%^C029%^a%^C244%^tion, calling on the voices of the %^C077%^dark%^C244%^ and %^C077%^cunning%^C244%^ fey%^CRST%^";
}

void spell_effect(int prof)
{
    if(!target)
        target = caster->query_current_attacker();
    
    if (!objectp(target)) {
        dest_effect();
        return;
    }
    tell_room(place, "%^C077%^" + caster->query_cap_name() + "%^C244%^ points at %^C077%^" + target->query_cap_name() + "%^C244%^ and d%^C065%^a%^C071%^r%^C244%^k g%^C065%^r%^C071%^e%^C077%^e%^C244%^n t%^C065%^e%^C071%^n%^C077%^d%^C071%^r%^C065%^i%^C244%^ls of foreboding energy race towards %^C077%^" + target->query_objective() + "%^C244%^, uttering s%^C059%^c%^C065%^i%^C071%^n%^C077%^t%^C071%^i%^C065%^l%^C244%^lating w%^C065%^h%^C071%^i%^C077%^s%^C071%^p%^C065%^e%^C244%^rs.%^CRST%^", ({ caster, target }));
    tell_object(caster, "%^C077%^You%^C244%^ point at %^C077%^" + target->query_cap_name() + "%^C244%^ and d%^C065%^a%^C071%^r%^C244%^k g%^C065%^r%^C071%^e%^C077%^e%^C244%^n t%^C065%^e%^C071%^n%^C077%^d%^C071%^r%^C065%^i%^C244%^ls of foreboding energy race towards %^C077%^" + target->query_objective() + "%^C244%^, uttering s%^C059%^c%^C065%^i%^C071%^n%^C077%^t%^C071%^i%^C065%^l%^C244%^lating w%^C065%^h%^C071%^i%^C077%^s%^C071%^p%^C065%^e%^C244%^rs.%^CRST%^");
    tell_object(target, "%^C077%^" + caster->query_cap_name() + "%^C244%^ points at %^C077%^you%^C244%^ and d%^C065%^a%^C071%^r%^C244%^k g%^C065%^r%^C071%^e%^C077%^e%^C244%^n t%^C065%^e%^C071%^n%^C077%^d%^C071%^r%^C065%^i%^C244%^ls of foreboding energy race towards %^C077%^you%^C244%^, uttering s%^C059%^c%^C065%^i%^C071%^n%^C077%^t%^C071%^i%^C065%^l%^C244%^lating w%^C065%^h%^C071%^i%^C077%^s%^C071%^p%^C065%^e%^C244%^rs.%^CRST%^");

    target->set_property("spelled", ({ TO }));
    addSpellToCaster();
    check_confusion();
    spell_successful();
}

void check_confusion()
{
    if (!objectp(target)) {
        dest_effect();
    }

    if (counter > (clevel / 4 + 4)) {
        dest_effect();
    }

    counter++;

    if (!do_save(target, -2)) {
        CONFUSION->confuse(caster, target);
        call_out("check_confusion", ROUND_LENGTH);
    }else {
        tell_room(ENV(target), "%^BOLD%^%^WHITE%^" + target->QCN + " shakes off the confusion.");
        spell_kill(target, caster);
        dest_effect();
    }
}

void dest_effect()
{
    remove_call_out("check_confusion");
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
