#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
"north" : FOR"1",
"east" : FOR"35",
"south" : FOR"23",
"west" : FOR"10",

]));

}
