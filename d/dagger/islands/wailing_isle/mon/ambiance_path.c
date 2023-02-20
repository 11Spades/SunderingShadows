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
        switch(random(5)){
            case 0 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C245%^A %^C243%^h%^C244%^e%^C245%^a%^C246%^rt-%^C243%^wr%^C244%^en%^C245%^ch%^C246%^ing %^C243%^w%^C244%^a%^C245%^i%^C246%^l%^C245%^ from the %^C248%^cliffs%^C245%^ overhead %^C059%^e%^C243%^c%^C245%^ho%^C243%^e%^C059%^s%^RESET%^%^C245%^ through the quiet path.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C041%^Birds chirp from deeper in the %^C040%^lush forest%^C076%^.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C101%^Waves crash along the %^C102%^rocky precipice%^C101%^ below.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^RESET%^%^CRST%^%^C041%^Branches snap and crack as something darts among the %^C040%^foliage%^C076%^.%^CRST%^");
                break;
            case 4 : 
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

