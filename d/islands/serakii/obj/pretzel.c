inherit "/std/food.c";

#include <std.h>

void create(){
   ::create();
   set_name("pretzel");
   set_id(({"pretzel","soft pretzel","food"}));
   set_strength(10);
   set_value(10);
   set_weight(10);
   set_short("%^C130%^soft pretzel%^CRST%^");
   set_destroy();
   set_long("This twist of %^C143%^dough%^CRST%^ has been boiled and dusted with thick %^C255%^chunks of sea salt%^CRST%^ to make a delicious treat. Before %^C245%^boiling %^CRST%^the dough is coated in %^C143%^lye %^CRST%^making the outer crust of the finished pretzel a %^C058%^deep mahogany%^CRST%^.");
   set_my_mess("You tear apart the %^C094%^pretzel %^CRST%^slowly, savoring each piece of it.");
   set_your_mess("eats the %^C094%^pretzel%^CRST%^, bits of %^C255%^salt %^CRST%^falling as they tear it apart.");
  }
