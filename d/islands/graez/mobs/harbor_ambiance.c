// Docks Streets - LoKi
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
                tell_room(room, "%^C081%^A massive %^C094%^three mast galleon%^C081%^ sails out of the %^C094%^harbor%^C081%^, its %^C214%^square sails%^C081%^ filled with the wind.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^C102%^You watch a series of %^C094%^wagons %^C102%^pass by loaded with %^C059%^supplies%^C102%^.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^C137%^A sleek sloop with a %^C239%^black triangle sail%^C137%^ sails past the %^C094%^docks%^C137%^.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^C172%^A %^C255%^seagull %^C172%^caws overhead.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^C144%^A group of %^C101%^sailors %^C144%^push past you, headed to the tavern.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^C066%^A squad of %^C240%^grizzled veteran%^C066%^ soldiers patrol the %^C094%^dockside%^C066%^.%^CRST%^");
                break;
            default :
                tell_room(room, "Something broke here, tell LoKi");
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