#include <std.h>
#include "../elf.h"

inherit OBJECT;


void create(){
   ::create();
        set_name("iridescent stone");
        set_id(({ "stone", "iridescent stone", "iridescent ioun", "ioun", "ioun stone",
"iridescent ioun stone", "small stone", "small iridescent stone" }));
        set_short("Iridescent Ioun Stone");
        set_obvious_short("small stone");
       set_long(
@AVATAR
%^BOLD%^%^BLACK%^This is a small iridescent stone, nearly clear, about the size of a marble.  
It is perfectly round and smooth, with no markings whatsoever.%^RESET%^
AVATAR
        );
   
        set_lore(
@AVATAR
This is an ioun stone.  Ioun stones are magical items which, when used
%^ORANGE%^<use stone>%^RESET%^ will grant their users magical effects.  The type of effect is
determined by the color of the stone. 
This one looks to let the user breath water.
AVATAR
);//totally stolen from cyric
   set_property("lore difficulty",20);
   set_weight(1);
   set_value(18000);
}

void init(){
   ::init();
   add_action("break_func","use");
}

int break_func(string str){
   object ob, ob2;
   if ( !str || str !="stone") {
      notify_fail ("Use what?\n");
      return 0;
   }
   if(present("iridescent ioun",ETP)){
     notify_fail ("Stone already present.");
	 return 0;
   }
        if(TP->query_bound() || TP->query_unconcious() ||
TP->query_paralyzed() ||TP->query_tripped()) {
                TP->send_paralyzed_message("info",TP);
                return 1;
   }
  
         tell_object(ETO,"%^CYAN%^You activate the stone and it begins to orbit you.");
         tell_room(EETO,"%^CYAN%^"+ETOQCN+" activates the stone and it begins orbiting them.",ETO);
 
         ob=new(MON"istone");
         ob->move(EETO);
		 ob->owned(ETO);
         ETO->add_follower(ob);    
         TO->remove();
         return 1;
}
