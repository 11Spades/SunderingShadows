inherit "/std/monster.c";

void create() {
  :: create();  
   set_name("wolf");
   set_id( ({ "wolf" }) );
  set_short("A wolf");
   set_level(1);
   set("long", "The wolf looks hungrily at you.\n");
   set_gender("male");
   set("race", "dog");
   set_body_type("dog");
  set_alignment(5);
   set_size(3);
   set_stats("intelligence",5);
   set_stats("wisdom",4);
   set_stats("strength",5);
   set_stats("charisma",3);
   set_stats("dexterity",7);
   set_stats("constitution",7);
   set_max_mp(3);
   set_hd(1,1);
set_max_hp(query_hp());
set_max_sp(query_hp());
set_sp(query_max_sp());
   set_max_hp(query_hp());
   set_mp(query_max_mp());
}

// Taming DCs: Low - 10, Mid - 25, High - 40, Epic - 55
// Types of DCs: "survival" for wild creatures (snakes, rats, stags, spiders, etc...)
//               "spellcraft" for magical creatures (elementals, sprites, will o wisp, etc...)
//               "dungeoneering" for constructs (clockwork creatures, golems, etc...)
int is_tamable(){ return 1; }
int query_tame_DC(){ return 25; }
string query_DC_type(){ return "survival"; }

