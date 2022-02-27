
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
    "east" : FOR"21",
    "west" : FOR"16",

]));
  add_item("statue","%^C060%^You look over the massive statue in front of you.. \n\n You are at the front of the statue and see a soldier dressed in armor and wielding weapon and shield. While the statue is immeasurably old, the forest seems unwilling to grow over it and it seems new as the day it was carved. At the base of the statue is the simple word 'Agrath'\n%^CRST%^");
  
  
     set_long(::query_long()+"\n%^C243%^%^C060%^A massive statue rises from the forest here... \n%^CRST%^");

}

