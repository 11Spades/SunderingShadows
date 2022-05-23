/*
Calm Repear - LoKi 2022
*/

#include <std.h>
#include <daemons.h>

#define HIT_INTERVAL 4

inherit "/d/common/obj/weapon/sickle.c";

int count;
object owner,ob;

void create()
{
    ::create();
    set_name("Calm Reaper");
    set_id( ({ "calm reaper", "Calm Reaper", "reaper", "sickle", "silver sickle"}) );
    set_short("%^C067%^ca%^C073%^l%^C067%^m r%^C074%^e%^C067%^ap%^C074%^e%^C067%^r%^CRST%^");
    set_obvious_short("%^C246%^s%^C247%^i%^C246%^l%^C248%^v%^C246%^er s%^C247%^i%^C246%^c%^C247%^k%^C246%^le%^CRST%^");
    set_long("Usually a %^C034%^farmers%^CRST%^' implement, "+
	"this is instantly recognized as a %^C242%^sickle%^CRST%^, "+
	"but the amount of craftsmanship and detail shows this "+
	"particular %^C242%^sickle %^CRST%^is more than a "+
	"harvester of %^C058%^grains%^CRST%^. The handle is a %^C195%^bone "+
	"white wood%^CRST%^ with a %^C248%^silver inlay%^CRST%^ "+
	"of %^C073%^runes %^CRST%^and the cap at the end of the handle "+
	"is similarly %^C249%^silver %^CRST%^with a fine script you "+
	"could %^C241%^>read<%^CRST%^ on it. The blade of the %^C242%^sickle %^CRST%^is an impossible mixture of %^C238%^steel %^CRST%^and %^C244%^silver%^CRST%^, where the "+
	"steel provides the backbone of the blade with the %^C244%^silver "+
	"%^CRST%^entwined in it like the roots of a %^C064%^tree%^CRST%^. "+
	"While the effect is beautiful it also ensures any wound is both "+
	"sharp, and tinged with the bite of silver as well.\n");

        set_lore("%^C066%^Into the mass of undead he dove. "+
		"In either hand he bore the implement of the farmer, "+
		"the sickles that had months earlier brought food to "+
		"his village. Now he faced his family and friends as "+
		"legion of undead with only the voice of Lysara in his "+
		"head. He would calmly and methodically reap this new "+
		"crop, and while none would dine on what was grown "+
		"in that field, he was confident that he was doing "+
		"her work.%^CRST%^\n%^C068%^- How Many are our scars, "+
		"the lost villages of Attaya -%^CRST%^ %^C152%^Carrow Davin%^CRST%^\n");
    set_property("lore difficulty", 30);
    set_property("id difficulty", 30);

    // Enchantment and Bonuses
    set_property("enchantment", 4);
    set_item_bonus("attack bonus", 4);

    // Wield and Unwield
    set_wield((: TO, "extra_wield" :));
    set_unwield((: TO, "extra_unwield" :));
    set_hit((: TO, "extra_hit" :));

}

void init() {
    ::init();
    add_action("read_fun", "read");
}

int extra_wield()
{
    owner = environment(this_object());
     
    tell_object(owner, "%^C059%^You grip the sickle in your hand with grim resolve.%^RESET%^");
    tell_room(environment(owner), "%^C059%^" + owner->query_cap_name() + " %^C059%^wields the sickle with a grim look.%^RESET%^", owner);

  if((ob = present("calm reaper",ETO)) && living(ETO) && ob != TO)
  {
     if(ob->query_wielded())
     {
      set_item_bonus("will",10);
    tell_object(owner, "%^C059%^As you wield the second sickle a sense of perfect resolve comes over you.%^RESET%^%^RESET%^");
     }
  }	
	return 1;
}

int extra_unwield()
{
    
    tell_object(owner, "%^C069%^You release the sickle and feel you can breathe again.%^RESET%^");
    tell_room(environment(owner), "%^C069%^" + owner->query_cap_name() + "%^C069%^ unwields the sickle and opens their eyes.%^RESET%^", owner);
    return 1;
}

int extra_damage(object ob)
{
    int bonus;
    
    bonus = this_object()->query_wc() + this_object()->query_property("enchantment") + owner->query_damage_bonus();
    bonus += BONUS_D->new_damage_bonus(this_object(), owner->query_stats("strength"));
    
    return bonus;
}

int extra_hit(object ob)
{
    object room, attackers;
    int bonus;
    string ename, oname, oposs;
    
    if(!objectp(ob) || !objectp(owner))
        return 0;
    
    room = environment(owner);
    
    if(!objectp(room))
        return 0;
    
    count++;
    
    if(count < HIT_INTERVAL)
        return 0;
    
    count = 0;
    ename = ob->query_cap_name();
    oname = owner->query_cap_name();
    oposs = owner->query_possessive();
    
    switch(random(3))
    {
        case 0:
        tell_object(owner, "%^C147%^Your sickle sings as you launch into another attack!%^CRST%^");
        owner->execute_attack();
        break;
        case 1:
        tell_object(owner, "%^BOLD%^You launch yourself at " + ename + "%^BOLD%^ and slice " + ob->query_objective() + "%^BOLD%^!");
        tell_object(ob, "%^BOLD%^As the sickle slices into your skin you feel the bite of the silver!%^RESET%^");
        ob->cause_typed_damage(ob, "torso", extra_damage(ob), "silver");
        break;
        case 2:
        tell_object(owner, "%^C067%^The sickle in your hand glows with a soft light!%^CRST%^");
        owner->add_hp(random(50)+20);
        break;
    }
    
    return (bonus + roll_dice(3, 4));
}   

int read_fun(string str,object who){

    if(!str) {
       tell_object(TP,"%^BLACK%^%^BOLD%^Read what?\n%^RESET%^");
       return 1;
    }

    if((str == "sickle") || (str == "Calm Reaper")){
        tell_object(TP,"%^C081%^The reaping of undead need continue. Only with two sickles can you have the will to do what needs done...%^CRST%^\n");
        tell_room(ETP,""+TPQCN+" reads the runes on their sickle.",TP);

       return 1;
    }
    return 0;
}

