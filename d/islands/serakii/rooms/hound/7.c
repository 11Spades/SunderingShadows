#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();

set_exits(([
"east" : HOUND"9",
"north" : HOUND"10",
"west" : HOUND"5",

]));

}
