
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([

    "east" : FOR"44",
    "south" : FOR"42",
    "north" : FOR"46",

]));

}

