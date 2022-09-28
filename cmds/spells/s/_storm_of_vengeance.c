//Ice Storm coded by Bane//
//Adding to clerics because it is also a cleric spell in the
//PHB after discussions with other Imms ~Circe~ 5/18/13
//After discussing with Circe, removing it from Clerics for the time being until they we are finished rebalancing
#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int timer,mystage,flag;

void create() {
    ::create();
    set_spell_name("storm of vengeance");
    set_spell_level(([ "druid" : 9, "cleric" :9, "oracle" : 9 ]));
    set_mystery("wind");
    set_mystery("battle");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS storm of vengeance");
    set_description("When this spell is cast, a dark storm cloud will cover the current area. Lightning will begin to strike enemies of the caster and they will be shaken by thunder. Soon after, the cloud will open up in a torrent of acid rain and hail, making it difficult to maintain footing and to see.");
    set_verbal_comp();
    set_somatic_comp();
    set_save("varied");
    mystage = 1;
    aoe_spell(1);
    set_aoe_message("%^RESET%^%^CRST%^%^C202%^(%^C059%^shaken by a %^C243%^vengeful %^C226%^s%^C230%^t%^C226%^or%^C230%^m%^C202%^)%^CRST%^");
}

string query_cast_string() {
    tell_object(caster, "%^RESET%^%^CRST%^%^C034%^You shout into the %^C243%^h%^C059%^eav%^C243%^e%^C059%^n%^C243%^s%^RESET%^%^C034%^, calling forth the vengeance of the %^C046%^wilds!%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C034%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C034%^ shouts into the %^C243%^h%^C059%^eav%^C243%^e%^C059%^n%^C243%^s%^RESET%^%^C034%^, calling forth the vengeance of the %^C046%^wilds!%^CRST%^", caster);
    return "display";
}

void spell_effect(int prof) {
    tell_room(place,"%^RESET%^%^CRST%^%^C028%^An %^C243%^o%^C059%^min%^C243%^o%^C059%^u%^C243%^s b%^C059%^lac%^C243%^k c%^C059%^l%^C243%^o%^C059%^u%^C243%^d %^C028%^roils into the area with %^C036%^unnatural %^C028%^purpose!%^CRST%^");

    spell_successful();
    addSpellToCaster();
}

void execute_attack() {
    object *foes=({}),*targs=({}),*tmp,targ;
    int i, strikes,hail,acid,lightning;
    string limb;

    ::execute_attack();
    if(!objectp(caster)) {
        dest_effect();
        return;
    }
    if(!objectp(place)){
        dest_effect();
        return;
    }
    if(!present(caster,place)) {
        dest_effect();
        return;
    }
    if((time() > timer) && mystage > 1) {
        dest_effect();
        return;
    }

    switch(mystage) {
    case 1:
        tell_room(place, "%^RESET%^%^CRST%^%^C020%^A deafening %^C059%^BOOM %^C020%^of %^C243%^th%^C245%^un%^C243%^d%^C245%^e%^C243%^r %^RESET%^%^C020%^coincides instantly with a bright %^C226%^fl%^C230%^as%^C226%^h %^C020%^of %^C230%^l%^C226%^ig%^C230%^ht%^C226%^ni%^C230%^n%^C226%^g%^C255%^!%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C020%^A %^C059%^terrible %^C243%^st%^C245%^or%^C243%^m %^RESET%^%^C020%^begins to drench the area, %^C226%^fla%^C230%^she%^C226%^s %^C020%^of %^C230%^l%^C226%^ig%^C230%^ht%^C226%^ni%^C230%^n%^C226%^g %^RESET%^%^C020%^illuminating the area as fist-sized %^C253%^h%^C255%^a%^C087%^i%^C253%^l %^C255%^s%^C087%^t%^C255%^o%^C253%^n%^C255%^e%^C087%^s %^RESET%^%^C020%^smash violently all around!%^CRST%^");
        place->addObjectToCombatCycle(TO,1);
        mystage++;
        timer = time() + 30 + (ROUND_LENGTH * clevel * 2);
        return;

    default:
        tell_room(place, "%^RESET%^%^CRST%^%^C020%^%^The terrible storm continues to rage, %^C226%^fla%^C230%^she%^C226%^s %^C020%^of %^C230%^l%^C226%^ig%^C230%^ht%^C226%^ni%^C230%^n%^C226%^g %^RESET%^%^C020%^illuminating the area as fist-sized %^C253%^h%^C255%^a%^C087%^i%^C253%^l %^C255%^s%^C087%^t%^C255%^o%^C253%^n%^C255%^e%^C087%^s %^RESET%^%^C020%^smash violently down and %^C036%^hi%^C030%^s%^C036%^si%^C042%^n%^C036%^g r%^C030%^a%^C036%^in %^RESET%^%^C020%^burns everything it touches!%^CRST%^");
        break;
    } // falls through when mystage is above 1


    foes = target_selector();
    foes -= ({ caster });
    define_base_damage(0);
    hail = sdamage/2;
    acid = sdamage;
    lightning = sdamage;

    for(i=0;i<sizeof(foes);i++) {
        if(!objectp(targ = foes[i])) continue;

        limb = targ->return_target_limb();

        switch(random(3)) {
            case 0: // hail time
                set_save("reflex");

                if(!do_save(targ)) {
                    tell_object(targ, "%^RESET%^%^CRST%^%^C253%^H%^C255%^a%^C087%^i%^C253%^l %^C255%^s%^C087%^t%^C255%^o%^C253%^n%^C255%^e%^C087%^s %^RESET%^%^C020%^smash into your head and shoulders!%^CRST%^");
                    damage_targ(targ,limb,hail,"cold");
                    damage_targ(targ,limb,hail,"bludgeoning");
                }
                else {
                    if(!evade_splash(foes[i])) {
                        tell_object(targ, "%^RESET%^%^CRST%^%^C020%^You move aside at the last instant, avoiding most of the damage from the hailstones!%^CRST%^");
                        damage_targ(targ,limb,hail/2,"cold");
                        damage_targ(targ,limb,hail/2,"bludgeoning");
                    }
                }
                break;
            case 1: // acid
                set_save("reflex");

                if(!do_save(targ)) {
                    tell_object(targ, "%^RESET%^%^CRST%^%^C020%^You feel the burn as the %^C036%^ra%^C042%^i%^C036%^n %^C020%^strikes your skin. It's %^C036%^ac%^C030%^i%^C036%^d%^C020%^!%^CRST%^");
                    damage_targ(targ,limb,acid,"acid");
                }
                else {
                    if(!evade_splash(foes[i])) {
                    tell_object(targ, "%^RESET%^%^CRST%^%^C020%^You move aside at the last instant, avoiding the rain, though a few droplets still sear your skin!%^CRST%^");
                    damage_targ(targ,limb,acid/2,"acid");
                    }
                }
                break;
            case 2: // thunder
                set_save("reflex");

                if(!do_save(targ)) {
                    tell_object(targ, "%^RESET%^%^CRST%^%^C020%^You are electrified by a %^C226%^bo%^C230%^l%^C226%^t of %^C230%^l%^C226%^ig%^C230%^ht%^C226%^ni%^C230%^n%^C226%^g %^RESET%^%^C020%^from the storm cloud!%^CRST%^");
                    damage_targ(targ,limb,lightning,"electricity");
                }
                else {
                    if(!evade_splash(foes[i])) {
                        tell_object(targ, "%^RESET%^%^CRST%^%^C020%^You dodge aside at the last second, avoiding the brunt of the damage from the lightning strike!%^CRST%^");
                        damage_targ(targ,limb,lightning/2,"electricity");
                    }
                }

                set_save("fort");

                if(!do_save(targ)) {
                    tell_object(targ,"%^RESET%^%^CRST%^%^C020%^The %^C059%^t%^C243%^hun%^C059%^d%^C243%^e%^C059%^r %^C020%^crashes right against you, deafening you!%^CRST%^");
                    targ->set_paralyzed(roll_dice(2,6), "%^RESET%^%^CRST%^%^C059%^Your ears are bleeding!%^CRST%^");
                }
                break;
        }
    }
    place->addObjectToCombatCycle(TO,1);
}


void dest_effect() {

    if(objectp(place)) tell_room(place,"%^RESET%^%^CRST%^%^C032%^The %^C059%^ominous %^C243%^black %^C059%^st%^C243%^or%^C059%^mclo%^C243%^u%^C059%^ds %^RESET%^%^C032%^suddenly billow away, disappearing as quickly as they arrived!%^CRST%^");

    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

