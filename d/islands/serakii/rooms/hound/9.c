#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();

set_exits(([
"north" : HOUND"11",
"west" : HOUND"7",

]));

}
