#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();


set_exits(([
"south" : WHITE"13",
"northwest" : WHITE"9",


]));


}
