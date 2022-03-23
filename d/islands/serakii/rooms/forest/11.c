
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
    "north" : FOR"12",
    "east" : FOR"10",
    "south" : FOR"21",

]));
  add_item("statue","%^C060%^You look over the massive statue in front of you.. \n\n  You are on the left of the statue and you see that the figure has a footman's mace in their left hand. While the statue is immeasurably old, the forest seems unwilling to grow over it and it seems new as the day it was carved.\n%^CRST%^");
  
  
     set_long(::query_long()+"\n%^C243%^%^C060%^A massive statue rises from the forest here... \n%^CRST%^");

}

