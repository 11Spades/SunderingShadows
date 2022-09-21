// Chernobog (9/21/22)
// Thief of Five Fates

#include <spell.h>
#include <magic.h>

inherit SPELL;

int counter;

void create(){
    ::create();
    set_spell_name("thief of five fates");
    set_spell_level(([ "warlock" : 4 ]));
    set_heritage("astral");
    set_spell_sphere("enchantment_charm");
    set_syntax("cast CLASS thief of five fates on TARGET");
    set_damage_desc("target is at disadvantage on saves and attacks");
    set_description("The warlock's patron has revealed to the them those stars that guide the fates, and with the proper pull... those fates can be unwound. For a brief period, the warlock can twist the fortunes of their victim, causing swings of a weapon to miss, footsteps to falter into traps, or a weakening of resolve when needed most.");
    set_target_required(1);
    set_save("will");
}

string query_cast_string(){
    tell_object(caster, "%^RESET%^%^CRST%^%^C101%^You reach out towards "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^, contorting your fingers in %^RESET%^%^C143%^s%^C149%^t%^C155%^ran%^C149%^g%^C143%^e p%^C149%^a%^C155%^tter%^C149%^n%^C143%^s%^C100%^.%^CRST%^");
    return "%^RESET%^%^CRST%^%^C101%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^ reaches out towards "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^, contorting his fingers in %^RESET%^%^C143%^s%^C149%^t%^C155%^ran%^C149%^g%^C143%^e p%^C149%^a%^C155%^tter%^C149%^n%^C143%^s%^C100%^.%^CRST%^";
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
    
    if(!objectp(target)){
        tell_object(caster, "%^RESET%^%^CRST%^%^C059%^Your target is no longer here.%^CRST%^");
        return;
    }
    if(target->query_property("roll disadvantage")){
        tell_object(caster, "%^RESET%^%^CRST%^%^C101%^The fate of your victim has already been %^C143%^t%^C149%^a%^C155%^int%^C149%^e%^C143%^d%^C101%^!%^CRST%^");
        dest_effect();
        return;
    }
    
    caster_name = caster->query_cap_name();
    target_name = target->query_cap_name();
    
    if(do_save(target, 0)){
        tell_object(caster, "%^RESET%^%^CRST%^%^C101%^A %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^beings to surround "+target_name+"%^RESET%^%^CRST%^%^C101%^, but %^C136%^falters %^C101%^and %^C253%^di%^C144%^sp%^C101%^er%^C100%^se%^C058%^s %^RESET%^%^C101%^as they resist your machinations.%^CRST%^");
        tell_object(target, "%^RESET%^%^CRST%^%^C101%^A %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^begins to surround you, but %^C136%^falters %^C101%^and %^C253%^di%^C144%^sp%^C101%^er%^C100%^se%^C058%^s%^RESET%^%^C101%^.%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C101%^A %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^begins to surround "+target_name+"%^RESET%^%^CRST%^%^C101%^, but %^C136%^falters %^C101%^and %^C253%^di%^C144%^sp%^C101%^er%^C100%^se%^C058%^s%^RESET%^%^C101%^.%^CRST%^", ({caster, target}));
        return;
    }

    tell_object(target, "%^RESET%^%^CRST%^%^C101%^A %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^descends upon you, radiating a suspenseful sense of %^C059%^d%^C243%^r%^C059%^e%^C243%^a%^C059%^d%^RESET%^%^C101%^.%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C101%^A %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^descends upon "+target_name+"%^RESET%^%^CRST%^%^C101%^, radiating a suspenseful sense of %^C059%^d%^C243%^r%^C059%^e%^C243%^a%^C059%^d%^RESET%^%^C101%^.%^CRST%^", target);
    
    spell_successful();
    target->set_property("roll disadvantage", 1);
    counter = 5;
    
    call_out("round_checkup", 6);
    return;
}

void round_checkup(){
    if(!objectp(target)){
        dest_effect();
        return;
    }
    if(do_save(target, 0)){
        dest_effect();
        return;
    }
    
    place = environment(target);
    tell_object(target, "%^RESET%^%^CRST%^%^C101%^The %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^continues to plague you...%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C101%^The %^C143%^f%^C149%^e%^C155%^ll au%^C149%^r%^C143%^a %^RESET%^%^C101%^continues to plague "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^...%^CRST%^", target);
    
    counter--;
    if(counter < 0) dest_effect();
    else call_out("round_checkup", 6);
    return;
}

void dest_effect(){
    if(target && target->query_property("roll disadvantage")){
        place = environment(target);
        tell_object(target, "%^RESET%^%^CRST%^%^C101%^The %^C149%^a%^C155%^u%^C149%^r%^C143%^a %^RESET%^%^C253%^di%^C144%^sp%^C101%^er%^C100%^se%^C058%^s %^RESET%^%^C101%^and the oppressive weight lifts!%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C101%^The %^C149%^a%^C155%^u%^C149%^r%^C143%^a %^RESET%^%^C101%^around "+target->query_cap_name()+" %^C253%^di%^C144%^sp%^C101%^er%^C100%^se%^C058%^s!%^CRST%^", target);
        target->remove_property("roll disadvantage");
    }
    
    ::dest_effect();
    if(objectp(this_object())) this_object()->remove();
}

