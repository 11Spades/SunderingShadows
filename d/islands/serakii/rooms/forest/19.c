
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
    "east" : FOR"18",

]));
  add_item("rock","%^C243%^a giant chunk of rock has landed here that blocks your way west%^CRST%^.");
  
  
     set_long(::query_long()+"\n%^C060%^The forest is blocked here from any travel west by a %^C240%^giant chunk %^C060%^of rock that has impacted here%^CRST%^\n");

}

