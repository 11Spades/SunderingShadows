//

#include <std.h>

inherit DAEMON;

int help(){
    write(
@OLI
    grant <player> <exp> <class> <reason>

Will grant the exp indicated tot he specific class indicated. State a reason 
for the notes.

OLI
    );
    return 1;
}

int cmd_grant(string str){
    int exp;
    string who,theclass,reason;
    object player;

   string posxxx; 
   if(!objectp(TP)) { return 0; }
   posxxx = lower_case((string)TP->query_position());
   if(posxxx == "builder" || posxxx == "apprentice")
   {
       tell_object(TP,"You cannot use this command as a builder or apprentice.");
       return 1;
   }

    if (!str) {
        return help();
    }

    if (sscanf(str, "%s %d %s %s", who, exp, theclass, reason) != 4) {
        return help();
    }

    player = find_player(who);
    if (!objectp(player)) {
        return notify_fail("That player isn't around.\n");
    }
    write("%^BOLD%^You grant "+exp+" to "+capitalize(who)+"'s "+theclass+" class.");

    player->set_property("ignore tax",1);
    player->add_general_exp(theclass,exp);
    player->remove_property("ignore tax");

    "/cmds/avatar/_note.c"->cmd_note("ckpt "+player->query_name()+" %^BOLD%^%^CYAN%^was granted "+exp+" to the "+theclass+" by "+capitalize(TP->query_true_name())+" for "+reason+".");

    return 1;


}
