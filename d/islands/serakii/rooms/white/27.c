#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

set_long("%^C246%^This room is smaller than the rest of the castle. Its walls are still the huge %^C255%^white stone%^C246%^ and the same %^C063%^carpet %^C246%^is laid here but it is obvious you are getting closer to the top of the %^C255%^tower %^C246%^and there is less room for stairs.\n%^CRST%^");

set_long(::query_long()+"\n%^C247%^Stairs here lead to the top of the tower.%^CRST%^\n");

set_exits(([
"west" : WHITE"25",
"up" : WHITE"top",

]));


}
