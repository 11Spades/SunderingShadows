//Coded by Bane//
//added lines to also attack the now wandering wild creatures, hopefully to
//prevent them killing PC's in error due to the swarm - complaint was from 
//battles where the forest critters wandered in to their area and attacked 
//the PC's and the commandos jumped in to help the forest critters due to swarm
//Styx 12/15/01
//removed the special wander code to set moving & speed & pre-exit functions 
//to keep them in their area. - Styx 12/29/01
//over-loading move_around here and taking the pre-exit room functions out so if 
//they are shot by bows they can chase - Styx 1/12/02

#include <std.h>
#define ASDIR "/d/laerad/parnelli/asgard/"
#define NOGOROOM ({ASDIR+"as56", ASDIR+"as57","/d/laerad/parnelli/forest/for081"})

//inherit "/d/laerad/mon/wander/cwander.c";
inherit WEAPONLESS;

void kill_em(object targ);

void create(){
    ::create();
    set_id(({"commando","Commando","asgard commando"}));
    set_name("commando");
    set_short("An Asgard Commando");
    set_long(
	"This man is a pure bred machine of death and destruction.  He is "+
	"dressed in camouflage armor and covered in green and black paint.  "+
	"He is extremely well built, his muscles bulging as he drops back "+
	"into a karate stance.  These men have been trained since birth "+
	"to be the assassins for the king of Asgard.  They know one enemy, "+
	"the hated Trolls from Systyquah!"
    );
    set_body_type("human");
    set_race("human");
    set_gender("male");
    set_size(2);
    set_hd(20+(random(9)),6);
    set_hp(166+(random(72)));
    set_max_level(27);
    set_overall_ac(-5);
    set_exp(12000);
    set_alignment(8);
    set_class("fighter");
    set_guild_level("fighter",24);
    set_stats("strength",22);
    set_stats("dexterity",20);
    set_stats("constitution",19);
    set_stats("charisma",18);
    set_base_damage_type("magebludgeon");
    set_attack_limbs(({"right hand","left hand","right foot","left foot"}));
    set_attacks_num(4);
    set_damage(1,6);
    set_mob_magic_resistance("average");
    set_property("swarm",1);
    set("aggressive", "kill_em");
    set_funcs(({"headlock","kick"}));
    set_func_chance(30);
    set_moving(1);
    set_speed(10);
}

void move_around() {
   string *exits;
   string exitn;
   int j;

   if(!this_object()) return;
   if(!objectp(ETO)) return;
   ETO->setupExits();
   if(query_current_attacker()) return;
   if(environment(this_object()))
      exits = environment(TO)->query_exits();
   if(sizeof(exits)){
      j = random(sizeof(exits));
      exitn = (string)environment(TO)->query_exit(exits[j]);
//      if(exitn != ASDIR+"as56" && exitn != ASDIR+"as57")  {
      if(member_array(exitn,NOGOROOM) == -1) {
         (ETO->query_exit(exits[j]) )->init();
         exitn->init();
         TO->force_me(exits[j]);
      }
   }
   moving=0;
}

void kill_em(object targ) {
    if(member_array("forestmon",TP->query_id()) != -1) {   
       force_me("say %^BOLD%^No wild forest animals are getting in OUR city!");
       force_me("kill "+TPQN);
    }
    return;
}

void headlock(object targ){
    if(!"daemon/saving_d"->saving_throw(targ,"paralyzation_poison_death")){
	tell_object(targ,"%^BOLD%^GREEN%^The Commando slips in behind you and puts you in a painful headlock!");
	tell_room(ETO,"%^BOLD%^GREEN%^The Commando slips in behind "+targ->query_cap_name()+" and puts "+targ->query_objective()+" in a headlock!",targ);
	targ->set_paralyzed(30,"You are in a headlock.");
	return 1;
    }
    tell_object(targ,"%^BOLD%^GREEN%^The Commando attempts to slip in behind you but you cut him off!");
    tell_room(ETO,"%^BOLD%^GREEN%^The Commando attempts to slip in behind "+targ->query_cap_name()+" but "+targ->query_subjective()+" cuts him off!",targ);
    return 1;
}
void kick(object targ){
    if(!"daemon/saving_d"->saving_throw(targ,"rod_staff_wand")){
	tell_object(targ,"%^BOLD%^RED%^The Commando sends a bone crunching karate kick right to your throat!");
	tell_room(ETO,"%^BOLD%^RED%^The Commando sends a bone crunching karate kick right to "+targ->query_cap_name()+"'s throat!",targ);
	targ->do_damage(targ->return_target_limb(),roll_dice(5,10)+10);
	return 1;
    }
    tell_object(targ,"%^BOLD%^RED%^The Commando sends a karate kick towards you but you dodge out of the way!");
    tell_room(ETO,"%^BOLD%^RED%^The Commando sends a karate kick at "+targ->query_cap_name()+" but "+targ->query_subjective()+" dodges out of the way!",targ);
    return 1;
}

void heart_beat(){
    ::heart_beat();
  if(!objectp(TO)) return;
    if(random(20) < 2){
	TO->set_invis();
    }
}

void init(){
    ::init();
    if((string)TP->query_race() == "troll"){
	   force_me("say DIE TROLL!");
      force_me("kill troll");
    }
    if(member_array("forestmon",TP->query_id()) != -1) {   
       force_me("say %^BOLD%^No wild forest animals are getting in OUR city!");
       force_me("kill forestmon");
    }

    add_action("no_way","rush");
    add_action("no_way","stab");
}

int no_way(){
    write("The Commando easily catches you at your pitiful attempt.");
    return 1;
}
