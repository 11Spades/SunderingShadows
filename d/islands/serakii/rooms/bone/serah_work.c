// Serah Office

#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_atrium.c";

void create() {
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",1);

    set_name("cluttered workroom");
    set_property("light",2);
    set_short("%^C058%^cluttered workroom%^CRST%^");
    set_long("While the rest of the tower is %^C195%^pure%^CRST%^ and %^C193%^clean%^CRST%^ "+
        "and %^C195%^stark%^CRST%^ in its furnishings, this room is %^C058%^cluttered%^CRST%^ "+
        "with a thousand different %^C245%^mechanical parts%^CRST%^ and %^C062%^spell reagents%^CRST%^. "+
        "The floors are covered in %^C238%^soot%^CRST%^ and %^C059%^oil spills%^CRST%^ and "+
        "the %^C058%^work benches%^CRST%^ that dominate the walls are covered in %^C231%^vials%^CRST%^"+
        ", %^C152%^tubes%^CRST%^, and %^C058%^torn up books%^CRST%^. In one corner of the room is a "+
        "pile of %^C244%^half finished constructs%^CRST%^ and %^C059%^golems%^CRST%^. On the far side "+
        "is a %^C094%^cabinet%^CRST%^. There is a %^C094%^small bed%^CRST%^ near one wall but it is "+
        "evident it has not been used in some time. Overall the room has an %^C055%^oppressive%^CRST%^ feel.\n");

    set_items(([
      ({"floor"}) : "The once %^C195%^pristine floor%^CRST%^ is covered in %^C238%^soot%^CRST%^ "+
      "and %^C059%^oil stains%^CRST%^ that have not been cleaned up.\n",
      ({"pile","unfinished constructs"}) : "In the corner is a pile of %^C242%^unfinished "+
      "constructs%^CRST%^ and %^C058%^golems%^CRST%^. Some of them are %^C248%^quite "+
      "rudimentary%^CRST%^ and %^C244%^dusty%^CRST%^ as if they have spent years in "+
      "the %^C242%^pile%^CRST%^. Others, are fresh and new but discarded all the same.\n",

      ({"workbench","workbenches"}) : "The %^C094%^workbenches%^CRST%^ are piled high "+
      "with %^C059%^detrius%^CRST%^. %^C142%^Torn up books%^CRST%^, %^C195%^vials%^CRST%^, "+
      "%^C067%^magical reagents%^CRST%^. There is no way there is a system or organization "+
      "to any of this.\n",
      ({"bed"}) : "This %^C094%^simple bed%^CRST%^ is small and covered in a %^C074%^threadbare "+
      "blanket%^CRST%^. The %^C245%^layer of dust%^CRST%^ on it shows that it hasn't been used "+
      "in weeks, perhaps months.\n",
    ]));


set_smell("default","%^C130%^You smell oil and soot.%^CRST%^");
set_listen("default","%^C141%^The room is silent except what noise you make%^CRST%^");


   set_exits(([
        "south" : BONE"18",

   ]));
               set_door("simple door",BONE"18","south",0);
}

void reset()
{
        ::reset();
        if(!present("serah"))
        {
new(MOBS"serah")->move(TO);

        }
}
