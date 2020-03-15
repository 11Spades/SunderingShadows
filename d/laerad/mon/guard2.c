//Coded by Bane//
#include <std.h>
#include <daemons.h>
inherit "/d/laerad/mon/wander/pwander.c";
object *attackers;
void create(){
    ::create();
    set_id(({"guard","city guard","City guard"}));
    set_name("City guard");
    set_short("A city guard");
    set_long(
	"A city guardsman, here to protect the peaceful citizens of the "+
	"city of Asgard.  They patrol the streets keeping peace and fighting "+
	"crime.  These guards are said to be extremely honorable and are "+
	"rumored to despise anyone not of the 6 leading races of shadow."
    );
    set_body_type("human");
    set_race("human");
    set_gender("male");
    set_size(2);
    set_hd(10+(random(8)),15);
    set_hp(95+(random(64)));
    set_property("magic resistance",35);
    set_property("swarm",1);
    set_property("full attacks",1);
    set_overall_ac(2);
    set_exp(3500);
    set_stats("strength",18);
    set_stats("constitution",18);
    set_stats("dexterity",17);
    set_stats("charisma",17);
    set_damage_bonus(1);
    set_class("fighter");
    set_guild_level("fighter",15);
    add_search_path("/cmds/fighter");
    set_alignment(1);
    add_money("gold",random(500)+150);
    add_money("platinum",random(10)+5);
    set_wielding_limbs(({"right hand","left hand"}));
    new("/d/shadow/obj/armor/banded")->move(this_object());
    command("wear armor");
    new("/d/shadow/obj/armor/helm")->move(this_object());
    command("wear helm");
    new("/d/shadow/obj/weapon/two_hand_sword")->move(this_object());
    command("wield sword in right hand and left hand");
    set_max_level(35); //added by Ares 3-31-05, they should be moving on long before now, but just in case

}
void init(){
    string race;
    ::init();
    if ((string)TP->query_vehicle_type() != "riding animal" ) {
      race = (string)TP->query_race();
    } else { 
      if (objectp(TP->query_current_rider()))
	if (!call_other((object)TP->query_current_rider(),"query_invis"))
	  race = call_other((object)TP->query_current_rider(),"query_race");
      if (!stringp(race))
	race = "horse";
    }
    if(wizardp(TP)) return;
   if(TP->query_invis()) return;
    if(race == "human" || race == "elf" || race == "half-elf" || 
       race == "dwarf" || race == "gnome" || race == "halfling" || 
       race == "horse") {
       return;
    }
	if(interactive(TP)){
	force_me("say You are not welcome here outsider!");
	}
   force_me("kill "+TPQN);
	return 1;
}
void heart_beat(){
        int i, j;
        object *att;
        if(!objectp(TO)) return;
        ::heart_beat();
        if((att = query_attackers()) != ({})){
                j = sizeof(att);
                for(i = 0;i <j;i++){
                        call_out("force_me",2,"rush "+att[i]->query_name());

                }
        }
}
