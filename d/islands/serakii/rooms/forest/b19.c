#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"west" : FOR"b18",
"north" : FOR"b21",
"east" : FOR"b20",

]));

}
