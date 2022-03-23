inherit "/std/food.c";

#include <std.h>

void create(){
   ::create();
   set_name("pretzel");
   set_id(({"stroopwaffel","waffle","food"}));
   set_strength(20);
   set_weight(1);
   set_value(20);
   set_short("%^C130%^gooey stroopwaffel%^CRST%^");
   set_destroy();
   set_long("This %^C142%^golden%^CRST%^, saucer-sized %^C136%^waffle cookie%^CRST%^ is still warm from the griddle. Despite its wafer-thinness it has somehow been delicately sliced open to sandwich a layer of %^C094%^gooey caramel%^CRST%^ between the two crispy halves.");
   set_my_mess("You try to eat the %^C136%^stroopwaffel%^CRST%^ carefully, enjoying the %^C094%^gooey caramel%^CRST%^.");
   set_your_mess("eats the %^C094%^gooey caramel%^CRST%^ filled %^C136%^stroopwaffel%^CRST%^.");
  }
