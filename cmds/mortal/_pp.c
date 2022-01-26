#include <std.h>
#define THIEVERY_D "/daemon/thievery_d.c"

inherit DAEMON;

int cmd_pp(string str) {
    mapping results;
    object victim;
    string amt_string;
    int thief_roll, victim_roll, amt;
    int platinum, gold, electrum, silver, copper;

    if (TP->query_ghost()) {
    	notify_fail("You cannot do that in your immaterial state.\n");
    	return 0;
    }
    if (TP->query_bound() || TP->query_tripped()) {
	    TP->send_paralyzed_message("info",TP);
	    return 1;
    }
    if (TP->query_disable()) {
        write("You are still finishing a previous attempt.");
        return 1;
    }
    if (!str) {
	    notify_fail("Pick whom?\n");
	    return 0;
    }
    if (TP->query_current_attacker()) {
	    notify_fail("You can't do that while in combat!\n");
	    return 0;
    }

    victim = present(str, ETP);

    if (!victim) victim = parse_objects(ETP, str);
    if (!victim) {
	    notify_fail("No "+str+" here!\n");
	    return 0;
    }
    if (!living(victim)) {
	    notify_fail(capitalize(str)+" is not a living thing!\n");
	    return 0;
    }
    if (wizardp(victim)) {
	    notify_fail("That is not adviseable.\n");
	    return 0;
    }
    if (victim->is_player() && !interactive(victim)) return 0;
    if (victim==TP) {
	    notify_fail("You cannot pick your own purse!\n");
	    return 0;
    }
    if(ETP->query_property("no steal")) {
        notify_fail("A magic force prevents you from doing that!\n");
        return 0;
    }
    if(victim->query_property("no steal")) {
        notify_fail((string)victim->query_cap_name()+" cannot be stolen from!\n");
        return 0;
    }
    if (!TP->ok_to_kill(victim)) return notify_fail("Supernatural forces prevent you.\n");
    if ((victim->is_player()) && (!victim->ok_to_kill(TP))){
        write("You cannot steal with a NoPK flag\n");
        return 1;
    }

    results = THIEVERY_D->initiate_thievery(TP, victim);
    thief_roll = results["thief_roll"];
    victim_roll = results["victim_roll"];

    if (victim_roll > thief_roll) {
	    write("You utterly fail in your attempt to pick from "+victim->query_cap_name()+".");
	    THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP);
	    return 1;
	}

	platinum = (int)victim->query_money("platinum");
	gold = (int)victim->query_money("gold");
	electrum = (int)victim->query_money("electrum");
	silver = (int)victim->query_money("silver");
	copper = (int)victim->query_money("copper");

    if (!platinum && !gold && !electrum && !silver && !copper) {
	    tell_object(TP,""+victim->query_cap_name()+" is flat broke!\n");
	    return 1;
	}

	platinum = (thief_roll*(platinum/10))/100;
	gold = (thief_roll*(gold/10))/100;
	electrum = (thief_roll*(electrum/10))/100;
	silver = (thief_roll*(silver/10))/100;
	copper = (thief_roll*(copper/10))/100;

    if (!platinum && !gold && !silver && !electrum && !copper) {
	    write("You fail to get anything from "+victim->query_cap_name()+"'s purse.");
	}
    else {
	    victim->add_money("platinum", -platinum);
	    victim->add_money("gold", -gold);
	    victim->add_money("electrum", -electrum);
	    victim->add_money("silver", -silver);
	    victim->add_money("copper", -copper);
	    TP->add_money("platinum", platinum);
	    TP->add_money("gold", gold);
	    TP->add_money("electrum", electrum);
	    TP->add_money("silver", silver);
	    TP->add_money("copper", copper);
	    write("You pick some money from "+victim->query_cap_name()+
            "'s purse.");
        amt = gold + platinum*5 + electrum/2 + silver/10 + copper/100;
        amt_string = "gold";
        if(!amt) {
            amt = electrum + silver / 5 + copper / 50;
            amt_string = "electrum";
        }
        if(!amt) {
            amt = silver + copper / 10;
            amt_string = "silver";
        }
        if(!amt) {
            amt = copper;
            amt_string = "copper";
        }

	    write("It amounts to "+amt+" "+amt_string+" in various coins.");
    }

	log_file("player/theft", TPQN+" stole "+gold+" gold from "+victim->query_name()+" on "+ctime(time())+"\n");
    THIEVERY_D->check_caught(victim_roll, victim, thief_roll, TP);
	if(TP->query("stolen money")){
	    TP->set("stolen money",(int)TP->query("stolen money")+amt);
	}
    else {
	    TP->set("stolen money",amt);
	}
	return 1;
}

void help() {
    write(
"%^CYAN%^NAME%^RESET%^

pp - pickpocket someone

%^CYAN%^SYNOPSIS%^RESET%^

pp %^ORANGE%^%^ULINE%^TARGET%^RESET%^

%^CYAN%^DESCRIPTION%^RESET%^

This command will attempt to steal some money from %^ORANGE%^%^ULINE%^TARGET%^RESET%^. If %^ORANGE%^%^ULINE%^TARGET%^RESET%^ discovers you attempt, they will be upset at you.

%^CYAN%^SEE ALSO%^RESET%^

stealth, steal, spy, look, glance, pk, pk rules, flee"
        );
}
