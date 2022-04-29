// Chernobog & Titania (4/18/22)
// Dustdevil Minion

#include <std.h>
#include <daemons.h>

inherit MONSTER;

int powerlevel, lifespan;

void create(){
    ::create();
    set_name("dust devil");
    set_id(({ "elemental", "dustdevil", "whirlwind", "dust devil", "devil" }));
    set_short("%^RESET%^%^CRST%^%^C101%^small cloudy %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d %^C101%^of %^C144%^debris%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C101%^At a glance, this is just a small %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d %^RESET%^%^C101%^of %^C144%^dust %^C101%^and %^C144%^debris%^C101%^, but peering closer reveals a %^RESET%^%^C059%^sh%^C244%^a%^C059%^do%^C244%^w%^C059%^y en%^C244%^t%^C059%^ity %^RESET%^%^C101%^lurking within the commotion.%^CRST%^\n");
    set_race("elemental");
    add_limb("torso", "torso", 50, 0, 2);
    add_limb("right arm", "torso", 50, 0, 2);
    add_limb("left arm", "torso", 50, 0, 2);
    add_limb("head", "torso", 50, 0, 2);
    set_attack_limbs(({ "left arm", "right arm" }));
    set_gender("neuter");
    set_size(2);
    set_alignment(8);
    set_base_damage_type("bludgeoning");
    set_func_chance(50);
    set_funcs(({ "slam_attack" }));
    set_property("no_random_treasure", 1);
    set_powerlevel(5);
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 5), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 5));
    set_damage(powerlevel, 5);
    set_attacks_num(3);
    set_overall_ac(-(powerlevel * 5));
    set_max_hp(powerlevel * 75);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 5), "very low");
    lifespan = powerlevel;
    return;
}

void heart_beat(){
    object dustdevil;
    
    ::heart_beat();
    
    dustdevil = this_object();
    if(!objectp(dustdevil)) return;
    
    lifespan--;
    if(lifespan < 0) dustdevil->die();
    return;
}

void slam_attack(object target){
    object dustdevil, room;
    dustdevil = this_object();
    room = environment(dustdevil);
    
    if(!objectp(target)) return;
    
    tell_object(target, "%^RESET%^%^CRST%^%^C101%^Spinning about wildly, the %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d %^C101%^of debris twirls towards you...%^CRST%%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C101%^Spinning about wildly, the %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d %^C101%^of debris twirls towards "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^...%^CRST%^", target);
    if(SAVING_THROW_D->reflex_save(target, (powerlevel * 8))){
        tell_object(target, "%^RESET%^%^CRST%^%^C118%^You manage to sidestep the whirlwind of debris!");
        tell_room(room, "%^RESET%^%^CRST%^%^C118%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ manages to sidestep the whirlwind of debris!", target);
    }
    else{
        tell_object(target, "%^RESET%^%^CRST%^%^C196%^The whirlwind catches you, battering you all over with flying debris!%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C196%^The whirlwind catches "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^, battering them all over with flying debris!%^CRST%^", target);
        target->cause_typed_damage(target, "torso", roll_dice(powerlevel * 8, 10), "bludgeoning");
    }
    return;
}

void die(){
    object dustdevil, room;
    dustdevil = this_object();
    room = environment(dustdevil);
    
    if(objectp(room)) tell_room(room,"%^RESET%^%^CRST%^%^C101%^The dust devil fades away and its whirlwind disperses...%^CRST%^");
    dustdevil->remove();

    return;
}

