#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the southeast you can see the %^C240%^mountains %^CRST%^break and a %^C052%^sprawling battlefield%^CRST%^.\n");


set_exits(([
"southeast" : BATTLE"8",
"northwest" : MOUNT"2",

]));

}

