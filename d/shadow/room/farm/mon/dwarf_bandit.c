#include <std.h>
#include "../farm.h"

inherit MONSTER;

#define COLORS ({"%^RED%^red%^RESET%^",\
"%^RESET%^%^ORANGE%^brown%^RESET%^", \
"%^BOLD%^%^BLACK%^black%^RESET%^", \
"%^RESET%^gray%^RESET%^",\
"%^YELLOW%^blonde%^RESET%^",\
"%^BOLD%^%^WHITE%^silver%^RESET%^"})

void create(){
     	int j;
	string str, COLOR;
	object obj; 
	::create();
	j = random(sizeof(COLORS));
      COLOR = COLORS[j];
	set_name("dwarf bandit");
	set_id(({"dwarf","bandit","dwarf bandit","farm_mon"}));
	set_short("%^RESET%^A stocky "+COLOR+" beard dwarf");
	set_long("With his grizzly beard and ruddy completion,"+
		" this short and stout dwarf looks irate and "+
		"angry.  His stocky body is about as wide as he "+
		"is tall.  Dressed in a simple earthen colored "+
		"shirt and breeches, the dwarf doesn't seem to "+
		"concerned with his appearance.  His "+COLOR+" %^CYAN%^wiry"+
		" beard spills off of his face and hangs down over his"+
		" chest.  His thick bushy "+COLOR+"%^CYAN%^ eyebrows almost "+
		"seem to hide his eyes.  A strange aroma of sweat, ale"+
		" and tobacco rolls off of his clothing and body.\n");
	set_race("dwarf");
	set_body_type("dwarf");
//        set_size(1);
        set_hd(12,5);
	set_stats("strength",16);
	set_stats("intelligence",15);
	set_stats("dexterity",18);
	set_stats("charisma",12);
	set_stats("constitution",16);
	set_stats("wisdom",15);
	set_overall_ac(8);
	set_property("full attacks",1);
	set_size(1);
	set_alignment(6);
		switch(random(2)){
case 0:
	obj=new(OBJ"hide");
if(random(3))
{
	obj->set_property("monsterweapon",1);
}
	obj->move(TO);
break;
case 1:
	obj=new(OBJ"leatherbp");
	if(random(3))
{
	obj->set_property("monsterweapon",1);
}
	obj->move(TO);
break;
	}
	set_property("magic resistance",10);//adjusted MR - was 30, Circe
		switch(random(5)){
case 0:
	set_class("fighter");
     	set_mlevel("fighter",12);
     	set_guild_level("fighter",12);
	add_search_path("/cmds/fighter");
      set_stats("strength",18);
	set_parrying(1);
	obj=new("/d/common/obj/weapon/battle_axe.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
	command("wield axe");
	force_me("wearall");
break;
case 1:
     	set_class("thief");
	set_mlevel("thief",12);
	set_guild_level("thief",12);
	add_search_path("/cmds/thief");
	set_thief_skill("hide in shadows",95);
     	set_thief_skill("move silently",95);
	set_stats("dexterity",18);
     	set_stats("constitution",17);
	set_scrambling(1);
	obj=new("/d/common/obj/weapon/shortsword.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
	obj=new("/d/common/obj/weapon/dagger.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
	command("wield sword");
	command("wield dagger");
	command("wearall");
break;
case 2:
     	set_class("cleric");
     	set_mlevel("cleric",12);
     	set_guild_level("cleric",12);
     	add_search_path("/cmds/cleric");
     	set_stats("wisdom",18);
	set_diety("mask");
	set_spell_chance(40);
	set_spells( ({ "limb attack","dispel magic"}) );
	obj=new("/d/common/obj/weapon/warhammer.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
	force_me("wearall");
break;
case 3:
     	set_class("fighter");
	set_class("thief");
     	set_mlevel("fighter",11);
	set_mlevel("thief",12);
    	set_guild_level("fighter",11);
	set_guild_level("thief",12);
    	add_search_path("/cmds/fighter");
	add_search_path("/cmds/thief");
     	set_stats("dexterity",18);
     	set_stats("constitution",16);
	obj=new("/d/common/obj/weapon/broad.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
   	command("wield sword");
	command("wearall");
break;
default:
     	set_class("fighter");
	set_class("cleric");
     	set_mlevel("cleric",12);
	set_mlevel("fighter",12);
     	set_guild_level("cleric",12);
	set_guild_level("fighter",12);
     	add_search_path("/cmds/cleric");
	add_search_path("/cmds/fighter");
     	set_stats("strength",17);
     	set_stats("dexterity",18);
	obj=new("/d/common/obj/weapon/warhammer.c");
	obj->set_property("monsterweapon",1);
	obj->move(TO);
	set_diety("mask");
	set_spell_chance(20);
	set_spells( ({ "limb attack","dispel magic"}) );
	set_parrying(1);
	command("wield hammer");
	command("wearall");
break;
}
	set_property("add kits",2);
	set_gender("male");
	set_size(2);   
	add_money("gold",random(20));
	add_money("silver",random(40));
	add_money("platinum",random(2));
	add_money("electrum",random(20));
	set_max_level(15);
	set_hp(random(25)+75);
      set_property("swarm",1);
      set("aggressive",25);
	//set_speed(30);
	set_nogo(({ ROOMDIR"farm6",
			ROOMDIR"gnomehome",}));
	set_exp(random(200)+1000);
	set_languages( ({ "common" }) );
	set_emotes(10,({
		"%^YELLOW%^The dwarf belches.",
		"%^BOLD%^%^GREEN%^The dwarf takes a swig of ale from his waterskin."
    	}),1);

}
