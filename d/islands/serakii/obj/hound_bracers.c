//hound bracers - LoKi - 2021 
	
#include <std.h>
inherit "/d/common/obj/armour/bracers.c";

string thread;

void create() {
   ::create();
   set_name("hound bracers");
   set_id(({"black leather bracers", "hound bracers", "leather bracers","bracers"}));
   set_short("%^C245%^hou%^C094%^n%^C245%^d "+
   "br%^C094%^a%^C245%^cers%^CRST%^");
   set_obvious_short("%^C244%^b%^C250%^l%^C244%^ack %^C094%^leath%^C245%^e%^C094%^r%^C244%^ "+
   "brace%^C248%^r%^C244%^s%^CRST%^");
   set_long("%^C245%^crafted with multiple "+
   "layers of %^C250%^thick black leather%^C245%^ "+
   "these bracers protect the %^C094%^forearm "+
   "%^C245%^of the wearer from any glancing blows. "+
   "They are mostly unadorned, with only a small "+
   "%^C251%^inlay %^C245%^near the wrist of "+
   "a %^C095%^canine paw%^C245%^. The bracers "+
   "are attached to the arm via %^C095%^leather "+
   "straps %^C245%^and %^C253%^ivory "+
   "buckles%^C245%^. %^CRST%^\n");   
   set_lore("%^C095%^Before you attack a fellow "+
   "hound look at their forearms. If you see "+
   "bracers, forget it. Dying isn't worth "+
   "whatever insulted your baby ego. Bracers "+
   "means officer. Officer means they can "+
   "kill you without penalty or "+
   "thought.%^C096%^\n- Captain Crenar, "+
   "Expedition Commander%^C250%^: From the "+
   "Hound Operations Manual %^CRST%^");
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
        tell_room(environment(query_worn()),"%^C124%^"+
            ""+ETOQCN+" %^C095%^raises an arm to "+who->QCN+" "+
			"%^C095%^'s strike, attempting to block the blow!",({ETO,who}));
        tell_object(ETO,"%^C095%^You raise your arm "+
		"as "+who->QCN+" %^C095%^strikes "+
		"you!");
        tell_object(who,"%^C095%^"+ETOQCN+" %^C095%^blocks some "+
		"of the blow with a raised arm!");
        return (damage/2);
 }
}

