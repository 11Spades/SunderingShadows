// Chernobog (7/19/22)
// Wailing Isle - Kraken Tentacle

#include <std.h>
#include <daemons.h>
#include "../defs.h"

inherit MONSTER;

int powerlevel;
object controller;

void create(){
    ::create();
    set_name("tentacle");
    set_id(({"tentacle", "kraken tentacle"}));
    set_short("%^RESET%^%^CRST%^%^C106%^sm%^C107%^oo%^C108%^th %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C109%^A %^C106%^mot%^C107%^t%^C108%^le%^C107%^d %^C106%^gr%^C107%^e%^C108%^en%^C107%^i%^C106%^sh-%^C107%^b%^C108%^l%^C107%^u%^C106%^e %^RESET%^%^C109%^in color, this long slender tentacle rises up from the deep waters. It curls and sways with an alien intent, displaying a disturbing level of %^C110%^fl%^C111%^owi%^C110%^ng art%^C111%^iculat%^C110%^ion %^RESET%^%^C109%^as it explores.%^CRST%^\n");
    set_race("tentacle");
    set_body_type("snake");
    set_gender("neuter");
    set_size(3);
    set_alignment(9);
    add_limb("tentacle","torso",0,0,0);
    set_attack_limbs(({"tentacle"}));
    set_base_damage_type("bludgeoning");
    set_func_chance(33);
    set_funcs(({ "wrap_attack" }));
    set_property("no fear", 1);
    set_property("fear_immunity", 1);
    set_property("no bows", 1);
    set_property("no paralyze", 1);
    set_property("no_random_treasure", 1);
    set_property("hidden inventory", 1);
    set_property("darkvision", 1);
    set_property("swarm", 1);
    set_property("aggressive", 40);
    set_property("dance-of-cuts", 1);
    set_true_seeing(1);
    set_monster_feats(({
        "blind fight",
        "weapon training",
        "weapon focus",
        "greater weapon focus",
        "epic weapon focus",
        "combat_reflexes",
        }));
    set_resistance_percent("electricity", 100);
    set_powerlevel(5);
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 10));
    set_class("thief");
    set_mlevel("thief", (powerlevel * 10));
    set_damage((powerlevel * 5), 5);
    set_attacks_num(1);
    set_overall_ac(-(powerlevel * 10));
    set_max_hp(powerlevel * powerlevel * 100);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "high");
    set_skill("athletics", (powerlevel * 10));
    return;
}

void init(){
    object player;
    
    ::init();
    player = this_player();
    if(userp(player) && !avatarp(player)) force_me("kill "+player->query_name()+"");
}

void set_controller(object target){
    if(!objectp(target)) return;
    
    controller = target;
    return;
}

void wrap_attack(object target){
    object room = environment(target);
    
    if(!objectp(target)) return;
    
    message("combat_special", "%^RESET%^%^CRST%^%^C109%^A %^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le %^RESET%^%^C109%^looms up for a moment before swinging low!%^CRST%^", room);
    if(!userp(target)){
        message("combat_special", "%^RESET%^%^CRST%^%^C124%^It loops tightly about "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C124%^ and drags them overboard!%^CRST%^", room);
        target->move("/d/shadowgate/void");
        target->die();
        return;
    }
    if(SAVING_THROW_D->reflex_save(target, (powerlevel * 16))){
        message("combat_special", "%^RESET%^%^CRST%^%^C118%^You manage to jump aside as it sweeps across the deck!%^CRST%^", target);
        message("combat_special", "%^RESET%^%^CRST%^%^C118%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ manages to jump aside as it sweeps across the deck!%^CRST%^", room, target);
    }
    else{
        message("combat_special", "%^RESET%^%^CRST%^%^C196%^It catches you, latching on and looping about them!%^CRST%^", target);
        message("combat_special", "%^RESET%^%^CRST%^%^C196%^It catches "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^, latching on and looping about them!%^CRST%^", room, target);
        target->set_paralyzed(random(8) + 5, "%^RESET%^%^CRST%^%^C109%^You're still struggling against the hold of the tentacle!%^CRST%^");
        target->cause_typed_damage(target, "torso", roll_dice((powerlevel * 5), 10), "bludgeoning");
    }
    return;
}

void die(){
    object room = environment(this_object());
    message("environment", "\n%^RESET%^%^CRST%^%^C109%^The %^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le %^RESET%^%^C109%^retreats back into the %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r%^C109%^...%^CRST%^\n", room);
    if(controller) controller->remove_tentacle();
    this_object()->remove();
}

