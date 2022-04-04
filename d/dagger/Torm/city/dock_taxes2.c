//room for tax collector for the Torm crime syndicate.
//Circe 7/12/04
// Chernobog (4/4/22)
// Updated for quest

#include <std.h>
#include "/d/dagger/Torm/tormdefs.h"
#include <daemons.h>
#define LEVELS ({"low","medium","high"})

inherit ROOM;

int tax1, tax2, tax3, padlock_locked, cabinet_locked;

void create(){
    ::create();
    set_terrain(CITY);
    set_travel(DIRT_ROAD);
    set_property("light",2);
    set_name("A Large Office on the Boardwalk");
    set_short("%^RESET%^%^CRST%^%^C130%^A Large Office on the Boardwalk%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C130%^A Large Office on the Boardwalk.%^CRST%^\n%^RESET%^%^CRST%^%^C136%^This office stands on the lower boardwalk looking out over the Dagger Sea. The office is tidy, with a simple wooden desk and chair in the southern part of the room, leaving enough space for sailors to travel between the two doors. A locked cabinet stands in the southwestern corner, and numerous papers and folios are on the desk. It seems that all business must pass through this office, day or night. A ladder just outside the western door leads to the upper boardwalk. The office opens up to the east, and through the far doorway, you can see the Dagger Sea. A %^C226%^%^small sign %^C136%^is posted on the wall behind the desk for you to read.%^CRST%^\n");
    set_smell("default","You smell salt in the air from the Dagger Sea.");
    set_listen("default","The waves of the sea wash against the docks.");
    set_items(([
        ({"sea","dagger sea","Dagger Sea"}) : "%^RESET%^%^CRST%^%^C039%^The vast Dagger Sea stretches far out into the distance. It is a %^C027%^dark blue %^C039%^and you can hear the %^C045%^wa%^C051%^ves %^C045%^brea%^C051%^king %^C039%^against the city walls and docks.%^CRST%^",
        "fog" : "%^RESET%^%^CRST%^%^C244%^A light layer of %^C250%^fog %^C244%^covers the entire bay, spilling off from the ocean into the city streets. During the early years of the city, it was probably a wonderful protection against pirates and others who might normally want to attack at night, for the fog hides all the dangerous rocks and most ships trying to dock would be smashed to pieces. Now it simply limits trade to the daytime hours, and probably brings in a lot of business for the inns in the city, with everyone forced to stay here at night.%^CRST%^",
        "spires" : "%^RESET%^%^CRST%^%^C244%^To the west you can see Torm's spires stretching into the sky.%^CRST%^",
        "ships" : "%^RESET%^%^CRST%^%^C039%^There are many %^C136%^wooden ships %^C039%^around, all of them appear fairly sturdy though there are several different styles from various distant lands. This is obviously a bustling %^C027%^sea port %^C039%^that draws business from many places.%^CRST%^",
        ({"birds","small birds"}) : "%^RESET%^%^CRST%^%^C250%^There are several %^C255%^small birds %^C250%^about, either dozing or trying to get a bit of food that a sailor might have left behind.%^CRST%^",
        ({"desk","wooden desk","chair"}) : "%^RESET%^%^CRST%^%^C136%^The %^C130%^wooden desk %^C136%^and chair are well-made, if small. The desk has been covered with %^C250%^writing implements%^C136%^, %^C059%^ink%^C136%^, and %^C144%^papers %^C136%^that contain columns of numbers and names.%^CRST%^",
        ({"papers","folios","ink","implements"}) : "%^RESET%^%^CRST%^%^C136%^Many of the %^C144%^papers %^C136%^are in closed folios, but what you can see seems to be columns of numbers and names, though they make little sense. They are obviously records of some kind. A large %^C059%^ink pot %^C136%^with several %^C250%^quills %^C136%^rests on the desk, just waiting to be used for another entry.%^CRST%^",
        ({"cabinet","wooden cabinet","storage cabinet","locked cabinet"}) : (:this_object(),"look_cabinet":),
        ({"sign","small sign"}) : ({"%^RESET%^%^CRST%^%^C214%^This is a small %^C226%^brass sign %^C214%^that you could read.%^CRST%^",(:this_object(),"read_sign":),"common"})
        ]));
    set_exits(([
        "up" : TCITY+"c70",
        "east" : TCITY+"dock_taxes"
    ]));
    set_pre_exit_functions(({"east"}),({"Pay_taxes"}));
    padlock_locked = 1;
    cabinet_locked = 1;
}

void reset(){
    object guard;
    
    ::reset();
    if(!present("torm guard")){
        guard = new(MON"guard");
        guard->move(this_object());
        guard->set_speed(0);
    }
    if(!present("torm tax collector")) new(MON"tax_collector2")->move(this_object());
    padlock_locked = 1;
    cabinet_locked = 1;
}

void init(){
    ::init();
    add_action("add_em", "add");
    add_action("remove_em", "remove");
    add_action("query_em", "query");
    add_action("check_em", "check");
    add_action("pay_em", "pay");
    add_action("pick_fun", "pick");
    add_action("smash_fun", "smash");
}

void look_cabinet(){
    object player;
    player = this_player();
    
    tell_object(player, "%^RESET%^%^CRST%^%^C136%^This large %^C130%^wooden cabinet %^C136%^has several %^C244%^ir%^C248%^o%^C244%^n loc%^C248%^k%^C244%^s %^C136%^built into it, as well as being sealed with a large %^RESET%^%^C244%^p%^C246%^a%^C248%^d%^C244%^l%^C246%^o%^C248%^c%^C244%^k%^RESET%^%^C136%^. There is no hint as to what might be inside.%^CRST%^");
    if(player->query("wailing isle quest") == 5) tell_object(player, "\n%^RESET%^%^CRST%^%^C144%^This appears to be the cabinet that Mister Brookes referenced. It could be possible to pick the cabinet... or perhaps smash it open?%^CRST%^");
    return;
}

int smash_fun(string str){
    object player, room, guard, taxes;
    string playername;
    
    if(!str) return 0;
    if(str != "cabinet") return 0;
    
    player = this_player();
    room = this_object();
    playername = player->query_cap_name();
    
    if(!padlock_locked && !cabinet_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C124%^Looks like someone already beat you to it. The locks are %^C059%^disabled %^C124%^and the cabinet has been %^C196%^plundered%^C124%^.%^CRST%^");
        return 1;
    }
    
    if(padlock_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C108%^Pulling and twisting at the %^C243%^p%^C245%^a%^C247%^dlo%^C245%^c%^C243%^k%^RESET%^%^C108%^, you eventually manage to pry it from the cabinet and let it fall to the floor.%^CRST%^\n");
        tell_room(room, "%^RESET%^%^CRST%^%^C108%^Pulling and twisting at the %^C243%^p%^C245%^a%^C247%^dlo%^C245%^c%^C243%^k%^RESET%^%^C108%^, "+playername+"%^RESET%^%^CRST%^%^C108%^ eventually manages to pry it from the cabinet and let it fall to the floor.%^CRST%^\n", player);
        padlock_locked = 0;
        if(present("torm guard")){ 
            tell_room(room, "%^RESET%^%^CRST%^%^C196%^The guard and tax collector give each other an incredulous look before drawing weapons and sounding the alarm!%^CRST%^");
            guard = new(MON"guard");
            guard->move(room);
            guard->force_me("kill "+player->query_name()+"");
            guard = new(MON"guard");
            guard->move(room);
            guard->force_me("kill "+player->query_name()+"");
        }
        return 1;
    }
    if(cabinet_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C108%^You slam into the cabinet, over and over... and the doors slowly cave before falling open, completely ruined. Inside are several shelves of %^C144%^files %^C108%^and %^C144%^bundled papers%^C108%^.%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ slams into the cabinet, over and over... and the doors slowly cave before falling open, completely ruined. Inside are several shelves of %^C144%^files %^C108%^and %^C144%^bundled papers%^C108%^.%^CRST%^", player);
        cabinet_locked = 0;
        if(player->query("wailing isle quest") == 5){
            tell_object(player, "%^RESET%^%^CRST%^%^C108%^The files that Mister Brookes mentioned catch your eye and you grab them up quickly. The rest of the paperwork doesn't look useful at all.%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ grabs up a few files.%^CRST%^", player);
            taxes = new("/realms/chernobog/areas/wailing_isle/obj/taxes");
            taxes->move(player);
            player->set("wailing isle quest", 6);
        }
        else{
            tell_object(player, "%^RESET%^%^CRST%^%^C059%^None of this paperwork looks useful at all.%^CRST%^\n");
        }
        tell_room(room, "%^RESET%^%^CRST%^%^C196%^The noise rings out through the office, attracting the attention of a couple guards who come running into the room!%^CRST%^");
        guard = new(MON"guard");
        guard->move(room);
        guard->force_me("kill "+player->query_name()+"");
        guard = new(MON"guard");
        guard->move(room);
        guard->force_me("kill "+player->query_name()+"");
    }
    return 1;
}

int pick_fun(string str){
    object player, room, guard, lockpicks;
    string playername;
    
    if(!str) return 0;
    if(str != "cabinet") return 0;
    
    player = this_player();
    room = this_object();
    playername = player->query_cap_name();
    
    if(!objectp(lockpicks = present("thief toolx", player))){
        tell_object(player, "You might need some tools for this.");
        return 1;
    }
    if(!padlock_locked && !cabinet_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C124%^Looks like someone already beat you to it. The locks are %^C059%^disabled %^C124%^and the cabinet has been %^C196%^plundered%^C124%^.%^CRST%^");
        return 1;
    }
    
    if(padlock_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C108%^You kneel down and start working at the %^C243%^p%^C245%^a%^C247%^dlo%^C245%^c%^C243%^k %^RESET%^%^C108%^on the cabinet.%^CRST%^\n");
        player->set_property("picking cabinet", 1);
        if(!player->query_hidden() && !player->query_magic_hidden()){
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ kneels down and starts working at the %^C243%^p%^C245%^a%^C247%^dlo%^C245%^c%^C243%^k%^RESET%^%^C108%^ on the cabinet.%^CRST%^", player);
            if(present("torm guard")){ 
                tell_room(room, "%^RESET%^%^CRST%^%^C196%^The guard and tax collector give each other an incredulous look before drawing weapons and sounding the alarm!%^CRST%^");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
            }
        }
        call_out("pick_padlock", 3, room, player, lockpicks, playername);
    }
    if(!padlock_locked && cabinet_locked){
        tell_object(player, "%^RESET%^%^CRST%^%^C108%^You kneel down and start working at the %^C243%^b%^C245%^u%^C247%^ilt-%^C245%^i%^C243%^n l%^C245%^o%^C247%^c%^C245%^k%^C243%^s %^RESET%^%^C108%^of the cabinet.%^CRST%^\n");
        player->set_property("picking cabinet", 1);
        if(!player->query_hidden() && !player->query_magic_hidden()){
            tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ kneels down and starts working at the %^C243%^b%^C245%^u%^C247%^ilt-%^C245%^i%^C243%^n l%^C245%^o%^C247%^c%^C245%^k%^C243%^s %^RESET%^%^C108%^of the cabinet.%^CRST%^", player);
            if(present("torm guard")){
                tell_room(room, "%^RESET%^%^CRST%^%^C196%^The guard and tax collector give each other an incredulous look before drawing weapons and sounding the alarm!%^CRST%^");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
            }
        }
        
        call_out("pick_cabinet", 3, room, player, lockpicks, playername);
    }
    input_to("stop_picking", player);
    return 1;
}

void pick_padlock(object room, object player, object lockpicks, string playername){
    int skill, success;
    object guard;
    
    if(!player->query_property("picking cabinet")) return 1;

    skill = player->query_skill("dungeoneering");
    success = ((roll_dice(1, 20) + skill) - 40);
    if(!success){
        if(success < -10){
            tell_object(player, "%^RESET%^%^CRST%^%^C124%^The padlock resists your skills, going as far as ruining your lockpicks!%^CRST%^\n");
            lockpicks->break_picks();
            tell_room(room, "%^RESET%^%^CRST%^%^C124%^"+playername+"%^RESET%^%^CRST%^%^C124%^ lets out a whispered curse.%^CRST%^", player);
            if(present("torm guard")){
                tell_room(room, "%^RESET%^%^CRST%^%^C196%^The guard and tax collector look around for the source of the noise before drawing weapons and sounding the alarm!%^CRST%^");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
            }
        }
        else{
            tell_object(player, "%^RESET%^%^CRST%^%^C124%^The padlock refuses to open!%^CRST%^\n");
        }
        stop_picking(0, player);
        return;
    }
    tell_object(player, "%^RESET%^%^CRST%^%^C108%^The %^C243%^p%^C245%^a%^C247%^dlo%^C245%^c%^C243%^k %^RESET%^%^C108%^relents to your skill, and you quietly set it aside before turning your attention to the %^C243%^b%^C245%^u%^C247%^ilt-%^C245%^i%^C243%^n l%^C245%^o%^C247%^c%^C245%^k%^C243%^s %^RESET%^%^C108%^of the cabinet.%^CRST%^\n");
    padlock_locked = 0;
    call_out("pick_cabinet", 3, room, player, lockpicks, playername);
    return;
}

void pick_cabinet(object room, object player, object lockpicks, string playername){
    int skill, success;
    object guard;
    
    if(!player->query_property("picking cabinet")) return 1;
    
    skill = player->query_skill("dungeoneering");
    success = ((skill + roll_dice(1, 20)) - 50);
    if(!success){
        if(success < -10){
            tell_object(player, "%^RESET%^%^CRST%^%^C124%^The cabinet locks resist your skills, going as far as ruining your lockpicks!%^CRST%^\n");
            lockpicks->break_picks();
            tell_room(room, "%^RESET%^%^CRST%^%^C124%^"+playername+"%^RESET%^%^CRST%^%^C124%^ lets out a whispered curse.%^CRST%^", player);
            if(present("torm guard")){
                tell_room(room, "%^RESET%^%^CRST%^%^C196%^The guard and tax collector look around for the source of the noise before drawing weapons and sounding the alarm!%^CRST%^");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
                guard = new(MON"guard");
                guard->move(room);
                guard->force_me("kill "+player->query_name()+"");
            }
        }
        tell_object(player, "%^RESET%^%^CRST%^%^C124%^The cabinet locks refuse to release.%^CRST%^");
        stop_picking(0, player);
        return;
    }
    tell_object(player, "%^RESET%^%^CRST%^%^C108%^The cabinet locks release with a barely audible *click*. You open it up to reveal several shelves of %^C144%^files %^C108%^and %^C144%^bundled papers%^C108%^.%^CRST%^\n");
    tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ opens the cabinet, revealing several shelves of %^C144%^files %^C108%^and %^C144%^bundled papers%^C108%^.%^CRST%^", player);
    cabinet_locked = 0;
    if(player->query("wailing isle quest") == 5){
        tell_object(player, "%^RESET%^%^CRST%^%^C108%^The files that Mister Brookes mentioned catch your eye and you grab them up quickly. The rest of the paperwork doesn't look useful at all.%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C108%^"+playername+"%^RESET%^%^CRST%^%^C108%^ grabs up a few files.%^CRST%^", player);
        new("/realms/chernobog/areas/wailing_isle/obj/taxes")->move(player);
        player->set("wailing isle quest", 6);
        player->remove_property("picking cabinet");
        return;
    }
    tell_object(player, "%^RESET%^%^CRST%^%^C059%^None of this paperwork looks useful at all.%^CRST%^");
    player->remove_property("picking cabinet");
    stop_picking(0, player);
    return;
}

void stop_picking(string str, object player){
    if(!player->query_property("picking cabinet")) return;
    tell_object(player, "%^RESET%^%^CRST%^%^C059%^You stop your work on the cabinet locks.%^CRST%^");
    player->remove_property("picking cabinet");
    return;
}

void read_sign(){
    write(
@CIRCE
%^BOLD%^%^GREEN%^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       %^BLUE%^Torm Tax Collector's Office

%^WHITE%^Here, taxes are collected for the city of 
Torm.  You may wish to <check status> to 
see whether or not you will be charged taxes.
If you owe taxes, you will need to <pay taxes>
before you can pass.
%^GREEN%^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%^RESET%^
CIRCE
    );
    if(avatarp(TP)){
    write(
@CIRCE
Here, you may 
   <add player taxlevel>
      The tax levels are low, medium, and high, 
      charging 100, 300, and 700 gold respectively.
   <remove player>
      This will remove the player's name from the tax lists.
   <query player> of <query all>
      This will tell you if a player is being taxed and at 
      what level.  Query all returns all taxed players.
   <check killers>
      This will tell you which players have attacked the 
      tax collectors and when.
   <check cheaters>
      This will tell you which players have snuck past the 
      tax collectors and when.
%^RED%^Note%^RESET%^: Be sure to query a player and remove them 
if they are already being taxed before adding a new tax level or
you run the risk of them being taxed multiple times or causing bugs.
CIRCE
    );
    }
}

int pay_em(string str){
    string taxname;
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    if(!str){
        tell_object(TP,"You may <pay taxes> here to pass through.");
        return 1;
    }
    if(str == "taxes"){
        if(!present("torm tax collector")){
            tell_object(TP,"There is no tax collector here! It must be your lucky day.");
            return 1;
        }
        if(member_array(TPQN, tax1) != -1){
            if(present("torm tax collector")){
                taxname = present("torm tax collector")->QCN;
                if(!TP->query_funds("gold",100)){
                    tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+". It says here you owe taxes in the amount of 100 gold. You will have to return with the funds to pay it before I can let you pass.");
                    return 0;
                }
                tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Thank you for your contribution, "+TPQCN+".  It will be put to good use.");
                tell_room(TO,""+taxname+" collects some money from "+TPQCN+" and locks it quickly away in the cabinet.");
                if(present("torm guard")){
                    tell_object(TO,"The guard steps out of the way and lets "+TPQCN+" pass.");
                }
                TP->set_property("paid taxes",1);
                TP->use_funds("gold",100);
                return 1;
            }
            return 1;
        }
        if(member_array(TPQN, tax2) != -1){
            if(present("torm tax collector")){
                taxname = present("torm tax collector")->QCN;
                if(!TP->query_funds("gold",300)){
                    tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+". It says here you owe taxes in the amount of 300 gold. You will have to return with the funds to pay it before I can let you pass.");
                    return 0;
                }
                tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Thank you for your contribution, "+TPQCN+". It will be put to good use.");
                tell_room(TO,""+taxname+" collects some money from "+TPQCN+" and locks it quickly away in the cabinet.");
                if(present("torm guard")){
                    tell_object(TO,"The guard steps out of the way and lets "+TPQCN+" pass.");
                }
                TP->set_property("paid taxes",1);
                TP->use_funds("gold",300);
                return 1;
            }
            return 1;
        }
        if(member_array(TPQN, tax3) != -1){
            if(present("torm tax collector")){
                taxname = present("torm tax collector")->QCN;
                if(!TP->query_funds("gold",700)){
                    tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+". It says here you owe taxes in the amount of 700 gold. You will have to return with the funds to pay it before I can let you pass.");
                    return 0;
                }
                tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Thank you for your contribution, "+TPQCN+". It will be put to good use.");
                tell_room(TO,""+taxname+" collects some money from "+TPQCN+" and locks it quickly away in the cabinet.");
                if(present("torm guard")){
                    tell_object(TO,"The guard steps out of the way and lets "+TPQCN+" pass.");
                }
                TP->set_property("paid taxes",1);
                TP->use_funds("gold",700);
                return 1;
            }
            return 1;
        }
    }
    tell_object(TP,"You may <pay taxes> here if you owe them.");
    return 1;
}

int add_em(string str){
    string player,level;
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    if(!avatarp(TP)) return 0;
    if(!str){
        tell_object(TP,"Try <add playername taxlevel>");
        return 1;
    }
    if(sscanf(str,"%s %s",player,level) != 2){
        tell_object(TP,"Try <add playername taxlevel>");
        return 1;
    }
    player = lower_case(player);
    if(!user_exists(player)){
        tell_object(TP,"%^RED%^Error: %^RESET%^Player %^YELLOW%^"+capitalize(player)+" %^RESET%^does not exist!");
        return 1;
    }
    if(member_array(level,LEVELS) == -1){
        tell_object(TP,"That is not a valid level.  Try low, medium, or high.");
        return 1;
    }
    switch(level){
        case "low":  
            if(member_array(player, tax1) != -1) return notify_fail("Player "+capitalize(player)+" is already on the low tax list.\n");
            SAVE_D->set_value("Torm_taxes_low", player);
            tell_object(TP,"Player "+capitalize(player)+" added to the %^YELLOW%^low %^RESET%^tax list.");
            break;
        case "medium":  
            if(member_array(player, tax2) != -1) return notify_fail("Player "+capitalize(player)+" is already on the medium tax list.\n");
            SAVE_D->set_value("Torm_taxes_med", player);
            tell_object(TP,"Player "+capitalize(player)+" added to the %^ORANGE%^medium %^RESET%^tax list.");
            break;
        case "high":  
            if(member_array(player, tax2) != -1) return notify_fail("Player "+capitalize(player)+" is already on the high tax list.\n");
            SAVE_D->set_value("Torm_taxes_high", player);
            tell_object(TP,"Player "+capitalize(player)+" added to the %^BOLD%^%^RED%^high %^RESET%^tax list.");
            break;
    }
    return 1;
}

int remove_em(string str){
    string player,level;
    int low,med,high;
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    if(!avatarp(TP)) return 0;
    if(!str){
        tell_object(TP,"Try <remove playername>");
        return 1;
    }
    str = lower_case(str);
    if(!user_exists(str)){
        tell_object(TP,"%^RED%^Error: %^RESET%^Player %^YELLOW%^"+str+" %^RESET%^does not exist!");
        return 1;
    }
    if(member_array(str, tax1) != -1){
        low = 1;
    }
    if(member_array(str, tax2) != -1){
        med = 1;
    }
    if(member_array(str, tax3) != -1){
        high = 1;
    }
    if(!low && !med && !high){
        tell_object(TP,"Player "+capitalize(str)+" not found on any tax list.");
        return 1;
    }
    if(member_array(str, tax1) != -1){
        SAVE_D->remove_name_from_array("Torm_taxes_low",str);
        tell_object(TP,"Player "+capitalize(str)+" was removed from the %^YELLOW%^low %^RESET%^tax list.");
    }
    if(member_array(str, tax2) != -1){
        SAVE_D->remove_name_from_array("Torm_taxes_med",str);
        tell_object(TP,"Player "+capitalize(str)+" was removed from the %^ORANGE%^medium %^RESET%^tax list.");
    }
    if(member_array(str, tax3) != -1){
        SAVE_D->remove_name_from_array("Torm_taxes_high",str);
        tell_object(TP,"Player "+capitalize(str)+" was removed from the %^BOLD%^%^RED%^high %^RESET%^tax list.");
        return 1;
    }
    return 1;
}

int query_em(string str){
    string player,level;
    int low,med,high,nolow,nomed,nohigh,i;
    string *names1; 
    string *names2;
    string *names3;
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    names1 = SAVE_D->query_array("Torm_taxes_low");
    names2 = SAVE_D->query_array("Torm_taxes_med");
    names3 = SAVE_D->query_array("Torm_taxes_high");
    if(!avatarp(TP)) return 0;
    if(!str){
        tell_object(TP,"Try <query playername>");
        return 1;
    }
    if(str == "all"){
        if(!sizeof(names1)){
            tell_object(TP,"There are no players on the %^YELLOW%^low %^RESET%^tax list.");
            nolow = 1;
        }
        if(!sizeof(names2)){
            tell_object(TP,"There are no players on the %^ORANGE%^medium %^RESET%^tax list.");
            nomed = 1;
        }
        if(!sizeof(names3)){
            tell_object(TP,"There are no players on the %^BOLD%^%^RED%^high %^RESET%^tax list.");
            nohigh = 1;
        }
        if(!nolow){
            tell_object(TP,"The following players are on the %^YELLOW%^low %^RESET%^tax list.");
            for(i = 0;i < sizeof(names1);i++){
                tell_object(TP,""+capitalize(names1[i])+"\n");
            }
        }
        if(!nomed){
            tell_object(TP,"The following players are on the %^ORANGE%^medium %^RESET%^tax list.");
            for(i = 0;i < sizeof(names2);i++){
                tell_object(TP,""+capitalize(names2[i])+"\n");
            }
        }
        if(!nohigh){
            tell_object(TP,"The following players are on the %^BOLD%^%^RED%^high %^RESET%^tax list.");
            for(i = 0;i < sizeof(names3);i++){
                tell_object(TP,""+capitalize(names3[i])+"\n");
            }
        }
        return 1;
    }
    str = lower_case(str);
    if(!user_exists(str)) {
        tell_object(TP,"%^RED%^Error: %^RESET%^Player %^YELLOW%^"+str+" %^RESET%^does not exist!");
        return 1;
    }
    if(member_array(str, tax1) != -1){
        low = 1;
    }
    if(member_array(str, tax2) != -1){
        med = 1;
    }
    if(member_array(str, tax3) != -1){
        high = 1;
    }
    if(!low && !med && !high){
        tell_object(TP,"Player "+capitalize(str)+" not found on any tax list.");
        return 1;
    }else{
        if(low == 1) tell_object(TP,"Player "+capitalize(str)+" found on the %^YELLOW%^low %^RESET%^tax list.");
        if(med == 1) tell_object(TP,"Player "+capitalize(str)+" found on the %^ORANGE%^medium %^RESET%^tax list.");
        if(high == 1) tell_object(TP,"Player "+capitalize(str)+" found on the %^BOLD%^%^RED%^high %^RESET%^tax list.");
        return 1;
    }
}

int check_em(string str){
    string player,level;
    int low,med,high;
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    if(!str){
        if(avatarp(TP)){
            tell_object(TP,"Try <check killers>");
            return 1;
        }
        tell_object(TP,"Try <check status>");
        return 1;
    }
    if(str == "status"){
        if(member_array(TPQN, tax1) != -1){
            low = 1;
        }
        if(member_array(TPQN, tax2) != -1){
            med = 1;
        }
        if(member_array(TPQN, tax3) != -1){
            high = 1;
        }
        if(!low && !med && !high){
            tell_object(TP,"You are not showed as owing any taxes.");
            return 1;
        }else{
            if(low == 1) tell_object(TP,"You will be charged %^YELLOW%^100 gold coins %^RESET%^in taxes for using this dock.");
            if(med == 1) tell_object(TP,"You will be charged %^YELLOW%^300 gold coins %^RESET%^in taxes for using this dock.");
            if(high == 1) tell_object(TP,"You will be charged %^YELLOW%^700 gold coins %^RESET%^in taxes for using this dock.");
            return 1;
        }
    }
    if(str == "killers"){
        if(!avatarp(TP)){
            tell_object(TP,"You cannot do that!");
            return 1;
        }
        tell_object(TP,"These are the attacks that have taken place against the tax collectors. It is up to you to decide if they were witnessed and what the consequences might be.");
        if(!file_exists("/log/reports/tormdocks")){
            tell_object(TP,"It seems there have been no attacks.");
            return 1;
        }
        TP->more("/log/reports/tormdocks");
        return 1;
    }
    if(str == "cheaters"){
        if(!avatarp(TP)){
            tell_object(TP,"You cannot do that!");
            return 1;
        }
        tell_object(TP,"These are the people who have skipped out on paying their taxes. It is up to you to decide if they were witnessed and what the consequences might be.");
        if(!file_exists("/log/reports/tormtaxes")){
            tell_object(TP,"It seems no one has tried to sneak by.");
            return 1;
        }
        TP->more("/log/reports/tormtaxes");
        return 1;
    }
    tell_object(TP,"You may <check status> here.");
    return 1;
}

int Pay_taxes(){
    string taxname;
    string myname = TPQN;
    string realname = capitalize(TP->query_true_name());
    tax1 = SAVE_D->query_array("Torm_taxes_low");
    tax2 = SAVE_D->query_array("Torm_taxes_med");
    tax3 = SAVE_D->query_array("Torm_taxes_high");
    if(!present("torm tax collector") && !present("torm guard")){
        if(member_array(myname, tax1) != -1){
            log_file("reports/tormtaxes",""+realname+" didn't pay their taxes of 100 gold. ["+ctime(time())+"].\n");
        }
        if(member_array(myname, tax2) != -1){
            log_file("reports/tormtaxes",""+realname+" didn't pay their taxes of 300 gold. ["+ctime(time())+"].\n");
        }
        if(member_array(myname, tax3) != -1){
         log_file("reports/tormtaxes",""+realname+" didn't pay their taxes of 700 gold. ["+ctime(time())+"].\n");
        }
    return 1;
    }
    if(TP->query_invis()){
        if(member_array(myname, tax1) != -1){
            log_file("reports/tormtaxes",""+realname+" didn't pay their taxes of 100 gold. ["+ctime(time())+"].\n");
        }
        if(member_array(myname, tax2) != -1){
            log_file("reports/tormtaxes",""+realname+" didn't pay their taxes of 300 gold. ["+ctime(time())+"].\n");
        }
        if(member_array(myname, tax3) != -1){
            log_file("reports/tormtaxes", ""+realname+" didn't pay their taxes of 700 gold. ["+ctime(time())+"].\n");
        }
        return 1;
    }
    if((int)TP->query_property("paid taxes") == 1){
        TP->remove_property("paid taxes");
        return 1;
    }
    if(member_array(myname, tax1) != -1){
        taxname = present("torm tax collector")->QCN;
        tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+".  It says here you owe taxes in the amount of 100 gold. You will have to return with the funds to pay it before I can let you pass.");
        return 0;
    }
    if(member_array(myname, tax2) != -1){
        taxname = present("torm tax collector")->QCN;
        tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+".  It says here you owe taxes in the amount of 300 gold. You will have to return with the funds to pay it before I can let you pass.");
        return 0;
    }
    if(member_array(myname, tax3) != -1){
        taxname = present("torm tax collector")->QCN;
        tell_room(TO,"%^MAGENTA%^"+taxname+" says%^RESET%^: Hold right there, "+TPQCN+".  It says here you owe taxes in the amount of 700 gold. You will have to return with the funds to pay it before I can let you pass.");
        return 0;
    }
    return 1;
}

