#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();

set_exits(([
"east" : HOUND"7",
"north" : HOUND"8",
"west" : HOUND"4",

]));

}
