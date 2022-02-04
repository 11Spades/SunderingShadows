#include <std.h>
#include "../../serakii.h"

inherit CVAULT;

void pick_critters();


void create() {
    ::create();
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("light",2);
    set_property("indoors",1);
    set_name("grand foyer");
    set_short("grand foyer");
    set_long("This %^C248%^massive foyer%^CRST%^ "+
        "is breathtaking in its size and architecture. "+
        "The ceiling above you must be %^C111%^five "+
        "hundred feet%^CRST%^ and %^C248%^grand pillars%^CRST%^ "+
        "support several different floors. A %^C221%^g%^C227%^"+
        "i%^C221%^ant c%^C226%^r%^C221%^yst%^C226%^a%^C221%^l "+
        "c%^C226%^h%^C221%^andel%^C227%^i%^C221%^er%^CRST%^ "+
        "hangs from %^C245%^chains%^CRST%^ suspended from "+
        "chains hung at different levels that %^C226%^lights%^CRST%^ "+
        "up the %^C248%^foyer%^CRST%^. People in %^C061%^fi%^C063%^"+
        "n%^C061%^e r%^C063%^o%^C061%^bes%^CRST%^ wander the %^C248%^"+
        "foyer%^CRST%^ and congregate in clumps. %^C044%^Soft "+
        "music%^CRST%^ %^RESET%^flows around you and the sounds of conversation "+
        "fill the room. The floor is formed of interlocking %^C231%^"+
        "marble slabs%^CRST%^ forming a geometric pattern. %^C248%^"+
        "Archways%^CRST%^ lead both to the east and west and a %^C059%^"+
        "giant staircase%^CRST%^ on the north leads down..\n");

    set_items(([
      ({"ceiling"}) : "The ceiling is so far above you it is hard to "+
      "fathom exactly how high. There is a glass dome far above "+
      "you letting in light.\n",
      ({"floor"}) : "The floor is %^C247%^marble%^CRST%^, with "+
      "interlocking slabs forming a %^C250%^geometric "+
      "pattern%^CRST%^. With how large it is, its hard to tell "+
      "what the pattern is from here.\n",
      ({"chandelier"}) : " This %^C227%^massive crystal "+
      "chandelier%^CRST%^ would weigh several %^C060%^tonnes%^CRST%^ "+
      "and is suspended by at least%^C244%^ ten chains%^CRST%^ "+
      "at different levels of the building above you.\n",
      ({"archway","archways"}) : "Archways stand on both the east "+
      "and west walls. There is a %^C248%^heavy carved script%^CRST%^ "+
      "in both of them you could read.\n",
      ({"stairs","stairwell"}) : "%^C059%^Wide stairs%^CRST%^ lead "+
      "into the %^C247%^lower levels%^CRST%^ of the fortress city.\n",
    ]));

    set_smell("default","%^C028%^You smell fresh cut flowers.%^CRST%^");
    set_listen("default","%^C111%^The sounds of conversations float through the foyer.%^CRST%^");

    set_exits(([

       "stairs" : CAER"library",
        "east" : CAER"1",
        "west" : CAER"2",
        "gate" : RUINS"6",

    ]));

    set_door("heavy gate",RUINS"6","gate",0);
    set_door_description("heavy gate","%^C094%^Formed from solid "+
        "wood, this door looks very"+
" heavy. An %^C244%^iron ring %^C094%^hangs from it to allow it "+
"to be opened.%^CRST%^");
    set_string("heavy gate", "open", "%^C060%^It takes all your "+
        "strength to open the door.%^CRST%^");
    set_string("heavy gate", "close", "%^C060%^You push the door "+

        "with all your weight to close it.%^CRST%^");


      set_post_exit_functions(({"stairs"}),({"GoThroughDoor"}));

}


void init(){
    ::init();
    add_action("func_read", "read");

}


int func_read(string str){

    if(!str) {
        return 0;
    }
    if(str == "archway"){
        tell_object(TP,"%^C247%^There are two archways? Do you want to "+
            "read the %^C045%^eastern archway%^C247%^ or "+
            "the %^C045%^western archway%^C247%^?%^CRST%^\n");
        return 1;
    }
    if(str == "eastern archway"){
        tell_room(ETP,"%^C098%^"+TPQCN+" %^C098%^looks up to read "+
            "the eastern archway...%^CRST%^\n",TP);
        tell_object(TP,"%^C098%^You look up at the writing on the "+
            "eastern archway.\n\n %^C110%^Conclave of the Grand Companies "+
            "of Serakii%^C098%^.%^RESET%^\n");
        return 1;
    }
    if(str == "western archway"){
        tell_room(ETP,"%^C098%^"+TPQCN+" %^C098%^looks up to read the "+
            "western archway...%^CRST%^\n",TP);
        tell_object(TP,"%^C098%^You look up at the writing on the "+
            "eastern archway.\n\n %^C110%^Bastion of the Voice of "+
            "Serakii%^C098%^.%^RESET%^\n");
        return 1;
    }




}

int GoThroughDoor(){
   tell_object(TP,"%^C041%^Walking down the stairs you suddenly "+
   "feel the whole of reality shift as you are transported to "+
   "another plane of existence.%^CRST%^");
   return 1;
}


void reset()
{
    ::reset();
    if(!present("mercenary"))
    {
      new(MOBS"caermerc.c")->move(TO);
    }
}
