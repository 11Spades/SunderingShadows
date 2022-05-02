// Chernobog & Titania (2/21/22)
// Fishing Net (Cast)

#include <std.h>
#include "../defs.h"

inherit OBJECT;

string source;
int num_fish, quality, can_catch, uses, fishing;

void create(){
    ::create();
    set_name("fishing net");
    set_id(({"net", "fishing net", "fishing line", "line", "cast fishing net"}));
	set_short("%^RESET%^%^CRST%^%^C058%^a %^C130%^fi%^C136%^s%^C130%^hin%^C136%^g %^C130%^l%^C136%^i%^C130%^ne%^RESET%^%^C058%^ bound to the docks%^CRST%^");
	set_long("%^RESET%^%^CRST%^%^C058%^It appears to be connected to a submerged %^C130%^fi%^C136%^s%^C130%^hin%^C136%^g %^C130%^n%^C136%^e%^C130%^t%^RESET%^%^C058%^ nearby. You can %^C226%^<%^C220%^gather the net%^C226%^> %^RESET%^%^C058%^to bring it back up.%^CRST%^");
	set_weight(10000);
	set_value(100);
    source = "docks";
    num_fish = 1;
    quality = 0;
    can_catch = 0;
    fishing = 0;
}

void init(){
    ::init();
    add_action("gather_fun", "gather");
}

void set_uses(int new_total){
    uses = new_total;
    return;
}

int gather_fun(string str){
    object player, room, net;
    
    if((str != "net") && (str != "the net")) return 0;
    
    player = this_player();
    room = environment(player);
    fishing = 0;
    
    tell_object(player, "%^RESET%^%^CRST%^%^C058%^You grab the %^C130%^l%^C136%^i%^C130%^ne %^RESET%^%^C058%^and gather up the %^C130%^fi%^C136%^s%^C130%^hin%^C136%^g %^C130%^n%^C136%^e%^C130%^t%^RESET%^%^C058%^.%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ grabs the %^C130%^l%^C136%^i%^C130%^ne %^RESET%^%^C058%^and gathers up the %^C130%^fi%^C136%^s%^C130%^hin%^C136%^g %^C130%^n%^C136%^e%^C130%^t%^RESET%^%^C058%^.%^CRST%^", player);
    fish_haul(room);
    if(uses < 1) tell_room(room, "%^RESET%^%^CRST%^%^C059%^The %^C130%^n%^C136%^e%^C130%^t %^RESET%^%^C059%^has seen too much use and %^C124%^rips%^RESET%^%^C059%^, making itself useless.%^CRST%^\n");
    if(uses > 0){
        net = new(OBJ"fishing_net");
        net->move(player);
        net->set_uses(uses);
    }
    this_object()->remove();
    return 1;
}

void start_fishing(){
    object room;
    room = environment(this_object());
    
    fishing = 1;
    call_out("still_fishing", random(5) + 5, room);
    return;
}

void check_net(object room){
    int catch_chance;
    
    if(!fishing) return;
    
    if(random(2)){
        call_out("still_fishing", 1, room);
        return;
    }
    catch_chance = random (100);
    switch(catch_chance){
        case 0..14:
            quality = 2;
            num_fish = 1;
            tell_room(room, "\n%^RESET%^%^CRST%^%^C109%^A %^C103%^large shadow %^C109%^obscures the view of the net.%^CRST%^");
            call_out("catch_now", random(3) + 1, room);
            break;
        case 15..49 :
            quality = 1;
            num_fish = random(3) + 3;
            tell_room(room, "\n%^RESET%^%^CRST%^%^C109%^A cluster of %^C103%^small shadows %^C109%^flit beneath the surface of the water.%^CRST%^");
            call_out("catch_now", random(3) + 3, room);
            break;
        case 50..84 :
            quality = 1;
            num_fish = random(2) + 1;
            tell_room(room, "\n%^RESET%^%^CRST%^%^C109%^A %^C103%^small shadow %^C109%^darts through the water.%^CRST%^");
            call_out("catch_now", random(3) + 5, room);
            break;
        case 85..99 :
            quality = 0;
            num_fish = 1;
            tell_room(room, "\n%^RESET%^%^CRST%^%^C109%^Some %^C103%^murky shadows %^C109%^drift beneath the waves.%^CRST%^");
            call_out("catch_now", random(3) + 3, room);
            break;
    }
    can_catch = 1;
    return;
}

void catch_now(object room){
    if(!fishing) return;
    
    tell_room(room, "%^RESET%^%^CRST%^%^C108%^The %^C103%^shadows %^C108%^pass, leaving the water clear.%^CRST%^\n");
    can_catch = 0;
    still_fishing(room);
    return;
}

void still_fishing(object room){  
    if(!fishing) return;
    
    switch(random(6)){
        case 0 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^The %^C033%^w%^C039%^a%^C045%^v%^C039%^e%^C033%^s %^RESET%^%^C108%^sway and bob, obscuring a clear view of the %^C130%^n%^C136%^e%^C130%^t%^RESET%^%^C108%^.%^CRST%^");
            break;
        case 1 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^An errant %^C039%^w%^C045%^a%^C039%^v%^C033%^e %^RESET%^%^C108%^sends up a %^C045%^cooling %^C051%^spray %^RESET%^%^C108%^in the air.%^CRST%^");
            break;
        case 2 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^Light reflects off the surface of the %^C033%^w%^C039%^a%^C045%^t%^C039%^e%^C033%^r %^RESET%^%^C108%^as it swells into low %^C033%^w%^C039%^a%^C045%^v%^C039%^e%^C033%^s%^RESET%^%^C108%^.%^CRST%^");
            break;
        case 3 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^The %^C033%^w%^C039%^a%^C045%^t%^C039%^e%^C033%^r %^RESET%^%^C108%^splashes to and fro, the movement making it hard to see into the %^C059%^depths%^RESET%^%^C108%^.%^CRST%^");
            break;
        case 4 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^A %^C033%^s%^C039%^p%^C045%^r%^C039%^a%^C033%^y %^RESET%^%^C108%^of %^C033%^w%^C039%^a%^C045%^t%^C039%^e%^C033%^r %^C051%^mists %^RESET%^%^C108%^across your face.%^CRST%^");
            break;
        case 5 :
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^A few hungry %^C255%^gu%^C252%^l%^C255%^l%^C252%^s %^RESET%^%^C108%^swoop through the air, letting out %^C124%^shrill %^C196%^cries%^RESET%^%^C108%^.%^CRST%^");
            break;
    }
    call_out("check_net", random(10) + 5, room);
    return;
}

void fish_haul(object room){
    int i, location;
    object fish;
    
    if(!can_catch){
        tell_room(room, "%^RESET%^%^CRST%^%^C124%^It seems the net was empty.%^CRST%^\n");
        return;
    }
    
    if(room->is_dock()) location = 1;
    if(room->is_boat()) location = 2;
    
    tell_room(room, "%^RESET%^%^CRST%^%^C058%^The contents of the net spill out onto the ground.%^CRST%^\n");
    
    for(i = 0; i < num_fish; i++){
        if(!quality) fish = new(OBJ"garbage");
        if(quality) fish = new(OBJ"fish");
        fish->set_fish(quality, location);
        fish->move(room);
        continue;
    }
    uses--;
    return;
}

