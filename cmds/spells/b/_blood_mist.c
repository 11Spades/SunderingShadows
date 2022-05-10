// Chernobog (5/8/22)
// Blood Mist

#include <spell.h>
#include <magic.h>

inherit SPELL;

object* saves;
int time, first_execute;

void create(){
    ::create();
    set_spell_name("blood mist");
    set_spell_level(([ "oracle" : 8 ]));
    set_mystery("lunar");
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS blood mist");
    set_damage_desc("concealment and AOE confusion");
    set_description("This spell summons forth a thick ruddy mist in the area. Any creatures within the mist are coated by the heavy crimson droplets, granting a measure of concealment as well as confusing anyone that fails a will save.");
    set_verbal_comp();
    set_somatic_comp();
    aoe_spell(1);
    mental_spell();
    set_save("will");
    set_aoe_message("%^RESET%^%^CRST%^%^C196%^(%^C126%^obscured by a %^C196%^h%^C124%^a%^C196%^z%^C124%^y %^RESET%^%^C196%^m%^C124%^i%^C196%^s%^C124%^t%^C196%^)%^CRST%^");
}

void spell_effect(int prof){
    tell_object(caster,"%^RESET%^%^CRST%^%^C126%^You take in a %^C243%^d%^C245%^e%^C247%^e%^C249%^p %^C251%^br%^C249%^e%^C247%^a%^C245%^t%^C243%^h%^RESET%^%^C126%^... and then exhale a flowing %^RESET%^%^C196%^cr%^C124%^i%^C196%^m%^C124%^so%^C196%^n m%^C124%^i%^C196%^s%^C124%^t %^RESET%^%^C126%^that quickly fills the area.%^CRST%^");
    tell_room(place,"%^RESET%^%^CRST%^%^C126%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C126%^ takes in a %^C243%^d%^C245%^e%^C247%^e%^C249%^p %^C251%^br%^C249%^e%^C247%^a%^C245%^t%^C243%^h%^RESET%^%^C126%^... and then exhales a flowing %^RESET%^%^C196%^cr%^C124%^i%^C196%^m%^C124%^so%^C196%^n m%^C124%^i%^C196%^s%^C124%^t %^RESET%^%^C126%^that quickly fills the area.%^CRST%^", caster);
    place->set_property("spelled", ({this_object()}) );
    caster->set_property("spelled", ({this_object()}) );
    time = 0;
    addSpellToCaster();
    spell_successful();
    execute_attack();
}

void execute_attack(int prof){
    object* foes;

    if(!objectp(place)){
        dest_effect();
        return;
    }
    if(!objectp(caster)){
        dest_effect();
        return;
    }

    if(!place->query_property("concealment")) place->set_property("concealment", 20);

    foes = target_selector();
    foes = distinct_array( foes );
    foes -= ({ caster });
    foes -= saves;

    if(time > clevel){
        dest_effect();
        return;
    }
    if(!present(caster, place)){
        dest_effect();
        return;
    }

    tell_room(place,"%^RESET%^%^CRST%^%^C126%^Clouds of %^C196%^m%^C124%^i%^C196%^s%^C124%^t %^RESET%^%^C126%^drift about the area, the %^C196%^cr%^C124%^i%^C196%^m%^C124%^so%^C196%^n dr%^C124%^o%^C196%^pl%^C124%^et%^C196%^s %^RESET%^%^C126%^coating everything in a %^C124%^ruddy haze%^C126%^.%^CRST%^");
    
    foreach(object ob in foes)
    {
        if(!do_save(ob, clevel)){
            "/std/effect/status/confused"->apply_effect(ob, clevel/5 + 1, caster);
            tell_object(ob, "%^RESET%^%^CRST%^%^C124%^The bloody mist awakens something within you, %^C202%^wa%^C208%^r%^C202%^pi%^C208%^n%^C202%^g %^C124%^your perceptions!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C124%^"+ob->query_cap_name()+"%^RESET%^%^CRST%^%^C124%^ seems to get a %^C202%^cr%^C208%^a%^C202%^ze%^C208%^d %^C124%^look in their eyes.%^CRST%^", ob);
        }
        else tell_object(ob, "%^RESET%^%^CRST%^%^C125%^You manage to resist the lure of the mist.%^CRST%^");
        saves += ({ ob });
    }
    
    time++;

    if(present(caster, place) && !caster->query_unconscious()){
        place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
    else{
        dest_effect();
        return;
    }
}

void dest_effect(){
    if(objectp(place)){
        tell_object(place, "\n%^RESET%^%^CRST%^%^C126%^The %^C196%^cr%^C124%^i%^C196%^m%^C124%^so%^C196%^n m%^C124%^i%^C196%^st %^C126%^fades and %^RESET%^%^C059%^di%^C243%^sp%^C244%^er%^C245%^se%^C246%^s...%^CRST%^");
        place->remove_property_value("spelled", ({TO}) );
        place->remove_property("concealment");
    }
    if(objectp(caster)){
        caster->remove_property_value("spelled", ({TO}) );
    }
    
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

