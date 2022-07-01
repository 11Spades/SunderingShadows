#include <std.h>



inherit "/d/common/obj/weapon/two_hand_sword.c";


int hit_func;
int wield_func;
int unwield_func;

object room,wielder,room;


create() {
   ::create();
   set_id(({"sword"}));
   set_name("sword");
   set_obvious_short("sword");
   set_short("sword");
   set_long("sword sword");
   set_lore("lore");
   set_property("lore difficulty",20);
   set_value(1000);
   set_hit((:TO,"hit_func":));
   set_wield((:TO,"wield_func":));
   set_unwield((:TO,"unwield_func":));

}

int wield_func(){
	wielder = this_player();
    room = environment(this_object());
    tell_object(wielder," .");
    tell_room(environment(room),"As"+wielder->query_cap_name()+" .",wielder);
   return 1;
}


int unwield_func(){
	wielder = this_player();
    room = environment(this_object());
    tell_object(wielder," .");
    tell_room(environment(room),"As "+wielder->query_cap_name()+"  .",wielder);
    return 1;
}

int hit_func(object target) {
    object ob; 
    string targ_name,wielder_name;

    room = environment(this_player());
    targ_name = target->query_cap_name();
    if(!objectp(target)) return 0;
    if(random(1000) < 900){
      switch(random(12)){
           case 0..10:
            tell_object(wielder, "You hit " +targ_name+ "!");
            tell_object(target, "" +wielder_name+ " hits you!");
            tell_room(room, ""+wielder_name+" hits "+targ_name+"! SMASH!",({ target, wielder }));
            target->cause_typed_damage(target, target->return_target_limb(), 
			this_object()->special_damage(), "divine");

              break;

         case 11:

             break;
      }
          return 1;
   }
   }
