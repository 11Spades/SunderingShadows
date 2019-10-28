//pbat.c

#include <std.h>

inherit WEAPONLESS;

void create(){
   ::create();

   set_name("vampire bat");
   set_short("%^RESET%^%^RED%^A bat");
   set_long("%^RESET%^%^RED%^This is a bat, flying creature with sharp fangs and glowing red eyes.");
   set_id(({"bat","vampire bat"}));
   set("not living",1);

   set_long(
@OLI
   %^CYAN%^This is a large bat
OLI
   );
   set_race("bat");
   set_gender("male");
    set_property("no animate",1);
   set_body_type("fowl");
   set_hd(10,1);
   set_stats("strength",10);
   set_hp(45);
   set_attack_bonus(3);
   set_weight(10000);
   set_attack_limbs(({"mouth"}));
   set_attacks_num(1);
   set_damage(2,4);
   set_damage_bonus(3);
   set_size(1);
   set_overall_ac(7);
   set("magic",1);
}

void die(object ob){
   tell_room(ETO,"%^RED%^The bat turns into dark mist.");
   remove();
   return;
}
