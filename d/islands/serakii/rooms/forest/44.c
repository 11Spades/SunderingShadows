
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([

    "west" : FOR"45",
    "south" : FOR"43",
    "north" : FOR"47",

]));

}

