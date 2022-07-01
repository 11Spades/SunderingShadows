// Poor Streets - LoKi
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
                tell_room(room, "%^C059%^A %^C160%^meager camp fire%^C059%^ burns under an awning, %^C065%^children%^C059%^ huddled around it.%^CRST%^");
                break;
            case 1 : 
                tell_room(room, "%^C101%^A %^C241%^crippled soldier%^C101%^ whimpers from the shadows.%^CRST%^");
                break;
            case 2 : 
                tell_room(room, "%^C244%^A %^C059%^grizzled soldier%^C244%^ patrols silently.%^CRST%^");
                break;
            case 3 : 
                tell_room(room, "%^C102%^You hear a %^C124%^scream %^C102%^from an %^C059%^alleyway%^C102%^, then earie silence.%^CRST%^");
                break;
            case 4 : 
                tell_room(room, "%^C143%^A pair of %^C244%^drunk soldiers%^C143%^ push past you.%^CRST%^");
                break;
            case 5 : 
                tell_room(room, "%^C136%^The sounds of the %^C088%^battlefield %^C136%^echo around you.%^CRST%^");
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