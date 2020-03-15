//created by Styx 5/19/01 from Shadow warhammer.c for Newbietown to cover off size profs

inherit "/std/weapon";

create() {
    ::create();
   set_id(({ "small hammer","hammer" }));
   set_name("hammer");
   set_short("A small hammer");
   set_long(
  "This is a small but sturdy looking hammer.  It has a flattened head on one side, counterbalanced on the other by a conical but blunt spike.  It's small enough for even little people to wield in one hand."
   );
   set_weight(4);
   set_size(1);
   set("value", 2);
   set_wc(1,4);
   set_large_wc(1,4);
   set_type("bludgeon");
  set_prof_type("small hammer");
   set_weapon_speed(3);
}
