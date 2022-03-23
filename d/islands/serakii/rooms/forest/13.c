
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
    "east" : FOR"12",
    "west" : FOR"14",
    "north" : FOR"17",

]));
  add_item("statue","%^C060%^You look over the massive statue in front of you.. \n\nYou are at the back of the statue and you see that the figure has long hair that hangs back over their shoulders. They have a quiver on their back. While the statue is immeasurably old, the forest seems unwilling to grow over it and it seems new as the day it was carved.\n%^CRST%^");
  
  
     set_long(::query_long()+"\n%^C243%^%^C060%^A massive statue rises from the forest here... \n%^CRST%^");

}

