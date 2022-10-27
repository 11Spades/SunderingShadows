// Chernobog (10/27/22)
// Drunken Stupor

#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int counter;

void create(){
    ::create();
    set_spell_name("drunken stupor");
    set_spell_level(([ "cleric" : 6 ]));
    set_domains( "hedonism" );
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS drunken stupor on TARGET");
    set_damage_desc("target is at disadvantage on saves and attacks for 2 rounds");
    set_description("Your victim will suddenly feel extremely inebriated, stumbling about drunk and seeing double. Failing their save will put them at disadvantage for a couple rounds before the charm wears off.");
    set_target_required(1);
    set_save("fort");
}

string query_cast_string(){
    tell_object(caster, "%^RESET%^%^CRST%^%^C100%^You whisper a sibilant prayer, %^C058%^slurring %^C100%^your words...%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C100%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C100%^ whispers a sibilant prayer, %^C058%^slurring %^C100%^their words...%^CRST%^", caster);
    return "display";
}

int preSpell(){
    if(!caster->ok_to_kill(target)){
        tell_object(caster, "%^YELLOW%^There is a %^MAGENTA%^NoPK flag %^YELLOW%^preventing this action.%^RESET%^");
        dest_effect();
        return 0;
    }
    return 1;
}

void spell_effect(int prof){
    string caster_name, target_name;
    int duration = ROUND_LENGTH * 2;
    
    if(!objectp(target)){
        tell_object(caster, "%^RESET%^%^CRST%^%^C059%^Your target is no longer here.%^CRST%^");
        dest_effect();
        return;
    }
    if(target->query_property("roll disadvantage")){
        tell_object(caster, "%^RESET%^%^CRST%^%^C100%^Your victim is already suffering!%^CRST%^");
        dest_effect();
        return;
    }
    
    caster_name = caster->query_cap_name();
    target_name = target->query_cap_name();
    
    if(do_save(target, 0) || PLAYER_D->immunity_check(target, "charm")){
        tell_object(target, "%^RESET%^%^CRST%^%^C101%^Your balance suddenly swings off and you have trouble focusing... but you struggle through and quickly recover.%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C101%^"+target_name+"%^RESET%^%^CRST%^%^C101%^ stumbles about for a moment, but struggles through and quickly recovers.%^CRST%^", target);
        dest_effect();
        return;
    }

    tell_object(target, "%^RESET%^%^CRST%^%^C058%^You suddenly feel very %^C214%^-%^C220%^d%^C226%^run%^C220%^k%^C214%^-%^RESET%^%^C058%^... The room starts %^C100%^s%^C101%^p%^C144%^i%^C100%^n%^C101%^n%^C144%^i%^C100%^n%^C101%^g %^RESET%^%^C058%^and you have trouble keeping your balance!%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C058%^"+target_name+"%^RESET%^%^CRST%^%^C058%^ starts to %^C100%^s%^C101%^t%^C144%^u%^C100%^m%^C101%^b%^C144%^l%^C100%^e %^RESET%^%^C058%^about, clearly off-balance.%^CRST%^", target);
    
    target->set_property("roll disadvantage", 1);
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect", spell_duration);
    spell_successful();
    return;
}

void dest_effect(){
    if(target && target->query_property("roll disadvantage")){
        place = environment(target);
        tell_object(target, "%^RESET%^%^CRST%^%^C144%^The room stops spinning and you get your balance back!%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C144%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C144%^ seems to regain their balance!%^CRST%^", target);
        target->remove_property("roll disadvantage");
    }
    
    ::dest_effect();
    if(objectp(this_object())) this_object()->remove();
}

