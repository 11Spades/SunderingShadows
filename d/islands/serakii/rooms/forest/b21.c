#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"south" : FOR"b19",
"southeast" : FOR"b20",
"east" : FOR"b22",


]));

}
