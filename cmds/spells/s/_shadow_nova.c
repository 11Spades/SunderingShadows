// sunburst equiv for shadow adept (since sunburst is very clearly not appropriate to use with this feat)
#include <std.h>
#include <daemons.h>

inherit SPELL;


void create()
{
    ::create();
    set_author("nienne");
    set_spell_name("shadow nova");
    set_spell_level(([ "innate" : 9 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS shadow nova");
    set_damage_desc("void");
    set_description("This spell will send a burst of pure darkness out in a circle from the caster.  Any enemies "
        "caught in the area will suffer damage from the shadowy energy.  Those creatures who fail their save will find that "
        "the darkness also steals away their vision temporarily.

%^BOLD%^%^RED%^See also:%^RESET%^ status effects");
    set_verbal_comp();
    set_somatic_comp();
    splash_spell(2);
    set_save("reflex");
}


string query_cast_string()
{
    tell_object(caster,"%^RESET%^%^C026%^You can feel a %^RESET%^%^C051%^c%^C087%^h%^C123%^i%^C087%^l%^C051%^l %^RESET%^%^C026%^growing in the %^RESET%^%^C087%^air %^RESET%^%^C026%^as you chant.%^CRST%^");
    tell_room(place,"%^RESET%^%^C026%^A %^RESET%^%^C051%^c%^C087%^h%^C123%^i%^C159%^l%^C195%^l%^C123%^i%^C087%^n%^C051%^g %^RESET%^%^C051%^a%^C123%^u%^C159%^r%^C051%^a %^RESET%^%^C026%^surrounds "+caster->QCN+" %^RESET%^%^C026%^as "+caster->QS+" %^RESET%^%^C026%^begins to chant.%^CRST%^",caster);
    return "display";
}


void spell_effect(int prof)
{
    object *attackers;
    int i;

    attackers = target_selector();

    if(!sizeof(attackers))
    {
        tell_object(caster,"%^RESET%^%^C242%^The area is plunged into %^RESET%^%^C240%^utter darkness%^RESET%^%^C242%^, but nothing else happens.%^CRST%^");
        dest_effect();
        return;
    }

    tell_room(place,"%^RESET%^%^C242%^The area is plunged into %^RESET%^%^C240%^utter darkness%^RESET%^%^C242%^, the touch of the %^RESET%^%^C240%^void %^RESET%^%^C045%^c%^C051%^h%^C087%^i%^C123%^l%^C159%^l%^C087%^i%^C051%^n%^C045%^g %^RESET%^%^C242%^your very %^RESET%^%^C159%^soul%^RESET%^%^C242%^!%^CRST%^");

    for(i=0;i<sizeof(attackers);i++)
    {
        if(!objectp(attackers[i])) continue;
        if(!do_save(attackers[i],0))
        {
            tell_object(attackers[i],"%^RESET%^%^C241%^You %^RESET%^%^C249%^b%^C250%^l%^C251%^i%^C250%^n%^C249%^k %^RESET%^%^C241%^several times, but your vision remains clouded by complete %^RESET%^%^C240%^darkness%^RESET%^%^C241%^!%^CRST%^");
            attackers[i]->set_temporary_blinded(1);
        }
        tell_object(attackers[i],"%^RESET%^%^C242%^The unnatural %^RESET%^%^C051%^c%^C087%^h%^C123%^i%^C087%^l%^C051%^l %^RESET%^%^C242%^of the %^RESET%^%^C240%^void %^RESET%^%^C242%^sears your very %^RESET%^%^C159%^soul%^RESET%^%^C242%^!%^CRST%^");
        damage_targ(attackers[i],attackers[i]->return_target_limb(),sdamage,"void");
    }

    spell_successful();
    dest_effect();
}


void dest_effect()
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
