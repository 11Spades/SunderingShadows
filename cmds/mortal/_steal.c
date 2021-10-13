#include <std.h>
#define THIEVERY_D "/daemon/thievery_d.c"

inherit DAEMON;

int cmd_steal(string str) {
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
        notify_fail("Steal what from whom?\n");
        return 0;
    }
    if (TP->query_disable()) {
        write("You are still finishing a previous attempt.");
        return 1;
    }
    if (sscanf(str, "%s from %s", what, whom) != 2) {
        notify_fail("Steal what from whom?\n");
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
    if (ETP->query_property("no steal")) {
        notify_fail("A magic force prevents you from doing that!\n");
        return 0;
    }
    if (victim->query_property("no steal")) {
        notify_fail((string)victim->query_cap_name()+" cannot be stolen from!\n");
        return 0;
    }
    if (!TP->ok_to_kill(victim)) return notify_fail("Super natural forces prevent you.\n");
    if ((victim->is_player()) && (!victim->ok_to_kill(TP))){
        write("You cannot steal with a NoPK flag\n");
        return 1;
    }
    if (wizardp(victim)) {
        tell_object(victim,TPQCN+" just tried to steal from you... break "+TP->query_possessive()+" arms.\n");
        notify_fail(victim->query_cap_name()+" is going to hurt you when "+victim->query_subjective()+" gets this message.\n");
        return 0;
    }

    if(victim == TP) {
        notify_fail("Steal from yourself?\n");
        return 0;
    }

    if (TP->light_blind(-1)) {
        notify_fail(TP->light_blind_fail_message(TP->light_blind(-1))+"\n");
        return 0;
    }

    ob = present(what, victim);

    if(victim->query_property("shapeshifted"))
    {
        if((!ob->id("kitxyz")) && (!ob->id("band")) )
        {
            tell_object(TP,victim->QCN+" doesn't have that.");
            return 1;
        }
    }

    if (!ob) {
        inv = all_inventory(victim);
        if (sscanf(what, "%s %d", what, which) != 2) {
            notify_fail(capitalize(whom)+" does not have that!\n");
            return 0;
        }
        for (i=0, skip=0; i<sizeof(inv) && !ob; i++) {
            if (inv[i]->id(what)) {
                skip ++;
                if (skip == which) ob = inv[i];
            }
        }
        if (!ob) {
            notify_fail(capitalize(whom)+" does not have that!\n");
            return 0;
        }
    }
    if (!ob->get()) {
        notify_fail("You cannot steal that!\n");
        return 0;
    }
    if (victim->query_property("hidden inventory") || ob->query_property("no steal") || ob->query_property("plot_item") || ob->query_property("soulbound")) {
        write((string)victim->query_cap_name()+"'s "+(string)ob->query_name()+" cannot possibly be stolen.");
        return 1;
    }
    if (ob->query_wielded() || ob->query_worn()) {
        notify_fail("That would be impossible!\n");
        return 0;
    }

    results = THIEVERY_D->initiate_thievery(TP, victim, ob);
    thief_roll = results["thief_roll"];
    victim_roll = results["victim_roll"];

    if (thief_roll > victim_roll) {
        write("You successfully steal "+victim->query_cap_name()+"'s "+
            ob->query_name()+".\nYou are not sure if anyone noticed.");
        if (ob->move(TP)) {
            write("You cannot carry that!\nYou drop "+ob->query_name()+".");
            say(TPQCN+" drops "+ob->query_name()+".", TP);
            ob->move(ETP);
        }
        i = THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP, ob);
        if (interactive(victim)){
            log_file("player/theft", TPQN+"("+TP->query_level()+") stole "+ob->query_short()+" from "+victim->query_name()+"("+victim->query_lowest_level()+") on "+ctime(time())+" with difficulty "+i+" at "+environment(TP)+"\n");
        }
	    else {
            log_file("stealing", TPQN+"("+TP->query_level()+") stole "+ob->query_short()+" from "+victim->query_name()+"("+victim->query_lowest_level()+") on "+ctime(time())+" with difficulty "+i+" at "+environment(TP)+"\n");
        }
        flag_stolen(ob,i);
        return 1;
    }
    else {
        write("You fail to steal "+victim->query_cap_name()+"'s "+
            ob->query_name()+", but you are unsure if it went unnoticed.");
        THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP, ob);
        return 1;
    }
}

void flag_stolen(object obj, int difficulty){
    int i;

    obj->set_property("stolen",([TPQN:(["difficulty":difficulty,"max value":obj->query_value()])]));
    if (obj->is_bag()) {
        for (i = 0;i< sizeof(all_inventory(obj));i++) {
            flag_stolen(all_inventory(obj)[i],difficulty);
        }
    }
}

void help() {
    write(
"
%^CYAN%^NAME%^RESET%^

steal - optimize someone's intentory

%^CYAN%^SYNOPSIS%^RESET%^

steal %^ORANGE%^%^ULINE%^ITEM%^RESET%^ from %^ORANGE%^%^ULINE%^TARGET%^RESET%^

%^CYAN%^DESCRIPTION%^RESET%^

This will attempt to repossess %^ORANGE%^%^ULINE%^ITEM%^RESET%^ in %^ORANGE%^%^ULINE%^TARGET%^RESET%^'s inventory into your inventory. Success of this action depends on your thievery skill, lightning condition, targets perception and some other factors. Stolen item will be marked as such and can be then fenced out at thieves guild for guild credits, or sold for money.

%^CYAN%^SEE ALSO%^RESET%^

thievery, perception, skills, pp, glance, spy, thief, stab, stealth
"
        );
}
