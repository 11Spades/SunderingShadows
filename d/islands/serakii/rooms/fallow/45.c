
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();

   set_long(::query_long()+"%^C058%^\nA massive boulder blocks travel east.%^CRST%^\n");
set_exits(([

"northwest" : FALLOW"43",





]));

add_item("boulder", "%^C246%^This giant boulder is more like a chunk of mountain that has been set to block any passage east. It would be impossible for even a large dragon to move this without excessive force.%^CRST%^\n");

}

