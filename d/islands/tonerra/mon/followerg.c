//followerg

#include <std.h>

#include "/d/islands/tonerra/areadefs.h"

inherit MONSTER;

void create(){
   ::create();

   set_name("follower");
   set_short("Follower of Ibrandul");
   set_long(
@OLI
   This is a devoted follower of Ibrandul. Warrior priest,
raised by his parents to serve Ibrandul, even in his supposed
death.
OLI
   );
   set_class("cleric");
   set_race("human");
   set_class("fighter");
   set_hd(random(15)+20,9);
   set_body_type("human");
   set_mlevel("cleric",query_hd());
   set_mlevel("fighter",query_hd());
   set_spells(({"limb attack","flame strike"}));
   set_spell_chance(45);
   set_overall_ac(-14);
   set_hp(15*query_hd());
   set_exp(500*query_hd());
   set_new_exp(35,"very high");
   set_max_level(36);
   new(OBJ+"mace_of_ibrandul")->move(TO);
   command("wield mace");
   set_property("full attacks",1);
   set_property("magic resistance",20);
   set("aggressive",25);
}

int query_ibrandul(){return 1;}

