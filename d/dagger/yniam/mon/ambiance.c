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
    
    if(!room->get_occupied()) return;
    
    if(random(100) < 4){
        switch(room->get_temperment()){
            case 1 : //normal
                if(random(2)) tell_room(room, "%^RESET%^%^CRST%^%^C108%^The goblin lets out a low growl from within the cage, gnashing its teeth at you.%^CRST%^");
                else tell_room(room, "%^RESET%^%^CRST%^%^C108%^Narrowing its beady little eyes, the goblin grabs hold of the bars of its cage and glares at you.%^CRST%^");
                break;
            case 2 : //stoned
                if(random(2)) tell_room(room, "%^RESET%^%^CRST%^%^C108%^Slumped in a corner of its cage, the goblin lets out a low keening hum.%^CRST%^");
                else tell_room(room, "%^RESET%^%^CRST%^%^C108%^The goblin raises a hand up in the light, staring at it with wide eyes and a slack jaw.%^CRST%^");
                break;
            case 3 : //pcp'd
                if(random(2)) tell_room(room, "%^RESET%^%^CRST%^%^C108%^Snarling and drooling, the goblin rails against its cage, bruising and breaking its own limbs as it throws itself at the iron bars.%^CRST%^");
                else tell_room(room, "%^RESET%^%^CRST%^%^C108%^The goblin rips and tears at itself in a frenzy, growling and biting its own arms as it thrashes about on the floor of its cage.%^CRST%^");
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

