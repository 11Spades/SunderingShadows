#include <std.h>

inherit ROOM;

void create()
{
   ::create();
   set_long("This is a storage room no one should be in ");
   set_short("Storage room");
   set_had_players(3);
}

void reset(){
   int i;
   int j;
   ::reset();
   j = roll_dice(1,20);
   for(i=0;i<j;i++)
   {
      if (!present("cloth "+i)) {
         new("/std/obj/cloth")->move(TO);
      }
   }
}

