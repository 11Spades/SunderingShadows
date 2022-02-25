


#include <std.h>
#include "../serakii.h"

inherit CROOM;



void create() {
    ::create();
    set_terrain(GRASSLANDS);
    set_travel(RUTTED_TRACK);
    set_property("indoors",0);
    set_name("hidden beach");
    set_short("%^C220%^h%^C222%^i%^C220%^dden "+
        "bea%^C223%^c%^C220%^h%^CRST%^");
    set_long("This %^C220%^beach%^CRST%^ is nestled in an almost "+
        "impossible formation to keep it hidden from the world. "+
        "On the east an almost %^C243%^sheer%^CRST%^ drop down "+
        "into a %^C028%^valley%^CRST%^ so no one could ever climb "+
        "up, and on the west, the cove has a %^C220%^deep sandbar%^CRST%^ "+
        "with %^C035%^thick foliage%^CRST%^. All in all unless you were "+
        "flying overhead you would never find this place. The "+
        "%^C220%^beach%^CRST%^ itself is formed of fine %^C221%^golden "+
        "sand%^CRST%^ that would be beautiful if it was not smeared "+
        "with %^C196%^blood%^CRST%^ and %^C094%^detritus%^CRST%^. "+
        "All around you are %^C244%^heavy stakes%^CRST%^ driven into "+
        "the %^C094%^ground%^CRST%^ either have a person %^C242%^chained%^CRST%^ "+
        "to it or previously did by the amount of %^C088%^caked blood%^CRST%^ "+
        "on the %^C244%^manacles%^CRST%^. %^C249%^Tins%^CRST%^ on the "+
        "ground must have held %^C058%^food%^CRST%^ or %^C111%^water%^CRST%^ "+
        "but most are empty.\n");
    set_items(([
        ({"beach","sand"}) : "The %^C220%^sand%^CRST%^ from the "+
        "%^C220%^beach%^CRST%^ was once beautiful %^C226%^golden%^CRST%^, "+
        "but now stained from the %^C088%^blood%^CRST%^ "+
        "and %^C094%^detritus%^CRST%^ .",
        ({"blood","detritus"}) : "The %^C124%^blood%^CRST%^ "+
        "and %^C094%^excrement%^CRST%^ of the people held here as "+
        "stained the %^C220%^beach%^CRST%^ and left a "+
        "%^C060%^stink%^CRST%^ across it even the %^C111%^surf%^CRST%^ "+
        "cant hide.",
        ({"manacles","tins"}) : "%^C243%^Manacles%^CRST%^ are tied "+
        "to %^C060%^heavy stakes%^CRST%^ and %^C250%^tins%^CRST%^ lay "+
        "around the ground, empty now.",

    ]));

set_smell("default","%^C243%^You smell human misery and sand.%^CRST%^");
set_listen("default","%^C111%^The surf crashes against the beach%^CRST%^.");

}


void pick_critters(){
   switch(random(6)){
         case 0:   set_monsters(
({MOBS"hound_heavy",MOBS"attack_dog"}),({random(4),random(2)}) );
                   break;
         case 1:   set_monsters(
({MOBS"hound_heavy"}),({random(6)}) );
                   break;
         case 2:   set_monsters(
({MOBS"hound_heavy",MOBS"archer"}),({1,random(1)+3}) );
                   break;
         case 3:   set_monsters(
({MOBS"archer"}),({random(5)}) );
                   break;
         case 4..5: set_monsters(
({MOBS"hound_heavy",MOBS"attack_dog"}),({random(4),random(2)}) );
                   break;
   }
}
