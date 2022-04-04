// cigar by Odin 5/2/2020
// altered by Chernobog (1/27/21)
// updated and reduced spam - Chernobog (4/4/22)

#include <std.h>

inherit OBJECT;

int lit, charges;

void create(){
    ::create();
    set_name("cigarette");
    set_id(({ "cigarette" }));
    set_short("%^RESET%^%^CRST%^%^C136%^slender %^C255%^ci%^C252%^g%^C255%^ar%^C252%^e%^C255%^tt%^C252%^e%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C136%^This is a crude, hand rolled %^C255%^ci%^C252%^g%^C255%^ar%^C252%^e%^C255%^tt%^C252%^e%^RESET%^%^C136%^. Dried, aromatic tobacco has been tucked within a roll of thin parchment paper.\n\n%^RESET%^%^CRST%^%^C059%^Try smoking it. Douse it to put it out.%^CRST%^");
    set_weight(0);
    set_value(50);
    lit = 0;
    charges = 30 + random(10);
}

void init(){
    ::init();
    add_action("extinguish", "douse");
    add_action("smoke", "smoke");
}

int smoke(string str){
    object player, cigarette, room;
    
    if(!id(str)){
        notify_fail("Smoke what?\n");
        return 0;
    }
    if(lit){
        notify_fail("You're already smoking it!\n");
        return 0;
    }
    
    cigarette = this_object();
    player = environment(cigarette);
    room = environment(player);
    tell_object(player, "%^BOLD%^%^BLACK%^You begin smoking your cigarette.%^RESET%^\n");
    tell_room(room, "%^BOLD%^%^BLACK%^"+player->query_cap_name()+" %^BOLD%^%^BLACK%^begins smoking a cigarette.\n%^RESET%^", player);
    cigarette->set_property("added short", ({ "%^RESET%^%^CRST%^ %^C214%^(%^C202%^l%^C196%^i%^C202%^t%^C214%^)%^CRST%^" }));
    call_out("take_drag", 5);
    lit = 1;
    return 1;
}

int extinguish(string str){
    object player, cigarette, room;
    
    if(!id(str)){
        notify_fail("Douse what?\n");
        return 0;
    }
    if(!lit){
        notify_fail("Your cigarette is not lit!\n");
        return 0;
    }
    
    cigarette = this_object();
    player = environment(cigarette);
    room = environment(player);
    tell_object(player, "%^RESET%^%^CRST%^%^C059%^You douse your cigarette.%^CRST%^\n");
    tell_room(room, "%^RESET%^%^CRST%^%^C059%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^ douses a cigarette.%^CRST%^\n", player);
    remove_call_out("take_drag");
    lit = 0;
    cigarette->remove_property_value("added short", ({ "%^RESET%^%^CRST%^ %^C214%^(%^C202%^l%^C196%^i%^C202%^t%^C214%^)%^CRST%^" }));
    cigarette->remove_property("added short");
    return 1;
}

void take_drag(){
    object player, room;
    int i;
    
    player = environment(this_object());
    room = environment(player);
    if(!living(player)) call_out("go out", 2);
    if(charges < 1) call_out("go_out", 1);
    tell_object(player, "%^RESET%^%^CRST%^%^C250%^Sm%^C248%^ok%^C246%^e g%^C244%^en%^C059%^tl%^C244%^y t%^C246%^ra%^C248%^il%^C250%^s u%^C248%^pw%^C246%^ar%^C244%^ds %^C059%^fr%^C244%^om %^C246%^th%^C248%^e %^RESET%^%^C124%^e%^C196%^m%^C124%^b%^C196%^e%^C124%^r %^RESET%^%^C248%^o%^C250%^f y%^C248%^ou%^C246%^r c%^C244%^ig%^C059%^ar%^C244%^et%^C246%^te%^C248%^.%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C250%^Sm%^C248%^ok%^C246%^e g%^C244%^en%^C059%^tl%^C244%^y t%^C246%^ra%^C248%^il%^C250%^s u%^C248%^pw%^C246%^ar%^C244%^ds %^C059%^fr%^C244%^om %^C246%^th%^C248%^e %^RESET%^%^C124%^e%^C196%^m%^C124%^b%^C196%^e%^C124%^r %^RESET%^%^C248%^o%^C250%^f %^RESET%^%^C248%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C248%^'s %^C246%^ci%^C244%^ga%^C059%^re%^C244%^tt%^C246%^e.%^CRST%^", player);
    call_out("take_drag", random(30) + 60);
    charges--;
}

void go_out(){
    object player, room, cigarette;
    
    cigarette = this_object();
    player = environment(cigarette);
    room = environment(player);
    tell_object(player, "%^RESET%^%^CRST%^%^C059%^Your cigarette goes out, and you dispose of the remaining butt.%^CRST%^\n");
    tell_room(room, "%^RESET%^%^CRST%^%^C059%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^'s cigarette goes out, and "+player->query_subjective()+" disposes of the remaining butt.%^CRST%^\n", player);
    remove_call_out("take_drag");
    lit = 0;
    cigarette->remove_property_value("added short", ({ "%^RESET%^%^CRST%^ %^C214%^(%^C202%^l%^C196%^i%^C202%^t%^C214%^)%^CRST%^" }));
    cigarette->remove_property("added short");
    cigarette->remove();
}

remove(){
    if (lit){
        lit = 0;
        remove_call_out("take_drag");
        this_object()->remove_property("lit cigar");
    }
    return ::remove();
}

int is_cigarette(){
    return 1;
}

