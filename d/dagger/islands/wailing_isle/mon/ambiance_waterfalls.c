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
    set_property("no charm", 1);
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
        switch(random(7)){
            case 0 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C080%^Light %^C087%^dances%^C080%^ across the surface of the %^C087%^clear water%^C080%^.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C086%^The scattered %^C085%^coins%^C086%^ glimmer enticingly beneath the water.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C081%^A small fish %^C080%^languidly%^C081%^ swims through the shallows.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C041%^Birds sing sweetly from the nearby forest.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C153%^Rainbows leap between the rivulets of water cascading down the cliffs.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C080%^A sprinkling of water mists across the %^C086%^mossy rocks%^C080%^.%^CRST%^");
                break;
            case 6 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C255%^A long, %^C250%^l%^C248%^o%^C247%^w %^C245%^w%^C243%^a%^C245%^i%^C247%^l%^RESET%^%^C255%^ is carried on the rising wind.%^CRST%^");
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

