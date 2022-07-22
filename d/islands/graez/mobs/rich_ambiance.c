// Rich Area Streets - LoKi
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
                tell_room(room, "%^C066%^A squad of %^C242%^private security%^C066%^ marches past you on the %^C094%^street%^C066%^, a %^C135%^nobleman%^C066%^ walking in the centre of their %^C244%^formation%^CRST%^.");
                break;
            case 1 : 
                tell_room(room, "%^C081%^A %^C159%^flare of power%^C081%^ can be seen from the top of the %^C059%^tower %^C081%^at the northwest corner of the city.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^C109%^Children %^C107%^run past you, playing a %^C101%^game%^C107%^.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^C143%^Merchants squabble over a %^C214%^contract %^C143%^near you.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^C244%^A %^C059%^young soldier%^C244%^ in %^C230%^gleaming plate%^C244%^ lazily watches the crowds.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^C075%^A %^C069%^young couple%^C075%^ walks by without a care in the %^C058%^world%^C075%^.%^CRST%^");
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