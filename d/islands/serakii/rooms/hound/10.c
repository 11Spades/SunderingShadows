#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();

set_exits(([
"east" : HOUND"11",
"west" : HOUND"8",
"south" : HOUND"7",
"north" : HOUND"13",

]));

}
