#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

set_long(::query_long()+"\n%^C244%^A %^C094%^massive table%^C244%^ dominates this room. To the west is a door, to the east is stairs going up and to the south an arsenal of %^C241%^war machines%^C244%^ are poised for action. It is %^C045%^colder %^C244%^here as there seem to be openings to the %^C063%^outside %^C244%^on this floor.\n%^CRST%^");

set_exits(([
"north" : WHITE"24",
"west" : WHITE"room3",
"east" : WHITE"27",
"southwest" : WHITE"28",
"south" : WHITE"29",
"southeast" : WHITE"30",





]));

    set_door("wooden door",WHITE"room3","west",0);
    set_door_description("wooden door","%^C094%^Formed from solid wood, this door looks very"+
" heavy. An %^C243%^iron ring%^C094%^ hands from it to allow it to be opened.");
    set_string("wooden door", "open", "%^C094%^You push against the heavy door and it opens slowly.%^CRST%^");
    set_string("wooden door", "close", "%^C094%^You close the heavy wooden door slowly%^RESET%^%^BOLD%^.");

add_item("table", "%^C094%^This table is heavy oak and higher than what you would expect, as if it was designed for meetings where everyone was standing.%^CRST%^\n");

}
