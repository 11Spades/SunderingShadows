// Chernobog (4/12/22)
// Garrote Wire Object

#include <std.h>
#include <daemons.h>

inherit OBJECT;

int duration;

void create(){
    ::create();
    set_name("tripping_obj");
    set_id(({"tripping_obj"}));
    set_weight(0);
    set_property("no animate",1);
    set_hidden(1);
    duration = (random(3) * 3) + 6;
    set_heart_beat(1);
}

void init(){
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    if(!objectp(tripping)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    
    add_action("say_fun","say");
    
    victim->set_property("strangled", 1);
    victim->set_static("spell interrupt", "%^RESET%^%^CRST%^%^C196%^The %^C244%^w%^C248%^i%^C244%^r%^C059%^e%^RESET%^%^C196%^ is tight around your throat, cutting off all speech!%^CRST%^");
    victim->set_property("spell interrupt", "%^RESET%^%^CRST%^%^C196%^The %^C244%^w%^C248%^i%^C244%^r%^C059%^e%^RESET%^%^C196%^ is tight around your throat, cutting off all speech!%^CRST%^");
}

void heart_beat(){
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    if(!objectp(tripping)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    
    tell_object(victim, "%^RESET%^%^CRST%^%^C196%^The %^C244%^w%^C248%^i%^C244%^r%^C059%^e%^RESET%^%^C196%^ is tight around your throat!%^CRST%^");
    victim->cause_typed_damage(victim, "torso", 10, "slashing");
    
    duration--;
    if(duration < 0) stop_garrote();
    return;
}

void stop_garrote(){
    object victim, garrote;
    garrote = this_object();
    victim = environment(garrote);
    
    victim->set_static("spell interrupt", 0);
    victim->remove_property("spell interrupt");
    tell_object(victim, "%^RESET%^%^CRST%^%^C144%^You manage to free yourself of the garrote, breaking it and tossing it aside.%^CRST%^");
    tell_room(environment(victim), "%^RESET%^%^CRST%^%^C144%^"+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C144%^ manages to free themself of the garrote, breaking it and tossing it aside.%^CRST%^", victim);
    victim->remove_property("strangled");
    garrote->remove();
    return;
}

int say_fun(string str){
    object victim;
    victim = environment(this_object());
    
    tell_object(victim, "%^RESET%^%^CRST%^%^C059%^You try to speak, but the %^C244%^w%^C248%^i%^C244%^r%^C059%^e%^RESET%^%^C059%^ around your throat cuts off everything except a %^C124%^s%^C196%^tra%^C124%^n%^C196%^gle%^C124%^d g%^C196%^urgl%^C124%^e%^RESET%^%^C059%^!%^CRST%^");
    tell_room(environment(victim), "%^RESET%^%^CRST%^%^C059%^"+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^ tries to speak, but the %^C244%^w%^C248%^i%^C244%^r%^C059%^e%^RESET%^%^C059%^ around their throat cuts off everything except a %^C124%^s%^C196%^tra%^C124%^n%^C196%^gle%^C124%^d g%^C196%^urgl%^C124%^e%^RESET%^%^C059%^!%^CRST%^", victim);
    return 1;
}

int is_invincible(){ return 1;}
int is_detectable(){ return 0;}

