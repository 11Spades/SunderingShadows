#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"northwest" : FOR"b11",
"southwest" : FOR"b8",
"northeast" : FOR"b16",

]));

}
