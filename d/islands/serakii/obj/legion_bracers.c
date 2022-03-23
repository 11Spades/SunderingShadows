//legion bracers - LoKi - 2021 
	
#include <std.h>
inherit "/d/common/obj/armour/bracers.c";

string thread;

void create() {
   ::create();
   set_name("legion bracers");
   set_id(({"pearl bracers", "legion bracers", "Legion bracers","bracers"}));
   set_short("%^C250%^Le%^C246%^g%^C250%^i%^C110%^o%^C250%^n "+
   "br%^C244%^a%^C250%^ce%^C111%^r%^C250%^s%^CRST%^");
   set_obvious_short("%^C247%^p%^C245%^e%^C247%^a%^C110%^"+
   "r%^C247%^l b%^C110%^r%^C247%^ace%^C246%^r%^C247%^s%^CRST%^");
   set_long("%^C247%^Crafted from %^C251%^pearl%^C247%^, "+
   "these bracers are extremely well made and would be "+
   "quite %^C044%^expensive%^C247%^. Some magic has taken all "+
   "of the %^C254%^pearl %^C247%^and reformed it into a perfectly "+
   "smooth surface for the bracers and allowed it to keep its "+
   "%^C224%^lustre%^C247%^. Near the top of the bracers is an "+
   "inlay of %^C242%^darker pearl%^C247%^ with the symbol of "+
   "a %^C254%^sphere %^C247%^with a %^C253%^shield %^C247%^behind "+
   "it. The bracers are affixed to the arm with heavy %^C063%^"+
   "blue silk%^C247%^ wraps.%^CRST%^\n");   
   set_lore("%^C110%^We have, all of us, lost so many of our friends "+
   "and comrades. We sanctify this new armor in the name of those we "+
   "lost, but with an eye to those we have remaining to protect. "+
   "Wear the pearl with pride.\n- %^C093%^Inquisitor Baltsar Albrecht%^CRST%^: From the "+
   "Legion Reformation");

   set_value(5000);
   set_property("enchantment",5);
   set_wear((:this_object(), "extra_wear":));
   set_remove((:TO,"removeme":));
   set_struck((:TO,"struck":));
}

int is_metal() { return 0; }


int extra_wear(){


   return 1;    
}

int removeme() {

   	return 1;
}

int strike_func(int damage, object what, object who){
    if(random(1000) < 100){
        tell_room(environment(query_worn()),"%^C247%^"+
            ""+ETOQCN+" %^247%^raises an arm to "+who->QCN+" "+
			"%^247%^'s strike, attempting to block the blow!",({ETO,who}));
        tell_object(ETO,"%^247%^You raise your arm "+
		"as "+who->QCN+" %^247%^strikes "+
		"you!");
        tell_object(who,"%^247%^"+ETOQCN+" %^247%^blocks some "+
		"of the blow with a raised arm!");
        return (damage/2);
    }
    return damage;
}

 
