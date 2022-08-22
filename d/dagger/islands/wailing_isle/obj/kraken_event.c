// Chernobog (7/18/22)
// Wailing Isle - Kraken Event

#include <std.h>
#include <daemons.h>
#include "../defs.h"

inherit OBJECT;

int tentacles, powerlevel;

void create(){
    ::create();
    set_name("kraken event");
    set_id(({"kraken_event", "event"}));
    set_short("");
    set_long("");
    set_weight(100000);
    set_property("no animate",1);
    tentacles = 8;
    powerlevel = 5;
}

void init(){
    ::init();
    add_action("steer_fun", "steer");
}

int steer_fun(string str){
    if(!str) return 0;
    message("info", "%^RESET%^%^CRST%^%^C059%^Something seems to have taken hold of the rudder... it doesn't look like you're going anywhere.%^CRST%^", this_player());
    return 1;
}

void start_event(int power){
    object tentacle, room, controller;
    int i;
    
    powerlevel = power;
    controller = this_object();
    room = environment(controller);
    tentacles = 4;
    
    message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r %^RESET%^%^C109%^suddenly froths as %^C108%^te%^C107%^n%^C106%^tac%^C107%^l%^C108%^es %^RESET%^%^C109%^erupt from the sea, surrounding the ship and %^C245%^c%^C243%^l%^C059%^osi%^C243%^n%^C245%^g %^RESET%^%^C109%^in!%^CRST%^\n", room);
    
    for(i = 0; i < tentacles; i++){
        tentacle = new(MON"kraken_tentacle");
        tentacle->set_powerlevel(powerlevel);
        tentacle->set_controller(controller);
        tentacle->move(room);
    }
    return;
}

void remove_tentacle(){
    object room;
    
    tentacles--;
    if(!tentacles){
        room = environment(this_object());
        call_out("intermission", 3, (random(5) + 2), room);
    }
    return;
}

void intermission(int counter, object room){
    int i;
    object *targets = ({ });
    
    if(counter < 1){
        phase_two();
        return;
    }
    switch(random(8)){
        case 0..2 :
            message("environment", "%^RESET%^%^CRST%^%^C107%^The boat suddenly %^C102%^s%^C109%^h%^C116%^u%^C102%^d%^C109%^d%^C117%^e%^C102%^r%^C109%^s %^RESET%^%^C107%^as something %^C118%^slams %^C107%^into the %^C058%^hull%^C107%^!%^CRST%^", room);
            targets = all_living(room);
            for(i = 0; i < sizeof(targets); i++){
                if(!objectp(targets[i])) continue;
                if(avatarp(targets[i])) continue;
                if(SAVING_THROW_D->reflex_save(targets[i], (powerlevel * 17))){
                    message("combat_special", "%^RESET%^%^CRST%^%^C118%^You manage to keep your footing on the deck.%^CRST%^", targets[i]);
                }
                else{
                    if(!userp(targets[i])){
                        message("combat_special", "%^RESET%^%^CRST%^%^C124%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C124%^ stumbles backwards, falling overboard!%^CRST%^", room);
                        targets[i]->move("/d/shadowgate/void");
                        targets[i]->die();
                        continue;
                    }
                    message("combat_special", "%^RESET%^%^CRST%^%^C196%^You stumble, crashing down onto the deck!%^CRST%^", targets[i]);
                    message("combat_special", "%^RESET%^%^CRST%^%^C196%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^ stumbles, crashing down onto the deck!%^CRST%^", room, targets[i]);
                    targets[i]->set_tripped(2, "%^RESET%^%^CRST%^%^C109%^You're still struggling back onto your feet!%^CRST%^");
                }
                continue;
            }
            break;
        case 3 :
            message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r %^RESET%^%^C105%^ch%^C098%^u%^C105%^rn%^C098%^s %^C109%^and %^C255%^f%^C159%^ro%^C255%^t%^C159%^h%^C255%^s %^C109%^from something lurking beneath the %^RESET%^%^C111%^wa%^C117%^ve%^C123%^s%^C109%^.%^CRST%^\n", room);
            break;
        case 4 :
            message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C102%^cries %^C109%^of %^C255%^gul%^C250%^l%^C255%^s %^C109%^ring out as they circle overhead, expectantly watching the %^C117%^s%^C123%^e%^C117%^a %^RESET%^%^C109%^below...%^CRST%^\n", room);
            break;
        case 5 :
            message("environment", "%^RESET%^%^CRST%^%^C109%^A %^C108%^l%^C107%^o%^C106%^ng %^C108%^do%^C107%^rs%^C106%^al %^C108%^f%^C107%^i%^C106%^n %^RESET%^%^C109%^breaks the surface of the %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r%^RESET%^%^C109%^, slipping just as quickly out of %^C103%^sight%^C109%^.%^CRST%^\n", room);
            break;
        case 6 :
            message("environment", "%^RESET%^%^CRST%^%^C109%^Something swirls %^C103%^heavily %^C109%^beneath the %^RESET%^%^C111%^wa%^C117%^ve%^C123%^s%^C109%^, circling the ship with %^C108%^p%^C107%^r%^C106%^edato%^C107%^r%^C108%^y i%^C107%^n%^C106%^te%^C107%^n%^C108%^t%^C109%^.%^CRST%^\n", room);
            break;
        default :
            message("environment", "%^RESET%^%^CRST%^%^C109%^A %^C104%^d%^C098%^ar%^C104%^k s%^C098%^h%^C092%^ad%^C098%^o%^C104%^w %^RESET%^%^C109%^moves through the %^RESET%^%^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r %^RESET%^%^C109%^below, %^C103%^gargantuan %^C109%^and %^C103%^indistinct%^C109%^...%^CRST%^\n", room);
    }
    counter--;
    call_out("intermission", (random(6) + 5), counter, room);
    return;
}

void phase_two(){
    object kraken;
    
    message("info", "%^RESET%^%^CRST%^%^C109%^With a %^C103%^th%^C097%^un%^C091%^de%^C097%^ro%^C103%^us r%^C097%^oa%^C103%^r%^RESET%^%^C109%^, a massive form rises up from below. Waves of water crash over the %^C101%^s%^C100%^hi%^C101%^p %^RESET%^%^C109%^as the beast attacks... a %^C106%^d%^C112%^r%^C118%^ead%^C112%^e%^C106%^d %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n%^C109%^!%^CRST%^", ETO);
    
    kraken = new(MON"juvenile_kraken");
    kraken->set_powerlevel(powerlevel);
    kraken->move(environment(this_object()));
    end_event();
    return;
}

void end_event(){
    this_object()->remove();
    return;
}

