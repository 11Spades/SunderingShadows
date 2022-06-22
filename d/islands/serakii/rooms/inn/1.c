#include <std.h>
#include "../../serakii.h"

inherit STORAGE"outside_inn.c";



void create(){

object ob;
   ::create();
   set_long(::query_long()+"\n%^C094%^The door to the inn stands before you.%^CRST%^\n");


set_exits(([
"inn" : INN"inn",
"northeast" : INN"2",
"southwest" : ROAD"1",

]));

    set_door("door",INN"inn","inn",0);

ob = new("/std/bboard");
ob->set_name("board");
ob->set_id( ({ "board", "bulletin board" }) );
ob->set_board_id("serakii_board");
ob->set_short("Arcane Bulletin Board");
ob->set_long("This woooden board stands by the inn allow "+
    "businesses to advertise and citizens and adventurers"+
    "to communicate about events.");
ob->set_max_posts(50);
ob->set_location("/d/islands/serakii/rooms/inn/1.c");

}
