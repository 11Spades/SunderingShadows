#include <std.h>
#include <damage_types.h>

inherit DAEMON;

int help();

int cmd_damall(string str){
    object * objs;
    object room;
    mixed *args;
    int amount;
    string who, type;

    string posxxx;
    if(!objectp(TP)) { return 0; }
    posxxx = lower_case((string)TP->query_position());
    if(posxxx == "builder" || posxxx == "apprentice")
    {
        tell_object(TP,"You cannot use this command as a builder or apprentice.");
        return 1;
    }
   
    if(!strlen(str))
        return help();
    
    room = environment(this_player());
   
    if(!objectp(room))
        return 1;

    objs = all_living(room);
    args = explode(str, " ");  
    amount = atoi(args[0]);

    if (!intp(amount))
        return help();
 
    if(sizeof(args) > 1)
        type = args[1];
   
    if(!type || !strlen(type) || member_array(type, VALID_DAMAGE_TYPES) < 0)
        type = "untyped";
   
    set_property("magic",1);
   
    foreach(object ob in objs)
    {
        ob->cause_typed_damage(ob, "torso", amount, type);
        write("%^RED%^BOLD%^You damaged %^WHITE%^" + ob->query_cap_name() + " %^RED%^for%^WHITE%^ " + amount + " " + type + " %^RED%^damage!");
    }
    return 1;
}

int help(){
   write(
@OBS
Syntax: damall <amount of hp> <damage type>
Warning: Always have a good reason when you use the command.
         Any abuse will lead to punishment.
Note: Put negative values in amount, you can make it a healing command
Damages everything in your environment.
OBS
   );
   return 1;
}
