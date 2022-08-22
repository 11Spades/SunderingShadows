// Chernobog (12/1/21)
// Wailing Isle - Kraken Binding Effect

#include <std.h>
#include <daemons.h>
inherit OBJECT;

int counter, duration, powerlevel, cooldown, grip;
object stomach, kraken;

void create(){
    ::create();
    set_name("kraken_binding");
    set_id(({"kraken_binding"}));
    set_weight(0);
    set_property("no animate",1);
    set_hidden(1);
    set_heart_beat(1);
    duration = 4;
    cooldown = 0;
}

void init(){
    object binding, victim;
    binding = this_object();
    victim = environment(binding);
    
    if(!objectp(binding)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    
    victim->set_paralyzed(1000, "%^RESET%^%^CRST%^%^C109%^You're still struggling against the hold of the tentacle!%^CRST%^");
    victim->set_property("kraken_bound", 1);
    add_action("struggle_fun", "struggle");
    powerlevel = max(({ victim->query_level() / 10, 1 }));
    grip = powerlevel;
}

int struggle_fun(){
    object victim, room;
    victim = this_player();
    room = environment(victim);
    
    if(cooldown){
        message("info", "%^RESET%^%^CRST%^%^C088%^You need to catch your breath before struggling again!%^CRST%^", victim);
        return 1;
    }
    if(victim->query_stats("strength") > random(30)){
        message("environment", "%^RESET%^%^CRST%^%^C109%^You struggle against the grip of the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^, pushing it back!%^CRST%^", victim);
        grip -= 3;
    }
    else{
        message("environment", "%^RESET%^%^CRST%^%^C109%^You struggle feebly against the grip of the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^...%^CRST%^", victim);
        grip -= 1;
    }
    message("environment", "%^RESET%^%^CRST%^%^C109%^"+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C109%^ struggles against the grip of a %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^...%^CRST%^", room, victim);
    cooldown = 2;
    
    if(grip < 1){
        message("environment", "%^RESET%^%^CRST%^%^C118%^...and you manage to escape, slipping free of the writhing appendage!%^CRST%^", victim);
        message("environment", "%^RESET%^%^CRST%^%^C118%^...and manages to escape, slipping free of the writhing appendage!%^CRST%^", room, victim);
        end_binding();
    }
    return 1;
}

void heart_beat(){
    object binding, victim, room;
    binding = this_object();
    victim = environment(binding);
    
    if(!objectp(victim)) return;
    
    room = environment(victim);
    
    if(!objectp(binding)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    if(!present("juvenile kraken", room)) end_binding();
    if(!victim->query_paralyzed()) end_binding();
    
    if(counter == 2){
        message("environment", "%^RESET%^%^CRST%^%^C100%^The %^C058%^deck %^C100%^of the ship scrapes along your side as the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C100%^ drags you closer to the kraken's maw... if you don't %^C144%^struggle%^C100%^ free, you're going to be devoured whole!%^CRST%^", victim);
        message("environment", "%^RESET%^%^CRST%^%^C100%^A %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C100%^ drags "+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C100%^ across %^C058%^deck %^C100%^of the ship, heading for the kraken!%^CRST%^", room, victim);
    }
    
    counter++;
    if(counter > 3){
        counter = 1;
        duration--;
    }
    if(cooldown){
        cooldown--;
        if(!cooldown) message("environment", "%^RESET%^%^CRST%^%^C116%^You've caught your breath, ready to fight back again!%^CRST%^", victim);
    }
    
    if(duration < 0){
        if(kraken) kraken->devour_victim(victim, room);
        end_binding();
    }
    return;
}

void devour_victim(object victim, object room){
    message("environment", "%^RESET%^%^CRST%^%^C109%^With a final heave, the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^ tosses you through the air in a slow arc... and down into the kraken's awaiting %^C124%^maw%^C109%^.%^CRST%^", victim);
    message("environment", "%^RESET%^%^CRST%^%^C109%^With a final heave, the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^ tosses "+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C109%^ through the air in a slow arc... and down into the kraken's awaiting %^C124%^maw%^C109%^.%^CRST%^", room, victim);
    
    victim->move(stomach);
    end_binding();
    return;
}

void end_binding(){
    object binding, victim, room;
    binding = this_object();
    victim = environment(binding);
    room = environment(victim);
    
    message("environment", "%^RESET%^%^CRST%^%^C144%^The %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C144%^ releases its grip on you and withdraws.%^CRST%^", victim);
    message("environment", "%^RESET%^%^CRST%^%^C144%^The %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C144%^ releases its grip on "+victim->query_cap_name()+"%^RESET%^%^CRST%^%^C144%^ and withdraws.%^CRST%^", room, victim);
    victim->remove_property("kraken_bound");
    victim->set_paralyze(0);
    binding->remove();
    return;
}

void set_stomach(object stomach_room){
    stomach = stomach_room;
    return;
}

void set_controller(object controller){
    kraken = controller;
    return;
}

int save_me(string file){ return 1;}
int is_invincible(){ return 1;}
int is_detectable(){ return 0;}

