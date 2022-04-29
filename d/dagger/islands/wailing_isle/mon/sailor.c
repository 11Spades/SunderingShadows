// Chernobog (4/18/22)
// Sailor Minion

#include <std.h>
#include <daemons.h>

inherit MONSTER;

int powerlevel;

void create(){
    object gear;
    
    ::create();
    set_name("sailor");
    set_id(({ "sailor", "sailor of the zephyr", "sailor of the Zephyr" }));
    set_short("%^RESET%^%^CRST%^%^C038%^sailor %^C101%^of the %^C144%^Z%^C101%^ephyr%^CRST%^");
    set_long("%^CRST%^%^RESET%^%^C038%^This is a sailor from the %^C144%^Z%^C101%^ephyr%^C038%^, a merchant vessel, left aboard to guard the ship from %^C109%^trespassers%^C038%^ like you.%^CRST%^\n");
    set_race("human");
    set_gender(random(2) ? "male" : "female");
    set_alignment(5);
    set_base_damage_type("bludgeoning");
    set_powerlevel(2);
    set_monster_feats(({
        "parry",
        "weapon focus",
        "weapon training", }));
    switch(random(2)){
        case 0 :
            gear = new("/d/common/obj/weapon/longsword");
            gear->set_property("monsterweapon", 1);
            gear->move(this_object());
            force_me("wield sword");
            break;
        case 1 :
            gear = new("/d/common/obj/weapon/dagger");
            gear->set_property("monsterweapon", 1);
            gear->move(this_object());
            force_me("wield dagger");
            gear = new("/d/common/obj/weapon/dagger");
            gear->set_property("monsterweapon", 1);
            gear->move(this_object());
            force_me("wield dagger");
            break;
    }
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 10));
    set_damage(powerlevel, 5);
    set_attacks_num(1);
    set_overall_ac(-(powerlevel * 8));
    set_max_hp(powerlevel * 120);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "very low");
    set_skill("athletics", (powerlevel * 11));
    return;
}

