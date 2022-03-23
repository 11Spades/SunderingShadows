
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
    "north" : FOR"14",
    "south" : FOR"16",

]));
  add_item("statue","%^C060%^You look over the massive statue in front of you.. \n\n You are on the right of the statue and you see that the figure has a square towershield in their right hand. While the statue is immeasurably old, the forest seems unwilling to grow over it and it seems new as the day it was carved\n%^CRST%^");
  
  
     set_long(::query_long()+"\n%^C243%^%^C060%^A massive statue rises from the forest here... \n%^CRST%^");

}

