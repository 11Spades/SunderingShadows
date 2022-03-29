#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();


set_exits(([
"northwest" : BONE"4",
"up" : BONE"6",

]));

add_item("staircase","%^C240%^This staircase, made of %^C244%^wrought iron%^C240%^ is an absolute work of art. The balusters are made to look like %^C248%^old columns%^C240%^ with %^C064%^ivy %^C240%^crawling along them and even %^C124%^small birds%^C240%^ made of precious %^C160%^gems %^C240%^are placed around it.%^CRST%^");
   set_long(::query_long()+"\n%^C239%^A beautifully wrought iron staircase is here.%^CRST%^\n");
}
