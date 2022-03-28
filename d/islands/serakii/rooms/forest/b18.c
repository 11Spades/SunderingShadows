#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"east" : FOR"b19",
"south" : FOR"b17",

]));

	add_item("bridge","%^C059%^A %^C242%^stone %^C059%^bridge crosses the %^C075%^stream %^C059%^here.%^CRST%^");
	add_item("stream","%^C075%^The %^C081%^water %^C075%^in the stream lazily passes you by. It is %^C004%^dark %^C075%^and %^C020%^deep %^C075%^and you are unsure if it is safe%^CRST%^.");

    set_long(::query_long()+"\n%^C065%^A %^C063%^stream %^C065%^cuts the %^C022%^forest %^C065%^here in half and a %^C130%^bridge %^C065%^is here to allow you to cross.%^CRST%^\n");


}
