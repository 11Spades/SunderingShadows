#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_atrium.c";

void create(){
   ::create();

set_exits(([
"northeast" : BONE"18",
"southeast" : BONE"15",

]));

add_item("mirror","Dominating one wall is a %^C189%^massive mirror%^CRST%^. What is strange is that the %^C195%^mirror %^CRST%^does not show you, but instead shows a view of a %^C059%^dark inn%^CRST%^. If you were to %^C190%^>gaze<%^CRST%^ into the mirror you might see more clearly.\n");
set_long(::query_long()+"\n%^C195%^Domintating one wall is a massive mirror%^CRST%^.\n");

}

void init() {
    ::init();
    add_action("gaze_fun", "gaze");

}


void gaze_fun(){
    if(TP->query_blind() || TP->query_blindfolded() || TP->query_unconscious()){
        write("You cannot do that in your current state!");
        return 1;
    }
    tell_object(TP, "%^BOLD%^%^BLACK%^\nYou gaze deeply into the mirror... \n\n%^RESET%^");
    long_look_room(find_object_or_load("/d/darkwood/room/rhapsody.c"));
    return 1;
}

int long_look_room(object dest){
    object *inv;
    int i,j;
    message("room_description","\n%^RESET%^%^CRST%^"+(string)dest->query_long()+"", TP);
    inv = all_inventory(dest);
    if(sizeof(inv)< 1) return 1;
    for(i=0;i<sizeof(inv);i++){
     	if(!objectp(inv[i])) continue;
     	if(inv[i]->query_invis()) continue;
    	if(!inv[i]->is_detectable()) continue;
    	TO->send_living_name(inv[i]);
    }
    return 1;
}

int send_living_name(object targ){
	string known, str;
	int i,j;

    if(targ->is_monster()){
	    str = targ->query_short();
	    message("living_item", "%^RESET%^%^CRST%^"+str,TP);
        return 1;
    }
    if(objectp(TP) && TP->knownAs(targ->query_true_name())){
	    known = TP->knownAs(targ->query_true_name());
    }
    str = targ->getWholeDescriptivePhrase();
    if(known){
        str = capitalize(known)+", "+str;
    }
    if(str){
        message("living_item", "%^RESET%^%^CRST%^"+str, TP);
    }
    known = 0;
    return 1;
}