#include "../../graez.h"
inherit ROOM;

object ob;

void create() {
    ::create();
    set_terrain(CITY);
    set_travel(PAVED_ROAD);
    set_property("light", 2);
    set_property("indoors", 01);
    set_name("busy city square");
    set_short("busy city square");
    set_long("Surrounded by the many %^C059%^buildings%^CRST%^ in the "+
        "western half of the city, this city square is bustling with "+
        "activity. %^C151%^Hawkers%^CRST%^ are set up to sell their "+
        "wares and the more well to do population browse from "+
        "%^C058%^shop%^CRST%^ to %^C058%^shop%^CRST%^ without a "+
        "care in the world. The %^C056%^nightmare%^CRST%^ that is "+
        "just minutes to the east seems to be a world away. You "+
        "notice as well that no %^C245%^soldiers%^CRST%^ patrol here, "+
        "only personal %^C059%^bodyguards%^CRST%^.\n");
    set_smell("default","%^C144%^You smell fresh %^C058%^baked "+
        "bread%^C144%^ and %^C082%^flowers%^C144%^ from the many stalls%^CRST%^");
    set_listen("default","%^C065%^The %^C059%^square%^C065%^ is alive with activity%^CRST%^");
    set_exits( ([
       "west" : TOWN"9",
    ]) );


        ob = new("/std/bboard");
        ob->set_name("board");
        ob->set_id( ({ "board", "bulletin board" }) );
       ob->set_board_id("graez_board");
        ob->set_short("Arcane Bulletin Board");
        ob->set_long("This woooden board stands in the middle of the square allow "+
            "businesses to advertise and citizens and adventurers"+
            "to communicate about events.");
        ob->set_max_posts(50);
               ob->set_location("/d/islands/graez/rooms/city/square.c");
}
void reset(){
   ::reset();
   if(!present("ambiance device")){
      new(MOBS"rich_ambiance.c")->move(TO);
   }
}

