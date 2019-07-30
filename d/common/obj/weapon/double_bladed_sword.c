#include <std.h>
inherit "/std/weapon";
void create() {
   ::create();
   set_id(({"sword", "double bladed sword"}));
   set_name("double bladed sword");
   set_short("double bladed sword");
   set_long(
      "This sword consist of steel and wood. The shaft of the weapon is crafted"+
      " in a fashion similar to a thick staff. Set on both sides of the staff are"+
      " long blades so that the wielder can use either side of the weapon"+
      " to attack, giving weapon much versatility in combat."
   );
   set_weight(15);
   set_size(3);
   set_value(50);
   set_wc(2,8); //putting this a die higher than TT to reflect that we lack tech to make it usable as two weapons without needing ambidexterity
    set_type("thiefslashing");
   set_large_wc(2,8); //putting this a die higher than TT to reflect that we lack tech to make it usable as two weapons without needing ambidexterity
   set_weapon_prof("exotic");
   set_weapon_speed(10);

   set_critical_threat_range(2);
   set_critical_hit_multiplier(2);
   set_damage_type("slashing");
}
