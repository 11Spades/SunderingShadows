#include <std.h>
#define THIEVERY_D "/daemon/thievery_d.c"

inherit DAEMON;

int cmd_plant(string str) {
    mapping results;
    object *inv, victim, ob;
    string what, whom;
    int i, skip, which, thief_roll, victim_roll;

    /* Various checking */
    if (TP->query_ghost()) {
        notify_fail("You cannot do that in your immaterial state.\n");
        return 0;
    }

    if (TP->query_bound() || TP->query_tripped()) {
        TP->send_paralyzed_message("info",TP);
        return 1;
    }

    if (!str) {
        notify_fail("Plant what on whom?\n");
        return 0;
    }
    if (TP->query_disable()) {
        write("You are still finishing a previous attempt.");
        return 1;
    }

    if (sscanf(str, "%s on %s", what, whom) != 2) {
        notify_fail("Plant what on whom?\n");
        return 0;
    }
    if (TP->query_current_attacker()) {
        notify_fail("You cannot do that while in combat!\n");
        return 0;
    }
    victim = present(whom, ETP);
    if (!victim) {
        notify_fail(capitalize(whom)+" is not here!\n");
        return 0;
    }
    if (!living(victim)) {
        notify_fail(capitalize(whom)+" is not a living thing!\n");
        return 0;
    }
    if (victim->is_player() && !interactive(victim)) {
        notify_fail("You cannot steal from link-dead players.\n");
        return 0;
    }

    if (!TP->ok_to_kill(victim)) return notify_fail("Super natural forces prevent you.\n");

    if (wizardp(victim)) {
        tell_object(victim,TPQCN+" just tried to plant something on you... break "+TP->query_possessive()+" arms.\n");
        notify_fail(victim->query_cap_name()+" is going to hurt you when "+victim->query_subjective()+" gets this message.\n");
        return 0;
    }

   if (victim == TP) {
      notify_fail("Plant on yourself?\n");
      return 0;
   }

    if (victim->query_property("no steal")) {
        notify_fail((string)victim->query_cap_name()+" cannot be planted on!\n");
        return 0;
    }

//    if ((total_light(TP)+TP->query_sight_bonus()) < -1) {
   if (TP->light_blind(-1)) {
        notify_fail(TP->light_blind_fail_message(TP->light_blind(-1))+"\n");
        return 0;
    }

    ob = present(what, TP);

    if (!ob) {
        notify_fail("You do not have that!\n");
        return 0;
    }
    if (ob->drop()) {
        notify_fail("You cannot plant that!\n");
        return 0;
    }

   if(ETP->query_property("no steal")) {
      notify_fail("A magic force prevents you from doing that!\n");
      return 0;
   }

    if (ob->query_property("no steal")) {
        write((string)victim->query_cap_name()+"'s "+(string)ob->query_name()+" cannot possibly be planted on.");
        return 1;
    }

    if (ob->query_wielded() || ob->query_worn()) {
        notify_fail("Remove the item before trying to plant it.\n");
        return 0;
    }

    results = THIEVERY_D->initiate_thievery(TP, victim, ob);
    thief_roll = results["thief_roll"];
    victim_roll = results["victim_roll"];

    if (victim_roll < thief_roll) {
        write("You successfully plant "+ob->query_name()+" on "+victim->query_cap_name()+".\nYou are not sure if anyone noticed.");
        if (ob->move(victim)) {
            write(victim->query_cap_name()+" cannot carry that!\nThe plant fails.");
        }
        THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP, ob);
        if (interactive(victim)) log_file("player/theft", TPQN+"("+TP->query_level()+") planted "+ob->query_short()+" on "+victim->query_name()+"("+victim->query_lowest_level()+") on "+ctime(time())+"\n");
        return 1;

    } else {
        write("You fail to plant the "+ob->query_name()+" on "+victim->query_cap_name()+", but you are unsure if it went unnoticed.");
        THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP, ob);
        return 1;
    }

}

void help() {
    write(
"
%^CYAN%^NAME%^RESET%^

plant - plant something

%^CYAN%^SYNOPSIS%^RESET%^

plant %^ORANGE%^%^ULINE%^ITEM%^RESET%^ on %^ORANGE%^%^ULINE%^TARGET%^RESET%^

%^CYAN%^DESCRIPTION%^RESET%^

Plant gives a thief the ability to stealthily plant an item on another person. Sometimes the victim or others might notice, or sometimes no one will notice at all. It all depends on your ability to steal, the lighting, and other factors.

%^CYAN%^SEE ALSO%^RESET%^

stealth, give, spy, steal, pp, pkilling
");
}
