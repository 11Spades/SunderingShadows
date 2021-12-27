// Metals Vendor for Port Serith Institute

#include <std.h>
#include "../../serakii.h"

inherit ROOM;

void create() {
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",1);

    set_name("metals shop");
    set_property("light",2);
    set_short("metals shop");
    set_long("Tucked against the %^C248%^southern wall%^CRST%^ of "+
    "the building, a %^C094%^long oak table%^CRST%^ is set up in "+
    "front of %^C253%^heaps%^CRST%^ upon %^C252%^heaps%^CRST%^ "+
    "of %^C222%^billets%^CRST%^ of %^C243%^metal%^CRST%^, all "+
    "stacked neatly. A large scale sits on the table and a "+
    "ledger lays open. There are %^C094%^crates%^CRST%^ "+
    "stacked up as well, ready for unpacking. A %^C124%^small "+
    "red rug%^CRST%^ covers the %^C248%^simple flagstone "+
    "floor%^CRST%^ and on the wall is a %^C028%^painting%^CRST%^.\n");

    set_items(([
        ({"table"}) : "%^C094%^The table is almost ten feet long "+
        "and varnished to a deep shine. A large scale for "+
        "measuring billets and an open ledger lay on it.\n%^CRST%^",
        ({"painting"}) : "%^C060%^This oil painting is of a "+
        "%^C094%^galleon%^C060%^ in a %^C068%^heavy storm%^C060%^. "+
        "The painter has been able to capture the %^C245%^violence%^C060%^ "+
        "of the %^C027%^raging waves%^C060%^ and %^C241%^clouds%^C060%^ "+
        "but still allow the galleon, breaching the top of a %^C057%^wave%^C060%^, "+
        "to look %^C142%^stronger%^C060%^. It is framed in a %^C094%^heavy "+
        "oak frame%^C060%^ and would take several men to move.\n%^CRST%^",
        ({"scale"}) : "%^C242%^This heavy scale is used for "+
        "measuring billets. On one side of the scale "+
        "standardized weights are placed, tipping the arm. "+
        "Once the billet and the weights are equal, the "+
        "user of the scale will know how many units "+
        "they have.\n%^CRST%^.",
        ({"rug"}) : "%^C088%^This simple red rug its "+
        "in front of the table and allows for some "+
        "measure of elegance to the bare flagstone floor.%^CRST%^\n",
({"floor","flagstone"}) : "%^C243%^The floor here is simple flagstone%^CRST%^",
({"billets","crates"}) : "%^C060%^Piles of billets of "+
"different metals sit piled behind the table. Crates are "+
"also neatly stacked. %^CRST%^",
    ]));


set_smell("default","%^C094%^you smell the wood of the crates and the varnish of the table%^CRST%^.");
set_listen("default","%^C241%^you hear the busy %^C124%^forge%^C241%^ to the west%^CRST%^.");


   set_exits(([
          "north" : TOWN"garden",
          "northeast" : TOWN"fabric_vendor",
          "northwest" : TOWN"herb_vendor",
          "east" : TOWN"goldsmith_shop",
          "west" : TOWN"forge",
          
   ]));

}

void reset()
{
    ::reset();
    if(!present("trader"))
    {
      new(MOBS"oennan.c")->move(TO);
    }
}
