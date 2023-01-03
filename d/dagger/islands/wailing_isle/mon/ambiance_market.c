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
        switch(random(8)){
            case 0 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C109%^People dodge out of the way as a %^C108%^pig%^C109%^ comes squealing down the road.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C108%^Angry shouts%^C109%^ are followed by a %^C108%^collective cheer%^C109%^ as a %^C110%^fight%^C109%^ breaks out.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C109%^Glass %^C108%^shatters%^C109%^ somewhere nearby.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C109%^Laughter breaks out from a small gathering of sailors playing dice in a doorway.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C108%^An old pirate pushes his way through the crowd, the monkey riding his shoulder %^C109%^hissing%^C108%^ as they pass.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C109%^A %^C110%^charming lutist%^C109%^ weaves her way through the crowd, %^C110%^singing%^C109%^ as she sashays along.%^CRST%^");
                break;
            case 6 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C110%^A flock of %^C111%^seagulls%^C110%^ appears in a flurry of feathers and squawks to pick at a pile of %^C111%^garbage%^C110%^.%^CRST%^");
                break;
            case 7 : 
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

