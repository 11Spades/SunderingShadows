
#include <std.h>
#include "../../serakii.h"

inherit ROOM;

void create() {
    ::create();
    set_light(2);
    set_indoors(1);
    set_terrain(WOOD_BUILDING);
    set_travel(DIRT_ROAD);
    set_short("Cramped Incense Store");
    set_long("This %^C064%^shop %^CRST%^is "+
	"an insane chaotic mass of a thousand "+
	"%^C058%^jugs %^CRST%^and %^C247%^"+
	"jars %^CRST%^and piles of %^C142%^"+
	"ground herbs%^CRST%^. The room itself "+
	"has obviously not been cleaned "+
	"properly and it would take a %^C133%^"+
	"master %^CRST%^to just understand what "+
	"is what and where. The room is %^C246%^"+
	"dark %^CRST%^due to its cramped nature "+
	"but enough that you can carefully "+
	"navigate through. There is a %^C242%^"+
	"single lantern%^CRST%^ hanging from "+
	"the ceiling. Behind a %^C058%^cramped "+
	"counter%^CRST%^ is an %^C064%^"+
	"elderly %^CRST%^woman.\n");
    set_exits(([

           "south" : TOWN"5",
	]));

     set_items(([
       "shelves":" ."
     ] ));
    if(!present("kreekee"))
    {
      new(MOBS"kreekee.c")->move(TO);
    }
}

void reset()
{
    ::reset();
    if(!present("kreekee"))
    {
      new(MOBS"kreekee.c")->move(TO);
    }
}
