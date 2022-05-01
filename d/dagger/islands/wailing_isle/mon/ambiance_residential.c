// Chernobog (10/28/21)
// Ambiance Device

#include <std.h>
inherit MONSTER;

void create(){
    ::create();
    set_name("ambiance device");
    set_id(({"ambiance device"}));
    set_short("You see NOTHING.");
    add_limb("body","",0,0,0);
    set_property("no detect",1);
    set_invis();
}

void heart_beat(){
    object ambiance, room;
    
    ::heart_beat();
    
    ambiance = this_object();
    room = environment(ambiance);
    if(!objectp(ambiance)) return;
    if(!objectp(room)) return;
    
    if(random(100) < 4){
        switch(random(8)){
            case 0 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C245%^A %^C243%^h%^C244%^e%^C245%^a%^C246%^rt-%^C243%^wr%^C244%^en%^C245%^ch%^C246%^ing %^C243%^w%^C244%^a%^C245%^i%^C246%^l%^C245%^ from the %^C248%^cliffs%^C245%^ overhead %^C059%^e%^C243%^c%^C245%^ho%^C243%^e%^C059%^s%^RESET%^%^C245%^ through the quiet streets.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C138%^A %^C244%^slinky black cat%^C138%^ slips between some boards, vanishing into one of the dilapidated homes%^C138%^.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C138%^Some grubby kids run past, chasing each other with %^C101%^sticks%^C138%^ and %^C101%^stones%^C138%^.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C058%^A %^C059%^rat%^C058%^ scurries across the road.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C253%^A long, %^C249%^l%^C247%^o%^C245%^w %^C243%^wail%^RESET%^%^C253%^ is carried on the r%^C250%^i%^C248%^s%^C253%^ing wi%^C250%^n%^C253%^d%^RESET%^%^C253%^.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C139%^A litany of %^C244%^curses%^C139%^ that would make a sailor blush spills out from a nearby house.%^CRST%^");
                break;
            case 6 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C138%^Neighbors shout out from window to window, discussing the day's events.%^CRST%^");
                break;
            case 7 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C102%^Eyes peer out at you from an upper floor window before the curtain is quickly pulled shut.%^CRST%^");
                break;
            default :
                tell_room(room, "Something broke here, tell Chernobog");
        }
    }
}

void die(object ob){}
int do_damage(string str, int i){ return 0;}
int is_invincible(){ return 1;}
int is_detectable(){ return 0;}
void set_invis(){
    if (this_object()->query_invis()) return;
    else ::set_invis();
    return;
}

