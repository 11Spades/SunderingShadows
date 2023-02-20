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
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^A %^C102%^dirty mutt%^C101%^ scampers past with a %^C102%^small fish%^C101%^ in its mouth.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C103%^Seagulls circle overhead, now and then diving down to grab a bite to eat.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^A crew of sailors sing an %^C107%^old shanty%^C101%^ as they work.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^Waves crash against the old wooden wharf making it %^C102%^creak%^C101%^ and %^C102%^groan%^C101%^.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^A small boat sets sail for the open sea.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C102%^A few %^C101%^rough looking men%^C102%^ shove past carrying a load of %^C101%^heavy crates%^C102%^.%^CRST%^");
                break;
            case 6 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^Voices call back and forth as crews work to unload their holds.%^CRST%^");
                break;
            case 7 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C103%^The doxies preen and pose as %^C104%^leering sailors%^C103%^ watch with %^C104%^hungry eyes%^C103%^.%^CRST%^");
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

