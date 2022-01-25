#include <std.h>
#include <damage_types.h>

inherit DAEMON;

int help();

int cmd_dam(string str){
    object obj;
    int amount;
    string type;
    mixed *args;

    string posxxx;
    if(!objectp(TP)) { return 0; }
    posxxx = lower_case((string)TP->query_position());
    if(posxxx == "builder" || posxxx == "apprentice")
    {
        tell_object(TP,"You cannot use this command as a builder or apprentice.");
        return 1;
    }
   
    if(!str || !strlen(str))
        return help();
   
    args = explode(str, " ");
   
    if(sizeof(args) < 2)
        return help();
   
    obj = find_player(args[0]);
   
    if(!userp(obj))
       return notify_fail("That person is not logged in.\n");
   
    amount = atoi(args[1]);
    
    if(!intp(amount) || !amount)
        return notify_fail("You must designate a numerical value 1 or greater for damage amount.\n");
    
    if(sizeof(args) < 3)
        type = "untyped";
    else
        type = args[2];
    
    if(!strlen(type) || member_array(type, VALID_DAMAGE_TYPES) < 0)
        type = "untyped";  
    
    set_property("magic",1);
    obj->cause_typed_damage(obj, "torso", amount, type);
    write("%^RED%^BOLD%^You damaged %^WHITE%^" + obj->query_cap_name() + " %^RED%^for%^WHITE%^ " + amount + " " + type + " %^RED%^damage!");
    return 1;
}

int help(){
   write(
@OBS
Syntax: dam <user> <amount of hp> <damage type>
Warning: Always have a good reason when you use the command.
         Any abuse will lead to punishment.
Note: Put negative values in amount, you can make it a healing command.
OBS
   );
   return 1;
}
