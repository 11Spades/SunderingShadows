//dock.c

#include <std.h>
#include <daemons.h>
#define BOAT "/d/shadow/virtual/sea/obj/boat.c"
#define BOAT_DIR "/d/shadow/virtual/sea/obj/boats/"
inherit ROOM;

int is_virtual() { return 1; }
int is_water() { return 1; }
int is_dock() { return 1; }

int clean_up(){return 1;}

void create(){
     object ob;
   ::create();
    set_terrain(VILLAGE);
    set_travel(FOOT_PATH);
   set_property("training",1);
   set_property("no teleport",1);
/*
 ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({ "board", "bulletin board", "testing board" }) );
  ob->set_board_id("testing_board");
     ob->set("short","The ShadowGate Update Board");
     ob->set("long","An announcement of changes seen around the realms and the comments concerning those changes.");
  ob->set_max_posts(50);
    ob->set_location(base_name(TO));
*/
}
void init(){
   ::init();
   add_action("rent","rent");
   add_action("buy","buy");
   add_action("retrieve","retrieve");
   add_action("sell","sell");
   add_action("__Read_me","read");
   add_action("return_it","return");
}
	
string query_long(string str){
   string hold;
   if(!str) { // fixed as no set items could be viewed! N, 2/12.
     hold = room::query_long();
     hold += "\nThere is a sign here listing what can be done, please read it.\n";
     return hold;
   }
   return room::query_long(str);
}

int __Read_me(string str){
   if(!str || str != "sign") return 0;
   write(
@OLI
%^CYAN%^	This is the ship yard. From here you can do any number of things
concerning water transportation.
	rent boat  -------------  Will rent a boat for you. (1000 gold)
					(hope someone doesn't steal it)
	return boat  -----------  Will return rented boat.
	buy boat  --------------  Will buy a boat for you. (20000 gold)
					(this will make it so you always
					have a boat waiting for you)
	retrieve boat  ---------  Will call boat to this dock if you own one
	sell boat --------------  Will sell boat
		
	You will be interested to know that:
                    Laerad is located at 20,36.
                    Shadow is located at 0,36.
                    Deku is located at 20,16.
                    Dagger Straits are at 5,18. 
                    The Ocean is at 24,10 on the Dagger Sea.
                    Torm is located at 1,5 on the Dagger Sea.
                    Attaya is located at 28,43.
		 There are more islands that we have yet to map.
		
OLI
    );
    return 1;
}

int rent(string str){
   object ob;

   if(TP->query_property("shapeshifted"))
       return notify_fail("You can't do that while shapeshifted");

   if(!str || str != "boat")
      return notify_fail("Rent what?\n");
   if(!TP->query_funds("gold",1000))
      return notify_fail("You need 1000 gold to rent a boat.\n");
   ob = new(BOAT);
   ob->add_id("rental boat"); ob->add_id("rented boat");
   write("%^BOLD%^The harbor master sends for a boat for you to use.");
   tell_room(TO,"%^BOLD%^The harbor master sends for a boat for "+TPQCN+".",TP);
   call_out("get_boat",10,ob,TP);
   TP->use_funds("gold",1000);
   return 1;
}

void get_boat(object ob, object player)
{
   if(!objectp(ob)) return;
   tell_room(TO,"%^BOLD%^A small boat sails into the area for use.",player);
   tell_object(player,"%^BOLD%^Your boat sails into the area!\n");
   ob->move(TO);
   ob->make_me();
}

void get_boat2(object ob, object player){
   if(!objectp(ob)) return;
   tell_room(TO,"%^BOLD%^A small boat sails into the area for use.",player);
   if(present(player)) 
       tell_object(player,"%^BOLD%^Your boat sails into the area!\n");
   ob->move(TO);
   ob->make_me();
   ob->set_owner(player->query_name());
   ob->remove_exit("gangplank");
}

int return_it(string str){
   int money;
   object ob;

   if(TP->query_property("shapeshifted"))
       return notify_fail("You can't do that while shapeshifted");

   if(!str || str[0..3] != "boat")
      return notify_fail("Return what?\n");
   if(!ob=present(str))
      return notify_fail("No boat to return here\n");
   if((string)ob->query_owner() != "noone")
      return notify_fail("You can't return someone else's boat!\n");
   tell_room(TO,"%^MAGENTA%^The harbor master says%^RESET%^: Very well, hope you got use out of her.");
   tell_room(TO,"%^CYAN%^The harbor master has the boat locked and readied for the next user.");
   //should set up the virtual room daemon to move a person saved on the boat to the dock where the boat
   //was sold - Saide
   "/daemon/virtual_room_d"->destroy_virtual_room(ob->query_room()->query("my_virtual_name"), TO);
   ob->remove();
   money = 10 * (random(8)+1);
   TP->add_money("gold",money);
   write("%^BOLD%^Here's your money, "+money+" gold.");
   return 1;
}

int retrieve(string str){
   string file, file2;
   object ob;

   if(TP->query_property("shapeshifted"))
       return notify_fail("You can't do that while shapeshifted");

   if(!str || str[0..3] != "boat")
      return notify_fail("Retrieve what?\n");
   if((int)SAVE_D->is_member("boat_owners",TPQN) == -1)
      return notify_fail("We have no record of you owning a boat!\n");
   if(!file_exists(BOAT_DIR+TPQN+"boat.c")){
      write("Error in loading boat object: notify an immortal!");
      write_file(BOAT_DIR+"bad_boats","No "+TPQN+"boat.c on "+ctime(time())+"\n");
      return 1;
   }
   file = BOAT_DIR+TPQN+"boat.c";
   file2 = read_file(BOAT);
   rm(file);
      write_file(file,file2);

   if(!ob = find_object_or_load(BOAT_DIR+TPQN+"boat")){
      write("Error in loading boat object: notify an immortal!");
      write_file(BOAT_DIR+"bad_boats","No "+TPQN+"boat.c on "+ctime(time())+"\n");
      return 1;
   }
   if(objectp(environment(ob)) && environment(ob) == TO)
      return notify_fail("Umm, you're standing next to your boat.\n");
   call_out("get_boat2",5,ob,TP);
   write("%^BOLD%^%^CYAN%^You summon your boat from where ever it may be!");
   tell_room(TO,"%^BOLD%^%^CYAN%^"+TPQCN+" summons "+TP->query_possessive()+" boat!",TP);
   return 1;
}

int buy(string str){
   string file, file2;
   object ob;

   if(TP->query_property("shapeshifted"))
       return notify_fail("You can't do that while shapeshifted");

   if(!str || str[0..3] != "boat")
      return notify_fail("Buy what?\n");
   if((int)SAVE_D->is_member("boat_owners",TPQN) != -1)
      return notify_fail("You already own a boat!\n");
   if(!TP->query_funds("gold",20000))
      return notify_fail("You need 20000 gold to buy a boat!\n");
   file2 = BOAT_DIR+TPQN+"boat.c";
   if(!file_exists(file2)){
      file = read_file(BOAT);
      write_file(file2,file);
      if(!file_exists(file2)){
         write("Error in creation of your boat: contact an immortal or try again!");
         return 1;
      }
   }
   tell_room(TO,"%^BOLD%^%^MAGENTA%^The old man says%^RESET%^: Your boat will be ready for you momentarily, good thing we have extra stored for sale.");
   write("%^BOLD%^The old man takes your 20000 gold!");
   TP->use_funds("gold",20000);
   SAVE_D->set_value("boat_owners",TPQN);
   tell_room(TO,"%^BOLD%^%^MAGENTA%^The old man says%^RESET%^: just retrieve your boat when you want to use it.");
   return 1;
}

int sell(string str){
   int money;
   object ob;

   if(!str || str[0..3] != "boat")
      return notify_fail("Retrieve what?\n");
   if((int)SAVE_D->is_member("boat_owners",TPQN) == -1)
      return notify_fail("We have no record of you owning a boat!\n");
   if(!(ob = find_object_or_load(BOAT_DIR+TPQN+"boat"))){
      write("Error in loading boat object: notify an immortal!");
      write_file(BOAT_DIR+"bad_boats","No "+TPQN+"boat.c on "+ctime(time())+"\n");
      return 1;
   }
   if(TP->query_property("shapeshifted")) 
       return notify_fail("You can't do that while shapeshifted");

   //should set up the virtual room daemon to move a person saved on the boat to the dock where the boat
   //was sold - Saide
   "/daemon/virtual_room_d"->destroy_virtual_room(ob->query_room()->query("my_virtual_name"), TO);
   ob->remove();
   money = (random(10) +1) * 1000;
   tell_room(TO,"The old man hands "+TPQCN+" some money.",TP);
   write("The old man hands you "+money+" gold for your old boat.");
   SAVE_D->remove_name_from_array("boat_owners",TPQN);
   TP->add_money("gold",money);
   return 1;
}
