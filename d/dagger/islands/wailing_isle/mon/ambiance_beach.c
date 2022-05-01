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
                tell_room(room, "%^RESET%^%^CRST%^%^C186%^Small %^C159%^waves%^C186%^ lap at the shoreline.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C186%^A %^C180%^crab%^C186%^ scurries beneath the %^C187%^sand%^C186%^.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C186%^Seagulls %^C187%^circle%^C186%^ overhead, now and then %^C187%^diving%^C186%^ down to grab a bite to eat.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C187%^Some shouts coming from the wharf are muffled by the breeze.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C195%^A salty sea breeze picks up, tugging at your clothing.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C186%^A %^C153%^small wave%^C186%^ crashes upon the shore, the waterline rising high before quickly receding.%^CRST%^");
                break;
            case 6 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C186%^A sandpiper hops along the shore, poking around for a meal.%^CRST%^");
                break;
            case 7 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C194%^Light scatters like %^C153%^diamonds%^C194%^ across the surface of the %^C086%^turquoise sea%^C194%^.%^CRST%^");
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

