#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"south" : FOR"b11",
"west" : FOR"b12",
"northeast" : FOR"b14",

]));

}
