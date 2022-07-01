// Zombic Hand - Loki 2022

#include <std.h>
#include <daemons.h>

#include "../graez.h"

inherit WEAPONLESS;

void create() 
{
    ::create();
    set_name("Zombic Hand");
    set_id(({"hands","hand","zombie","zombic","zombic hand"}));
    set_short("%^C185%^Zo%^C114%^m%^C185%^bic Ha%^C114%^n%^C185%^d%^CRST%^");
    set_long("This %^C108%^hand%^CRST%^ is all that remains from some "+
        "poor soul who died in the %^C144%^swamp%^CRST%^. Where the "+
        "rest of its body went or how the hand alone is now animated "+
        "as %^C060%^something undead%^CRST%^ is a strange mystery. "+
        "The %^C113%^hand %^CRST%^scuttles along the ground, reaching "+
        "randomly for things to pull them %^C244%^down%^CRST%^.");
    set_overall_ac(3);
    set_race("undead");
    set_body_type("hand");
    add_limb("palm","palm",0,0,0);
    add_limb("index finger","index finger",0,0,0);
    add_limb("middle finger","middle finger",0,0,0);
    add_limb("ring finger","ring finger",0,0,0);
    add_limb("pinky finger","pinky finger",0,0,0);
    add_limb("thumb","thumb",0,0,0);

    set_class("fighter");
    set_mlevel("fighter", 25);
    set_new_exp(25,"normal");
    set_size(1);
    set_property("swarm",1);
    set_stats("strength",18);
    set_attacks_num(4);
    set_damage(5,7);    
    set_attack_limbs(({"palm","index finger","middle finger","ring finger","pinky finger","thumb"}));

    set_alignment(9);
    set_emotes(9,({"%^RED%^The Hands begin to %^BOLD%^claw%^RESET%^%^RED%^ at your ankles!",
        "%^BOLD%^You hear a %^BLUE%^moaning%^RESET%^%^BOLD%^ from beneath the surface of the swamp!",}),1);
    
    set("aggressive",35);
    set_resistance("negative energy",20);
    set_resistance("positive energy",-20); 
    set_property("no dominate",1);
    set_property("no hold", 1);
    set_property("no death", 1);
    set_property("no bows", 1);
    set_sight_bonus(5);
    set_property("no random treasure", 1);
    
    set_funcs(({"grab"}));
    set_func_chance(50);

}


void grab(object targ) { // 

  object room,nasty;
  
  nasty = this_object();
  room = environment(nasty);


  tell_object(targ, "%^C029%^The hand %^C035%^grabs%^C029%^ at you!%^CRST%^");
  tell_room(room, "%^C029%^The hand %^C035%^grabs%^C029%^ at%^CRST%^ "+targ->query_cap_name()+"%^C029%^!%^CRST%^",targ);

  if(SAVING_THROW_D->reflex_save(targ, (40))){
    tell_object(targ, "%^C034%^You manage to get away from the %^C065%^hand%^C034%^ before it can latch on!%^CRST%^");
    tell_room(room, "T%^C034%^he %^C060%^hand%^C034%^ scuttles away as %^CRST%^"+targ->query_cap_name()+" %^C034%^escapes its grasp!%^CRST%^",targ);

    return;
  } 

  tell_object(targ, "%^C112%^You are grabbed by the %^C060%^hand%^C112%^. You feel its effect right away as your very life is %^C244%^sucked%^C112%^ out of you, and it remains latched on you!%^CRST%^");
  tell_room(room, "%^C112%^The hand latches onto %^CRST%^"+targ->query_cap_name()+"%^C112%^!%^CRST%^",targ);
  targ->cause_typed_damage(targ, targ->return_target_limb(), roll_dice(10,8)+10,"negative energy");
  targ->set_paralyzed(5, "%^C100%^%^C143%^You feel %^C243%^numb%^C143%^ as the wound from the hand latching onto you still lingers%^CRST%^");

}


