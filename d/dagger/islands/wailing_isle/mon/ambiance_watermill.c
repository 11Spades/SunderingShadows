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
        switch(random(6)){
            case 0 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C037%^The old wheel %^C038%^creaks%^C037%^ and %^C038%^groans%^C037%^ as it turns.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C037%^The water churns tumultuously, causing waves to splash over the muddy river bank.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C037%^The river flows swiftly by, burbling along its rocky bed.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C041%^Birds sing sweetly from the nearby forest.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C255%^A %^C250%^ha%^C248%^un%^C246%^ti%^C244%^ng %^C243%^w%^C246%^a%^C248%^i%^C250%^l%^C255%^ from above is nearly muffled by the loud churning of the wheel.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C043%^A bird watches you from atop the old mill.%^CRST%^");
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

