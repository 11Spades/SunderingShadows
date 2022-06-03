//The Oni's Dance - LoKi 2022
#include <std.h>
inherit "/d/common/obj/clothing/robe.c";


void create()
{
   ::create();
      set_name(" ");
      set_id(({"robes","silk kimono","kimono","flowing silk kimono","The Oni's Dance"}));
      set_obvious_short("flowing silk kimono");
      set_short("%^C056%^T%^C057%^h%^C061%^e%^C056%^ O%^C061%^n%^C062%^i%^C056%^'s D%^C069%^a%^C061%^n%^C056%^c%^C075%^e%^CRST%^");
      set_long("Crafted from several layers of extremely "+
	  "thin silk of different colors, this kimono is a "+
	  "stunning work of art. The first layer is %^C240%^"+
	  "gray %^CRST%^as dark as %^C240%^storm clouds%^CRST%^, "+
	  "the second a %^C075%^light blue%^CRST%^ like %^C075%^"+
	  "seafoam%^CRST%^, and the top an almost %^C255%^sheer "+
	  "white%^CRST%^. The effect when the wearer moves is "+
	  "that of a %^C245%^thunderstorm%^CRST%^ flowing over "+
	  "them.\n");
        set_lore("%^C066%^Legend tells that the Oni were "+
		"once welcomed in the library, and even sat on the "+
		"Voice. We have lost the reasons why they retreated "+
		"to the forest of Mist, then deeper, now all but "+
		"disappeared from Serakii, but some items from their "+
		"halcyon age still remain.%^CRST%^\n%^C068%^- An "+
		"Incomplete History "+
		"of Serakii -%^CRST%^ %^C152%^Carrow Davin%^CRST%^\n");
      set_property("lore difficulty",40);      
      set_wear((:TO,"wear_func":));
      set_remove((:TO,"remove_func":));
      set_value(50000);
      set_type("clothing");
      set_property("no curse",1);
      set_property("enchantment",5);
      set_item_bonus("charisma", 6);
      set_item_bonus("radiant resistance", 20);
      set_item_bonus("void resistance", 20);
      set_property("no disenchant",1);
      set_property("no alter",1);
}


int wear_func(){
   object room, player;
   
   player = environment(this_object());    
   room = environment(this_object());

   tell_room(room,"%^C067%^"+player->query_cap_name()+" %^C067%^carefully "+
   "wraps the kimono around them.%^CRST%^",player);
   tell_object(player,"%^C067%^You tie the kimono around yourself.%^CRST%^");
   return 1;
}

int remove_func(){
   object room, player;
   
   player = environment(this_object());    
   room = environment(this_object());

   tell_room(room,"%^C081%^"+ETOQCN+" %^C081%^carefully removes their kimono.%^CRST%^",ETO);
   tell_object(player,"%^C081%^You carefully remove the kimono, making sure to not tear the silk.%^CRST%^");
   return 1;
}