#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int timer,flag,stage,toggle,counter;


void create()
{
    ::create();
    set_spell_name("caustic mire");
    set_spell_level(([ "warlock" : 2 ]));
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS caustic mire");
    set_damage_desc("AOE acid damage and tripped");
    set_description("This invocations causes the ground in the area to turn into a muddy, acidic mire that will cause all caught within it to lose their footing. The caustic fumes cause victims to suffer from acid damage throughout the duration.");
    set_verbal_comp();
    set_somatic_comp();
    set_save("reflex");
    set_immunities( ({"acid"}) );
    aoe_spell(1);
    set_aoe_message("%^RESET%^%^CRST%^%^C118%^(%^C065%^covered in %^C142%^a%^C136%^ci%^C130%^d%^C142%^i%^C136%^c m%^C130%^u%^C142%^d%^C118%^)%^CRST%^");
    set_feats_required(([ "warlock" : "tome of ancient secrets"]));
}

string query_cast_string()
{
    return "%^RESET%^%^CRST%^%^C065%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C065%^ places "+caster->query_possessive()+" hands together, gathering %^C118%^e%^C112%^ld%^C106%^r%^C118%^i%^C112%^tc%^C106%^h %^C118%^e%^C112%^ne%^C106%^r%^C118%^g%^C112%^y%^RESET%^%^C065%^.%^CRST%^";
}

void spell_effect(int prof)
{
    tell_object(caster, "%^RESET%^%^CRST%^%^C065%^You raise your hands to the air and the %^C118%^d%^C112%^ar%^C106%^k %^C118%^e%^C112%^ne%^C106%^r%^C118%^g%^C112%^y %^RESET%^%^C065%^spreads throughout the area, forming into a %^C142%^s%^C136%^ti%^C130%^c%^C142%^k%^C136%^y, %^C142%^a%^C136%^ci%^C130%^d%^C142%^i%^C136%^c m%^C130%^u%^C142%^d%^RESET%^%^C065%^!%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C065%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C065%^ raises "+caster->query_possessive()+" hands to the air and the %^C118%^d%^C112%^ar%^C106%^k %^C118%^e%^C112%^ne%^C106%^r%^C118%^g%^C112%^y %^RESET%^%^C065%^spreads throughout the area, forming into a %^C142%^s%^C136%^ti%^C130%^c%^C142%^k%^C136%^y, %^C142%^a%^C136%^ci%^C130%^d%^C142%^i%^C136%^c m%^C130%^u%^C142%^d%^RESET%^%^C065%^!%^CRST%^",caster);
    counter = clevel/8 + 2;
    addSpellToCaster();
    spell_successful();
    execute_attack();
}


void execute_attack()
{
    object *foes=({}),targ;
    int i;
    string limb;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    if(!objectp(caster) || !objectp(place) || !present(caster,place)|| counter<0)
    {
        dest_effect();
        return;
    }

    message("info", "%^RESET%^%^CRST%^%^C065%^The mud %^C142%^s%^C136%^ee%^C130%^t%^C142%^h%^C136%^es %^RESET%^%^C065%^and %^C142%^h%^C136%^is%^C130%^s%^C142%^e%^C136%^s %^RESET%^%^C065%^as it almost seems to grope at the living!%^CRST%^", nearbyRoom(place,2));

    foes = target_selector();
    foes -= ({ caster });

    for(i=0;i<sizeof(foes);i++) {
        if(!objectp(targ = foes[i])) continue;

        limb = targ->return_target_limb();
        if(do_save(targ,0)) {
          tell_object(targ,"%^RESET%^%^CRST%^%^C065%^You avoid the worst of the mire, but the %^C142%^a%^C136%^ci%^C130%^d%^C142%^i%^C136%^c f%^C130%^u%^C142%^m%^C136%^es %^RESET%^%^C065%^still cause %^C124%^scalding burns%^C065%^!%^CRST%^");
          tell_room(place,"%^RESET%^%^CRST%^%^C065%^"+targ->query_cap_name()+"%^RESET%^%^CRST%^%^C065%^ manages to hold strong in the mud!%^CRST%^",({targ}));
          damage_targ(targ,limb,sdamage/2,"acid");
        }
        else {
          tell_object(targ,"%^RESET%^%^CRST%^%^C065%^Unable to keep your footing, you %^C064%^slip %^C065%^in the %^C142%^m%^C136%^u%^C130%^d%^C065%^!%^CRST%^");
          tell_room(place,"%^RESET%^%^CRST%^%^C065%^Unable to keep balance, "+targ->query_cap_name()+"%^RESET%^%^CRST%^%^C065%^ %^C064%^slips %^C065%^in the %^C142%^m%^C136%^u%^C130%^d%^C065%^!%^CRST%^",({targ}));
          targ->set_temporary_blinded(1);
          targ->set_tripped(1,"%^RESET%^%^CRST%^%^C065%^You are struggling to regain your footing!%^CRST%^",4);
          damage_targ(targ,limb,sdamage,"acid");
        }
    }

    counter--;
    place->addObjectToCombatCycle(TO,1);
}


void dest_effect() {
    if(objectp(place)) tell_object(place,"%^RESET%^%^CRST%^%^C065%^The caustic mire %^C066%^dries up %^C065%^and the acidic fumes %^C100%^dis%^C101%^sip%^C144%^ate%^C065%^.%^CRST%^");
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
