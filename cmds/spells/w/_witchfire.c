// witchfire
#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit SPELL;

int bonus;

void create() {
    ::create();
    set_spell_name("witchfire");
    set_spell_level(([ "warlock":1 ]));
    set_heritage("fey");
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS witchfire on TARGET");
    set_description("When cast, ghastly tendrils of mist will reach for the target, enshrouding them in an ominous glow. The uncanny illumination will make them more susceptible to melee hits, and make it impossible for them to hide by magical or other means until the spell is dispelled or expires.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_heart_beat(1);
}

void heart_beat()
{
    if(!objectp(target)) { dest_effect(); return; }
    if(!objectp(caster)) { return; }
    if(target->query_invis()) {
        if((string)TO->query_spell_type() == "potion") tell_object(target,"%^RESET%^%^CRST%^%^C024%^The %^C031%^strange mist%^C024%^ encapsulating you makes it impossible to hide.%^CRST%^");
        else tell_object(target,"%^RESET%^%^CRST%^%^C024%^The %^C031%^strange mist%^C024%^ encapsulating you makes it impossible to hide.%^CRST%^");
        target->set_invis(0);
        return;
    }
    return;
}

string query_cast_string()
{
    tell_object(caster,"%^CRST%^%^RESET%^%^C061%^You shatter a %^C059%^black seed%^C061%^ between your palms, releasing a %^C059%^n%^C060%^a%^C066%^c%^C065%^r%^C059%^e%^C060%^o%^C066%^u%^C065%^s %^C059%^c%^C060%^l%^C066%^o%^C065%^u%^C059%^d%^RESET%^%^C061%^ of %^C059%^dark spores%^C061%^.%^CRST%^");
    tell_room(place,"%^CRST%^%^RESET%^%^C061%^"+caster-query_cap_name()+" shatters a %^C059%^black seed%^C061%^ between "+caster->query_possessive()+" palms, releasing a %^C059%^n%^C060%^a%^C066%^c%^C065%^r%^C059%^e%^C060%^o%^C066%^u%^C065%^s %^C059%^c%^C060%^l%^C066%^o%^C065%^u%^C059%^d%^RESET%^%^C061%^ of %^C059%^dark spores%^C061%^.%^CRST%^",caster);
    return "display";
}

void spell_effect(int prof) {
    int duration;
// SC/MC separation removed; no point on 3e system as it will simply scale with class levels.
    duration = (ROUND_LENGTH * 3/2) * clevel;
    bonus = clevel/10;

    if(!present(target,place)) {
        tell_object(caster,"%^CRST%^%^RESET%^%^C067%^Your target has left the area.%^CRST%^");
        if(objectp(TO)) TO->remove();
        return;
    }
    if((string)TO->query_spell_type() == "potion") {
      if((int)target->query_property("faerie fire")) {
        tell_object(caster,"An ominous mist shrouds you in an eerie glow.");
        if(objectp(TO)) TO->remove();
        return;
      }
      tell_object(target,"Your strange cloud of illumination flickers and flares.");
      tell_room(place,""+target->QCN+"'s strange illumination flickers and flares.",target);
    }
    else {
      tell_object(caster,"%^CRST%^%^RESET%^%^C066%^As you part your hands, the %^C059%^spores%^C066%^ weave toward "+target->query_cap_name()+" in ominous %^C073%^tendrils%^RESET%^%^C066%^ of %^C073%^mist%^C066%^, illuminating "+target->query_subjective()+" in an %^C061%^eerie %^C060%^gl%^C061%^o%^RESET%^%^C060%^w%^C066%^.%^CRST%^");
      tell_object(target,"%^CRST%^%^RESET%^%^C066%^As "+caster->query_cap_name()+" parts "+caster->query_possessive()+" hands, the %^C059%^spores%^C066%^ weave toward you in ominous %^C073%^tendrils%^RESET%^%^C066%^ of %^C073%^mist%^C066%^, illuminating you in an %^C061%^eerie %^C060%^gl%^C061%^o%^RESET%^%^C060%^w%^C066%^.%^CRST%^");
      tell_room(place,"%^CRST%^%^RESET%^%^C066%^As "+caster->query_cap_name()+" parts "+caster->query_possessive()+" hands, the %^C059%^spores%^C066%^ weave toward toward "+target->query_cap_name()+" in ominous %^C073%^tendrils%^RESET%^%^C066%^ of %^C073%^mist%^C066%^, illuminating "+target->query_subjective()+" in an %^C061%^eerie %^C060%^gl%^C061%^o%^RESET%^%^C060%^w%^C066%^.%^CRST%^",({target,caster}));
    }
    spell_successful();
    target->add_ac_bonus(-1*bonus);
    target->set_property("faerie fire",1);
    target->set_property("spelled",({TO}));
    target->set_property("added short",({"%^RESET%^%^CRST%^%^C054%^(%^C060%^illuminated%^C054%^)%^CRST%^"}));
    addSpellToCaster();
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect",spell_duration);

}

void dest_effect(){
    if(objectp(target)) {
        tell_room(place,"%^CRST%^%^RESET%^%^C067%^The %^C073%^ghastly mist%^C067%^ slowly dissipates from around "+target->query_cap_name()+", releasing "+target->query_subjective()+" from its %^C060%^ominous%^C067%^ grip.%^CRST%^");
        tell_object(target,"%^CRST%^%^RESET%^%^C067%^The %^C073%^ghastly mist%^C067%^ slowly dissipates, releasing you from its %^C060%^ominous%^C067%^ grip.");
        target->remove_property("faerie fire");
        target->remove_property_value("added short",({"(illuminated)"}));
        target->add_ac_bonus(bonus);
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();

}