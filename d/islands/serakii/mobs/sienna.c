#include <std.h>
#include <daemons.h>
#include "../serakii.h"

inherit MONSTER;

void create()
{
    object obj,ob;
    ::create();
    set_name("Commander Sienna Kava");
    set_id(({ "sienna", "Sienna", "sienna kava", "commander", "hound commander" }));
    set_short("%^C242%^Co%^C247%^m%^C242%^man%^C244%^d%^C242%^e"+
	"r S%^C056%^i%^C242%^enna K%^C056%^a%^C242%^va%^CRST%^");
    set_long("%^C246%^Dressed in the armor of a %^C100%^Hound%^C246%^, "+
	"this %^C053%^half-drow%^C246%^ woman is obviously much more than "+
	"a simple %^C064%^soldier%^C246%^. She wears her %^C058%^armor "+
	"%^C246%^with a casual indifference and her eyes show %^C168%^"+
	"malice %^C246%^even the toughened %^C064%^soldiers %^C246%^"+
	"outside would balk at. Her form is elegant and %^C043%^lithe "+
	"%^C246%^and her arms and legs show she has considerable %^C088%^"+
	"strength%^C246%^. She wields a %^C058%^whip %^C246%^in one hand, "+
	"unraveled and ready.%^CRST%^\n");
    set_race("half-drow");
    set_gender("female");
    set_class("fighter");
    set_guild_level("fighter",40);
    set_property("full attacks",1);
    set_hd(30, 6);
    set_overall_ac(-20);
    set_property("magic", 1);
    set_max_hp(2500);
    set_hp(2500);
    set_property("swarm", 1);
    set_property("no death", 1);
    set_property("no blind", 1);
    set_property("no hold", 1);
    set_property("no paralyze", 1);
    set_property("no knockdown", 1);
    set_property("magic", 1);
    set_stats("strength", 25);
    set_stats("dexterity", 25);
    set_stats("constitution", 25);
    set("aggressive", "aggfunc");
    set_mob_magic_resistance("very high");
    set_property("damage resistance", 20);
    set_property("spell damage resistance", 40);
    set_new_exp(30, "boss");

    set_funcs(({ 

      "rushit",
	  "flashit",
	  "kdit"

	}));
	
    set_func_chance(101);
    set_attacks_num(10);
    set_property("function and attack", 1);
    add_money("gold", 8000 + random(6000));
    set_monster_feats(({
         "precise strikes",
         "dodge",
         "mobility",
         "scramble",
         "spring attack",
         "defensive roll",
         "resistance",
         "increased resistance",
         "damage resistance",
         "improved damage resistance",
         "toughness",
		 "rush",
		 "knockdown",
		 "improved rush",
    }));
    set_skill("athletics", 20); 
    set_attacks_num(10);
    set_property("function and attack", 1);
	
	ob = new(OBJ"hound_robe.c");
    ob->move(TO);
    command("wear robe");
    ob = new(OBJ"hound_belt.c");
    ob->move(TO);
    command("wear belt");
    ob = new(OBJ"hound_bracers.c");
    ob->move(TO);
    command("wear bracers");
	
    ob = new(OBJ"black_leather_whip.c");
	ob->move(TO);
	command("wield whip");
	
	ob = new("/d/common/obj/armour/studded");
    ob->move(TO);
    command("wear studded");
     new(OBJ"hound_seal")->move(TO);
}

void set_paralyzed(int time,string message){return 1;}

void kdit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("knockdown "+targ->query_name());
}

void flashit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("flash "+targ->query_name());
}

void rushit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("rush "+targ->query_name());
}

void init(){
   ::init();
   add_action("xstab","stab");
   add_action("xcrit","crit");
   add_action("xrush","rush");

}

int xstab(string str){

   if(str=="sienna" || str=="attacker"){

      tell_object(TP,"%^BOLD%^%^RED%^As you try to stab sienna she grabs you and throws you over her shoulder to the ground!%^RESET%^");
      tell_room(ETO,"As "+TPQCN+" tries to stab sienna, she grabs "+TP->QO+" and flips them over!",TP);
	  TP->do_damage("torso",random(100)+80);

      return 1;
    }
}

int xrush(string str){

   if(str=="sienna" || str=="attacker"){
	   
      tell_object(TP,"sienna watches as you rush.");
      tell_object(TP,"%^BOLD%^%^RED%^At the last second, she steps aside and punches you in the face!%^RESET%^");
      tell_room(ETO,"As "+TPQCN+" tries to rush sienna, she sidesteps and punches them in the face!",TP);
	  TP->do_damage("torso",random(100)+80);
	  
      return 1;
   }
}


int xcrit(string str){
   if(str=="sienna" || str=="attacker"){
      tell_object(TP,"You slide up to the commander and try to sneak in a deadly blow.");
      tell_object(TP,"%^BOLD%^%^RED%^sienna grabs you and knees you hard in the belly with an armored knee!%^RESET%^");
      tell_room(ETO,"As "+TPQCN+" tries to attack they get kneed in the belly and double over!",TP);
	  TP->do_damage("torso",random(100)+80);
	  
      return 1;

   }
}

void aggfunc()
{
    set("aggresive",4);
}
