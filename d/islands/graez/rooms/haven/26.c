
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_name("inside a small building");
   set_short("%^C058%^inside a small %^C244%^desolate%^C058%^ building%^CRST%^");
   
   set_property("indoors",1);
   set_long(::query_long()+"\nThis %^C060%^building%^CRST%^ looks to be a %^C244%^barracks%^CRST%^ of sort where people can sleep while %^C059%^proper homes%^CRST%^ are being constructed. %^C186%^Cots%^CRST%^ are piled up in the corner and %^C222%^bedding%^CRST%^ is strewn about.\n");


set_exits(([
"north" : HAVEN"11",
"east" : HAVEN"12",
"southwest" : HAVEN"27",

]));

}

