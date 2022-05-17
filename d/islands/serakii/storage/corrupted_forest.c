
//Forest of Tears - Deeper - LoKi

#include <std.h>
#include "../serakii.h"

inherit CROOM;



void create() {
    ::create();
	pick_critters();
    set_repop(60);
    set_terrain(GRASSLANDS);
    set_travel(RUTTED_TRACK);
    set_property("indoors",0);
    set_property("no teleport",1);
    set_property("no scry",1);
    set_name("corrupted forest");
    set_short("%^C058%^co%^C059%^r%^C058%^ru%^C059%^"+
	"p%^C058%^t%^C022%^e%^C058%^d f%^C022%^o%^C059%^"+
	"r%^C058%^e%^C022%^s%^C058%^t%^CRST%^");
    set_long("This %^C022%^forest %^CRST%^is a strange "+
	"thing, and to call it a %^C022%^forest%^CRST%^ "+
	"at all anymore is a stretch. %^C022%^Immense "+
	"trees%^CRST%^ grow around you, each %^C094%^"+
	"trunk %^CRST%^two meters across, but instead "+
	"of proper %^C094%^branches%^CRST%^, the %^C058%^"+
	"bark %^CRST%^is split and %^C061%^writhing "+
	"tentacles%^CRST%^ emerge and flap about limply. "+
	"As you look up the %^C062%^tentacles %^CRST%^grow "+
	"together, blocking out the sky completely as a "+
	"nest of interlocking %^C062%^strange flesh%^CRST%^. "+
	"The %^C058%^ground %^CRST%^here feels mushy but "+
	"you cannot see it through a %^C056%^thick purple "+
	"miasma%^CRST%^ that rises thick over the %^C059%^"+
	"ground %^CRST%^at a foot height. You hear %^C244%^"+
	"strange chanting%^CRST%^ though it is hard to tell "+
	"if it comes from the %^C022%^trees%^CRST%^, or from "+
	"something under the %^C062%^miasma%^CRST%^. The "+
	"air itself feels almost %^C081%^wet %^CRST%^as you "+
	"breathe.\n");
    set_items(([
        ({"trees","trunks","tentacles"}) : "The %^C022%^"+
		"trees %^CRST%^here grow tall and strong in an "+
		"initial look though where %^C058%^branches%^CRST%^ "+
		"are supposed to be are instead %^C062%^fleshy "+
		"tentacles%^CRST%^ dangle and move limply.",
        ({"sky","canopy"}) : "The %^C087%^sky %^CRST%^is "+
		"completely obscured by the %^C062%^intertwined "+
		"tentacles%^CRST%^ above you.",
        ({"ground","mist","miasma"}) : "The %^C059%^"+
		"ground %^CRST%^is covered by a thick foot deep "+
		"layer of %^C056%^miasma %^CRST%^that smells "+
		"like %^C194%^ozone%^CRST%^.",
    ]));

set_smell("default","You smell ozone.");
set_listen("default","You hear strange chanting all around you.");


}

query_weather() { return "The air around you is %^C081%^wet %^CRST%^like it just %^C068%^rained%^CRST%^.\n"; }

void init(){
   ::init();
   add_action("peer_fun","peer");
}

void peer_fun(string str){

    int damroll;
    string* my_visions = ({ "%^C060%^A ravaged %^C058%^corpse%^CRST%^", "%^C059%^A pile of %^C066%^dead%^C059%^ children%^CRST%^", 
        "%^C220%^A %^C228%^man%^C220%^ trapped in amber%^CRST%^","%^C065%^An %^C067%^ogre-mage%^C065%^ dripping in miasma%^CRST%^", 
        "%^C055%^A mangled %^C060%^demon%^CRST%^", "%^C240%^A black %^C245%^gate%^CRST%^" });
    string my_vision;

    if(!random(2)){return 0;}
    damroll = roll_dice(10, 10) + 10;
    this_player()->add_hp(-damroll);
    my_vision = my_visions[random(sizeof(my_visions))];
    tell_object(this_player(), "%^C088%^You feel a sharp pain in your head and suddenly your "+
        "vision is filled with a vivid image of a " + my_vision + "%^C088%^! The pain hits "+
        "the back of your head as the vision swims, and then it is gone again.\n%^CRST%^");
    tell_object(this_environment(), "%^C088%^With a frown " + this_player() + "%^C088%^ squeezes "+
        "their eyes shut!%^CRST%^\n",this_player());
    return 1;

}

void pick_critters(){
   switch(random(5)){
         case 0:   set_monsters(
({MOBS"gibling",MOBS"minor_abom"}),({random(2),random(3)}) );
                   break;
         case 1:   set_monsters(
({MOBS"gibling"}),({random(5)}) );
                   break;
         case 2:   set_monsters(
({MOBS"gibling"}),({random(2)+2}) );
                   break;
         case 3..4: break;
   }
}
