// Chernobog (4/18/22)
// First Mate of the Zephyr

#include <std.h>
#include <daemons.h>
#include "../defs.h"
inherit MONSTER;

int powerlevel;

void create(){
    ::create();
    set_name("first mate");
    set_id(({ "sailor", "first mate of the zephyr", "first mate of the Zephyr", "mate", "first mate" }));
    set_short("%^RESET%^%^CRST%^%^C038%^first mate %^C101%^of the %^C144%^Z%^C101%^ephyr%^CRST%^");
    set_long("%^CRST%^%^RESET%^%^C038%^This is the first mate of the %^C144%^Z%^C101%^ephyr%^C038%^, a merchant vessel, left aboard to guard the ship from %^C109%^trespassers%^C038%^ like you. She is trusted by her captain, with access to the whole of the ship.%^CRST%^\n");
    set_race("human");
    set_gender("female");
    set_alignment(5);
    set_base_damage_type("bludgeoning");
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", 25);
    set_damage(3, 5);
    set_attacks_num(4);
    set_overall_ac(-20);
    set_max_hp(400);
    set_hp(query_max_hp());
    set_new_exp(25, "low");
    set_property("full attacks",1);
    set_monster_feats(({
        "parry",
        "weapon focus",
        "weapon training", }));
    set_skill("athletics", 30);
    set_skill("perception", 30);
    get_gear();
}

void get_gear(){
    object mate, gear;
    mate = this_object();
    
    switch(random(2)){
        case 0 :
            gear = new("/d/common/obj/weapon/longsword");
            gear->set_property("monsterweapon", 1);
            gear->move(mate);
            force_me("wield sword");
            break;
        case 1 :
            gear = new("/d/common/obj/weapon/dagger");
            gear->set_property("monsterweapon", 1);
            gear->move(mate);
            force_me("wield dagger");
            gear = new("/d/common/obj/weapon/dagger");
            gear->set_property("monsterweapon", 1);
            gear->move(mate);
            force_me("wield dagger");
            break;
    }
    gear = new(OBJ"zephyr_key");
    gear->move(mate);
}

