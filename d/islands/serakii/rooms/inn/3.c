#include <std.h>
#include "../../serakii.h"

inherit STORAGE"outside_inn.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C029%^The ground here, unlike all of the other parts of the area around the inn is %^C243%^blasted %^C029%^and %^C124%^wrecked %^C029%^as if some spell of %^C062%^massive power%^C029%^ was let loose here. %^CRST%^\n");


set_exits(([

"west" : INN"2",


]));

}
