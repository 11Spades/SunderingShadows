#include "summoned_monster.h"

inherit MONSTER;

void create() {
    ::create();
    set_name("ogre warrior");
    set_id( ({"ogre", "ogre warrior", "warrior", "Ogre Warrior", "cavemon"}) );
    set_short("Ogre warrior");
    set_long(
      "This is a large and ugly ogre warrior.  He is hefting what looks like a "
      "large sword on his shoulder.  As you look into his eyes you see a deep "
      "hatred, a hatred for all life."
    );
    set_gender("male");
    set("race", "ogre");
    set_body_type("human");
    set_overall_ac(5);
    set_property("swarm",1);
    set_class("fighter");
    set_mlevel("fighter", 9);
    set_hd(9,7);
    set_attack_bonus(2);
    set_exp(1250);
    set_stats("strength", 18);
    set_stats("dexterity", 8);
    set_stats("constitution", 18);
    set_stats("intelligence", 3);
    set_stats("wisdom", 5);
    set_stats("charisma", 3);
    set("aggressive", 20);
    set_alignment(9);
    set_size(3);
    set_max_hp(115);
    set_hp(115);
    set_property("full attacks", 1);
    add_money("gold", random(25));
    new(WEAPONDIR+"two_hand_sword.c")->move(TO);
    command("wield club");
}
