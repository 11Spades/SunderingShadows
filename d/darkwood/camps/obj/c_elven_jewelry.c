#include <std.h>
inherit ARMOUR;

void create(){
   ::create();
   "/d/darkwood/camps/obj/elven_jewelry.c"->create_jewelry(TO);
}

int query_size(){
   if(!objectp(ETO)) return 2;
   return ETO->query_size();
}
