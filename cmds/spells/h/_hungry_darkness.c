#include <spell.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

int time, flag;

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("hungry darkness");
    set_spell_level(([ "warlock" : 4 ]));
    set_heritage("gloom");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS hungry darkness");
    set_description("This invocation calls a supernatural darkness down within the area, blurring the line between the "
"prime material plane and the planes beyond. What lies beyond will ignore the warlock, but will reach out, biting and "
"clawing at anything close enough...Enemies that fail a save will suffer bleeding wounds.");
    set_verbal_comp();
    set_somatic_comp();
    set_save("reflex");
    aoe_spell(1);
    set_aoe_message("%^RESET%^%^CRST%^%^C059%^(%^C019%^blanketed in %^C026%^r%^C027%^o%^C032%^i%^C027%^l%^C032%^i%^C027%^n%^C026%^g %^C246%^s%^C243%^h%^C059%^ado%^C243%^w%^C246%^s%^RESET%^%^C059%^)%^CRST%^");
}

void spell_effect(int prof) {
    tell_object(caster, "%^RESET%^%^CRST%^%^C019%^You lift your arms, and a sudden %^C246%^d%^C243%^a%^C059%^rkne%^C243%^s%^C246%^s %^RESET%^%^C019%^descends upon the area!%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C019%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C019%^ lifts "+caster->query_possessive()+" arms, and a sudden %^C246%^d%^C243%^a%^C059%^rkne%^C243%^s%^C246%^s %^RESET%^%^C019%^descends upon the area!%^CRST%^", caster);
    time = 0;
    addSpellToCaster();
    spell_successful();
    execute_attack();
}

void execute_attack() {
    int damage, event, i;
    object *foes;
    string target_limb;

    if (!flag) {
        flag = 1;
        ::execute_attack();
        return;
    }
    if(!objectp(caster)) {
        dest_effect();
        return;
    }
    foes = target_selector();


    if (time>clevel * 2) {
        dest_effect();
    }
    else {
        //define_base_damage(0);//lazy re-roll.
        damage = sdamage;
        tell_room(place,"%^RESET%^%^CRST%^%^C019%^The %^C246%^d%^C243%^a%^C059%^rkne%^C243%^s%^C246%^s %^RESET%^%^C019%^moves around you like a living thing, %^C026%^w%^C027%^r%^C032%^i%^C027%^t%^C032%^h%^C027%^in%^C026%^g %^C019%^and %^C026%^m%^C027%^u%^C032%^t%^C027%^t%^C032%^e%^C027%^r%^C032%^i%^C027%^n%^C026%^g%^RESET%^%^C019%^.%^RESET%^");
        event = roll_dice(1,3);

        for (i=0;i<sizeof(foes);i++) {
            if (!objectp(foes[i])) continue;
            if (!objectp(caster)) {
                dest_effect();
                return;
            }
            if (foes[i] == caster && caster != target) continue;
            if (interactive(foes[i]) && newbiep(foes[i])) continue;
            if(foes[i]->query_property("no detect")) continue;
//added by Circe to stop scry detectors, etc, from being hit.
            if (!present(caster,place) && caster != target) {
                dest_effect();
                return;
            }
            if(!present(foes[i],place)) continue;

            target_limb = foes[i]->return_target_limb();
            if(do_save(foes[i],0)) {
                switch(event) {
                case 1:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^The %^C246%^s%^C243%^h%^C059%^ado%^C243%^w%^C246%^s %^RESET%^%^C019%^deepen around you, and you pull away as %^C255%^te%^C252%^e%^C255%^t%^C252%^h %^RESET%^%^C019%^graze your skin!%^RESET%^");
                    damage_targ(foes[i], target_limb, damage/2,"piercing");
                    break;
                case 2:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^Motion catches the edge of your vision, and you pull away as something %^C026%^c%^C027%^l%^C032%^a%^C027%^w%^C026%^s %^RESET%^%^C019%^at you from the %^C246%^s%^C243%^h%^C059%^ado%^C243%^w%^C246%^s%^C019%^!%^CRST%^");
                    damage_targ(foes[i], target_limb, damage/2,"slashing");
                    break;
                default:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^A terrible %^C218%^s%^C212%^h%^C206%^r%^C218%^i%^C212%^e%^C206%^k %^RESET%^%^C019%^bursts forth from the %^C246%^s%^C243%^h%^C059%^ado%^C243%^w%^C246%^s%^C019%^, and you quickly cover your ears to fend off the worst of it!%^CRST%^");
                    damage_targ(foes[i], target_limb, damage/2,"sonic");
                    break;
                }
            }
            else {
                switch(event) {
                case 1:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^As the shadows deepen around you, you feel %^C255%^te%^C252%^e%^C255%^t%^C252%^h %^RESET%^%^C019%^sink into your skin!%^CRST%^");
                    damage_targ(foes[i], target_limb, damage,"piercing");
                    break;
                case 2:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^Something claws at you from the shadows, drawing %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C196%^!%^CRST%^");
                    damage_targ(foes[i], target_limb, damage,"slashing");
                    break;
                default:
                    tell_object(foes[i], "%^RESET%^%^CRST%^%^C019%^A terrible %^C218%^s%^C212%^h%^C206%^r%^C218%^i%^C212%^e%^C206%^k %^RESET%^%^C019%^bursts forth from the shadows, an unnatural sound that pierces your skull like a %^C244%^k%^C247%^n%^C250%^i%^C247%^f%^C244%^e%^C019%^!%^CRST%^");
                    damage_targ(foes[i], target_limb, damage,"sonic");
                    break;
                }
                
                foes[i]->set_property("rend", 2);
            }
        }
        time++;;
        if (present(caster,place) && !caster->query_unconscious()) {
            place->addObjectToCombatCycle(this_object(),1);
        }
        else {
            dest_effect();
        }
    }
}

void dest_effect() {
    if(objectp(place)) tell_room(place, "%^RESET%^%^CRST%^%^C019%^The %^C246%^d%^C243%^a%^C059%^rkne%^C243%^s%^C246%^s %^C019%^di%^C020%^ss%^C021%^ip%^C026%^at%^C027%^es %^RESET%^%^C019%^into nothing but %^C026%^a%^C027%^i%^C032%^r%^C019%^.%^CRST%^");
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

