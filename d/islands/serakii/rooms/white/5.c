#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

set_long(::query_long()+"\n%^C247%^You can see a room to the south that has stairs. There is also an arch leading north%^CRST%^\n");

set_exits(([
"southeast" : WHITE"4",
"southwest" : WHITE"6",
"gates" : RUINS"1",
"south" : WHITE"7",

]));


}
