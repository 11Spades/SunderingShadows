#include <priest.h>
#include <magic.h>
#include <spell.h>

inherit SPELL;

int timer,flag,stage,toggle,counter;

void create()
{
    ::create();
    set_spell_name("unholy aura");
    set_spell_level(([ "cleric" : 8, "sorcerer" : 8 ]));
    set_spell_sphere("abjuration");
    set_bonus_type(({ "resistance", "deflection" }));
    set_syntax("cast CLASS unholy aura");
    set_damage_desc("divine damage, 4 AC, 4 to all saves");
    set_description("You are surrounded by an aura of evil that will harm all your opponents and will slightly protect you. This is nimbus-family spell that won't work with other nimbuses.");
    set_property("magic",1);
    traveling_aoe_spell(1);
    evil_spell(1);
}

int preSpell()
{
    int align = caster->query_true_align();
    if (caster->query_property("nimbus")) {
        tell_object(caster, "%^RESET%^%^C105%^You are still affected by shield of law or another nimbus spell.%^CRST%^");
        return 0;
    }
    if(caster->query_property("protection from spells"))
    {
        tell_object(caster, "%^RESET%^%^C105%^You are already affected by similar magic.%^CRST%^");
        return 0;
    }
    if (!(align == 3 || align == 6 || align == 9)) {
        tell_object(caster, "%^RESET%^%^C105%^You are of an improper alignment to use this spell!%^CRST%^");
        return 0;
    }
    return 1;
}

void spell_effect(int prof)
{
    int duration;
    duration = (ROUND_LENGTH * 10) * clevel;

    tell_object(caster,"%^RESET%^%^C105%^You feel %^RESET%^%^C240%^f%^C241%^e%^C242%^l%^C243%^l %^RESET%^%^C244%^p%^C243%^o%^C242%^w%^C241%^e%^C240%^r%^C241%^s %^RESET%^%^C105%^warding you from the %^RESET%^%^C220%^g%^C226%^o%^C227%^o%^C220%^d%^RESET%^%^C105%^!%^CRST%^");
    tell_room(place,"%^RESET%^%^C105%^"+caster->QCN+" %^RESET%^%^C105%^is suddenly surrounded by %^RESET%^%^C240%^halo of d%^C241%^a%^C242%^r%^C243%^k%^C244%^n%^C242%^e%^C241%^s%^C240%^s%^RESET%^%^C105%^!%^CRST%^",caster);

    caster->set_property("spelled", ({TO}));
    caster->set_property("nimbus",1);
    caster->set_property("protection from spells", 1);
    caster->set_property("added short",({"%^RESET%^%^C240%^ (in a f%^RESET%^%^C241%^e%^C242%^l%^C243%^l %^RESET%^%^C244%^h%^C245%^a%^C243%^l%^C241%^o%^RESET%^%^C240%^)%^CRST%^"}));
    addSpellToCaster();
    spell_successful();
    caster->add_saving_bonus("all",4);
    caster->add_ac_bonus(4);
    execute_attack();
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect",spell_duration);
    call_out("room_check",ROUND_LENGTH);
}

void room_check()
{
    if(!objectp(caster) || !objectp(ENV(caster)))
    {
        dest_effect();
        return;
    }

    prepend_to_combat_cycle(ENV(caster));

    call_out("room_check",ROUND_LENGTH*2);
    return;
}

void execute_attack(){
    object *attackers;
    int i;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    place      = environment(caster);
    if(!objectp(caster) || !objectp(place))
    {
        dest_effect();
        return;
    }

    attackers = filter_array(caster->query_attackers(),(:objectp($1):));
    attackers = filter_array(attackers,(:$1->is_living():));

    if(sizeof(attackers))
    {
        define_base_damage(0);
        tell_room(place,"%^RESET%^%^C105%^The %^RESET%^%^C240%^u%^C241%^n%^C242%^h%^C243%^o%^C241%^l%^C240%^y %^RESET%^%^C240%^d%^C241%^a%^C242%^r%^C243%^k%^C244%^n%^C242%^e%^C241%^s%^C240%^s a%^RESET%^%^C105%^round "+caster->QCN+" %^RESET%^%^C105%^falls upon "+caster->QP+" %^RESET%^%^C105%^enemies!",({caster,target}));
        tell_object(caster,"%^RESET%^%^C105%^The %^RESET%^%^C240%^u%^C241%^n%^C242%^h%^C243%^o%^C241%^l%^C240%^y %^RESET%^%^C240%^d%^C241%^a%^C242%^r%^C243%^k%^C244%^n%^C242%^e%^C241%^s%^C240%^s %^RESET%^%^C105%^around you falls upon your enemies!%^CRST%^");
        for(i=0;i<sizeof(attackers);i++){
            tell_object(attackers[i],"%^RESET%^%^C105%^You are %^RESET%^%^C052%^s%^C088%^c%^C124%^o%^C196%^r%^C160%^c%^C124%^h%^C088%^e%^C052%^d %^RESET%^%^C105%^by the %^RESET%^%^C240%^u%^C241%^n%^C242%^h%^C243%^o%^C241%^l%^C240%^y %^RESET%^%^C240%^d%^C241%^a%^C242%^r%^C243%^k%^C244%^n%^C242%^e%^C241%^s%^C240%^s %^RESET%^%^C105%^as you strike "
                        ""+caster->QCN+"%^RESET%^%^C105%^!%^CRST%^");
            damage_targ(attackers[i],attackers[i]->return_target_limb(),sdamage,"divine");
        }
    }
    prepend_to_combat_cycle(place);
}

void dest_effect()
{
    remove_call_out("room_check");
    if(objectp(caster))
    {
        tell_object(caster,"%^RESET%^%^C105%^The %^RESET%^%^C240%^halo %^RESET%^%^C105%^around you fades.%^CRST%^");
        caster->remove_property("nimbus");
        caster->remove_property("protection from spells");
        caster->add_ac_bonus(-4);
        caster->add_saving_bonus("all",-4);
	    caster->remove_property_value("added short",({"%^RESET%^%^C240%^ (in a f%^RESET%^%^C241%^e%^C242%^l%^C243%^l %^RESET%^%^C244%^h%^C245%^a%^C243%^l%^C241%^o%^RESET%^%^C240%^)%^CRST%^"}));
    }
    ::dest_effect();
    if(objectp(TO)) { TO->remove(); }
}
