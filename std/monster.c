/**
 * @file
 * @brief This is base inherit for all monsters
 */
 
 /*
   Reference of notable functions:
   
   set_monster_feats(array feats)                             - adds feats to the monster
   start_walking(string filename)                             - begins the mob walking to destination filename using pathfinder daemon
   query_walking()                                            - am I walking?
   set_charmed(int x)                                         - sets whether the mob is charmd (1), normal (0), or offended (-1)
   set_interaction_normal(string* action, string* func_name)  - these change add_actions based on offended, normal, charmed
   set_interaction_charmed(string* action, string* func_name)
   set_interaction_offended(string* action, string* func_name)
   set_spells(array spells)                                   - creates a list of spells the monster can cast
   get_random_spell()                                         - gives you a random spell from the monster's spell list 
   set_spell_chance(int percent)                              - percentage chance on any round that mob casts a spell   
   
*/

#define PATHFINDER "/daemon/pathfinder_d.c"  // added by Lujke, September 2005
#define LIGHT_MAX_RANGE 5

#include <std.h>
#include <move.h>
#include <objects.h>
#include <daemons.h>
#include <new_exp_table.h>
#include <rooms.h>
#include <security.h>

inherit "/std/weaponless_users.c"; // consolidating all weaponless combat into one spot -Ares
       
nosave mapping emotes,
        spells,
        thief_skill,
        charmed_int,
        offend_int,
        norm_int;

nosave int speed,      //Movement speed
           steal,
           no_catch_tell,
           charmed,
           func_chance,
           max_level,
           level,
           is_walking,
           will_open,
           will_avoid_traps,
           static_bab,
           hit_dice,
           hit_dice_bonus,
           stage,
           useMonsterFlag,
           is_npc,
           npc,
           ticker,
           already_listened,
           init_pause,
           swarm,
           heart_beat_on,
           no_moving,  //I guess this is a movement override
           moving;     //Are we moving?
           
nosave string destination,
              body_type,
              *monster_feats,
              *path,
              *funcs,
              *nogolist;
              
nosave object master_wiz;

//Prototyping
void set_body_type(string x);
void set_exp(int x);
void set_level(int x);
int query_level();
void move_around();
void set_emotes(int x, string* arr, int att);
int do_exp(int dice, int bonus);
int query_thief_skill(string skill);
void steal_fun();
void set_interaction_normal(string* action, string* func_name);
void set_interaction_charmed(string* action, string* func_name);
void set_interaction_offended(string* action, string* func_name);
int check_action(string str);
int npc_mon(int npc, object wizard);
int force_NPC(string command);
void disable_catch_tell(int def_tell);
void start_walking(string dest);  // These functions added by Lujke, September 2005
void stop_walking();                // to support the code for monsters
void reach_destination();         // to be able to find their way to a
void do_walk();                   // specified destination
int query_walking();            //
void will_open_doors(int num); // Will make wandering mobs open unlocked doors in their way -Ares 09/18/05
void avoid_traps(int num); // Will make wandering mobs avoid walking into exits that are trapped -Ares 09/18/05
void do_kit_stuff();
void die(object ob);
int query_exp_needed(int level);
void set_new_exp(int level, string perc); // new lib level exp function, see function definition for more details -Ares
void set_mob_magic_resistance(string perc);

//Variable manipulation functions
int set_use_monster_flag(int x) {  return (useMonsterFlag = x);                   }
int set_static_bab(int bab)     {  return (static_bab = bab);                     }
int run()                       {  return (is_walking = 3);                       }
int hurry()                     {  return (is_walking = 2);                       }  
int set_no_moving()             {  return (no_moving = 1);                        }
int set_moving(int x)           {  return (moving = x);                           }
int set_speed(int x)            {  return (speed = x);                            }

int query_static_bab()          {  return static_bab;                             }
int is_monster()                {  return 1;                                      }
int query_is_npc()              {  return is_npc;                                 }
int query_no_moving()           {  return no_moving;                              }
int query_moving()              {  return moving;                                 }
int query_speed()               {  return speed;                                  }

string *set_nogo(string *list)  {  return (nogolist = list);                      }

string query_sphere()           {  return "monster sphere";                       }
string query_vis_cap_name()     {  return query_cap_name();                       }
string getNameAsSeen(object ob) {  return this_object()->query_name();            }
string getParsableName()        {  return capitalize(this_object()->query_name());}
string *query_nogo()            {  return (pointerp(nogolist) ? nogolist : ({})); }

//Monster Spell Funcs
int set_spell_chance(int x)
{
    if(!mapp(spells))
        spells = ([  ]);

    return (spells["chance"] = x);
}

string *set_spells(string* arr)
{ 
    if(!mapp(spells))
        spells = ([  ]);
    
    return (spells["commands"] = arr);
}

int query_spell_chance() { return  mapp(spells) ? spells["chance"] : 0; }
string* query_spells() { return mapp(spells) ? spells["commands"] : 0; }
//End Monster Spell Funcs

//Some kind of masking here?
void set_languages(string* stuff) {  }
string *query_mini_quests() { return ({  }); }
string *query_quests() { return ({  }); }
string *query_temporary_feats() { return ({  }); }
                                             
void create()
{
    ::create();
    enable_commands();
    seteuid(getuid(this_object()));
    init_limb_data();
    init_stats();
    init_skills(0);
    init_max_hp();
    init_living();
    set_heart_beat(heart_beat_on = 1);
    speed = 0;
    set_gender("neuter");
    set_gender("male");
    set_alignment(5);
    enable_commands();
    is_npc = 0;
    no_catch_tell = 0;
    emotes = ([]);
    spells = ([]);
    thief_skill = ([]);
    norm_int = ([]);
    charmed_int = ([]);
    offend_int = ([]);
    stage = 60;
    path = ({});
    monster_feats = ({});
    set_sight_bonus(1);
    if (objectp(TO)) {
        catch("/daemon/quests"->isMon(TO));
    }
    ticker = 0;
}

void reset()
{
    if (!objectp(TO)) {
        return;
    }
    catch("/daemon/quests"->isMon(TO));
    if (!objectp(ETO)) {
        return;
    }
    ::reset();
}

void set_monster_feats(string* feats)
{
    string* valid_feats, * feats_check;
    int i;

    if (!pointerp(feats)) {
        return;
    }
    feats_check = get_dir(DIR_FEATS + "/");
    valid_feats = ({});
    //tell_object(find_player("saide"), "feats_check = "+identify(feats_check));
    foreach(string tmp in feats_check)
    {
        valid_feats += get_dir(DIR_FEATS + "/" + tmp + "/");
        continue;
    }
    //valid_feats = get_dir("/cmds/feats/");


    for (i = 0; i < sizeof(valid_feats); i++) {
        valid_feats[i] = replace_string(valid_feats[i], "_", "", 1);
        valid_feats[i] = replace_string(valid_feats[i], "_", " ");
        valid_feats[i] = replace_string(valid_feats[i], ".c", "");
    }
    for (i = 0; i < sizeof(feats); i++) {
        if (member_array(feats[i], valid_feats) == -1) {
            continue;
        }
        monster_feats += ({ feats[i] });
    }
    //builds a list of combat usable feats - Saide
    MONSTER_FEAT_D->init_combat_feats(TO);
}

string* query_monster_feats()
{
    return monster_feats;
}

private void check_heart_beat()
{
    if(!query_heart_beat(this_object()))
    {
        calculate_healing();
        set_heart_beat(heart_beat_on = 1);
    }
    call_out("check_heart_beat", 18);
}

int set_heart_beat(int flag)
{
    return efun::set_heart_beat((__COMBAT_SPEED__)*flag);

    return efun::set_heart_beat(flag);
}

int query_heart_status()
{
    return heart_beat_on;
}

void check_encounter(object player)
{
    object *dudes;
    object env = environment(this_object());
    string *temp = ({  });
    mixed aggro;
    
    if(!env) return;
    if(!objectp(player)) return;
    
    if(!find_call_out("check_heart_beat"))
        check_heart_beat();
    
    if(userp(player))
    {
        if(aggro = query("aggressive"))
        {
            if(!player->query_invis() || query_property("invis attack"))
            {
                if(intp(aggro) && aggro > (int)player->query_stats("charisma"))
                {
                    kill_ob(player);
                    kill_msg(player);
                }
                else
                {
                    if(stringp(aggro) && function_exists(aggro, this_object()))
                        call_other(this_object(), aggro);
                }
            }
        }
    }
                    
    if (norm_int)
    {
        temp += keys(norm_int);
        if (charmed_int)
            temp += keys(charmed_int);
        if (offend_int)
            temp += keys(offend_int);
        temp = distinct_array(temp);
        
        for (int i = 0; i < sizeof(temp); i++)
            add_action("check_action", temp[i], 1);
    }
}   

//Looking at this. Init function needs to have a delay to prevent insane recursion situations.
void init()
{   
    if(!objectp(this_object())) return;
    if(!environment()) return;
    if(base_name(environment()) == ROOM_VOID) return;
    if(!objectp(this_player())) return;
    if(this_player()->query_true_invis()) return;
    if(this_player()->query_ghost()) return;
    if(this_player()->query_property("draggee")) return;
    
    if(!userp(this_player()))
    {
        if(init_pause)
            return;
        else
            init_pause = 1;
    }
    
    if(eval_cost() < 50000)
        return;
    
    ::init();

    check_encounter(this_player());
}

void kill_msg(object tp)
{
    //tell_object(tp, "%^RED%^%^BOLD%^" + capitalize(this_object()->query_name()) + " attacks you!%^RESET%^");
    message("monster", "%^RED%^%^BOLD%^" + capitalize(this_object()->query_name()) + " attacks you!%^RESET%^", environment(tp), tp); 
}

object make_corpse()
{
    object tmp;
    tmp = new(OB_CORPSE);
    tmp->set_name(capitalize(query_name()));
    tmp->copy_body(this_object());
    return tmp;
}

void set_name(string str)
{
    set_living_name(str);
    ::set_name(str);
    if (query_level() < 1) {
        set_level(1);
    }
}

void do_kit_stuff()
{
    int num, level, hp, max_hp, diff, avg, i;
    string type;
    object ob;

    if (!objectp(TO)) {
        return;
    }

    num = (int)TO->query_property("add kits");
    if (!present("kitxyz", TO) && num == -1) {
        return;
    }
    if (!num) {
        return;
    }

    level = (int)TO->query_level();
    switch (level) {
    case 0..11:
        type = "/d/common/obj/potion/healing.c";
        avg = 11;
        break;

    case 12..24:
        type = "/d/common/obj/potion/extra_heal.c";
        avg = 20;
        break;

    case 25..34:
        type = "/d/common/obj/potion/advanced_heal.c";
        avg = 30;
        break;

    default:
        type = "/d/common/obj/potion/legendary_heal.c";
        avg = 50;
        break;
    }
    if (!present("kitxyz", TO) && num != -1) {
        ob = new(type);
        ob->set_uses(num);
        ob->move(TO);
        TO->remove_property("add kits");
        TO->set_property("add kits", -1);
    }

    if (!present("kitxyz", TO)) {
        return;
    }

    hp = (int)TO->query_hp();
    max_hp = (int)TO->query_max_hp();

    if (hp >= max_hp) {
        return;
    }

    diff = max_hp - hp;
    diff = diff / avg;
    if (diff > 4) {
        diff = 4;
    }
    if (diff) {
        for (i = 0; i < diff; i++) {
            force_me("drink kitxyz");
        }
    }
    return;
}

//Will be a call out to check this and keep it going.
//Will be a check in init in case call_out stops.
void heart_beat()
{
    object room;
    mixed error;
    
    if(!objectp(this_object()))
        return;
    
    room = environment(this_object());
    
    if(!objectp(room))
        return;
    
    ::heart_beat();
    
    already_listened = 0;
    init_pause = 0;
    ticker++;
    
    //Come back and check on this timing
     do_healing(calculate_healing());
    
    if(this_object()->query_current_attacker())
    {
        error = catch(iterate_combat());
        ok_to_attack() && continue_attack();
        error = catch(do_kit_stuff());
    }
    
    //We check again in case the combat stuff above killed the monster (ie: counterattacks)
    if(!objectp(this_object()) || !objectp(room))
        return;
    
    if(speed && moving >= speed)
    {
        if(!is_walking)
            move_around();
    }
    else
        moving++;
    
    steal && !random(50) && steal_fun();
    if(sizeof(query_attackers()) && query("protecting"))
        delete("protecting");
}

//Take this out after testing
object* ob_party(object ob)
{
    object* party;
    string party_name;

    if (!objectp(TO) || !objectp(ob)) {
        return ({ ob });
    }
    party_name = ob->query_party();
    if (!party_name) {
        return ({ ob });
    }
    party = PARTY_D->query_party_members(party_name);
    return party;
}

//General clean up of function and removal of unused code. -- Tlaloc -- 2022
//Actual XP giving is done in combat_d in check_death().
void die(object killer)
{
    object *killers, *my_stuff;
    object room, corpse, money;
    string quest_str, quest_exp;
    string *curr;
    
    if(!objectp(this_object()))
        return;
    
    room = environment(this_object());
    
    if(!objectp(room))
        return;
    
    if(!query_property("new_exp_set"))
        set_new_exp(this_object()->query_highest_level(), "normal");
    
    message("death", "%^RED%^" + this_object()->query_cap_name() + " drops dead before you.%^RESET%^", room, this_object());
    
    if(room->query_property("arena"))
    {
        destall(this_object());
        return;
    }
    
    killers = all_living(room);
    killers = filter_array(killers, (: userp($1) :));
    quest_str = query_property("add quest");
    quest_exp = query_property("quest exp");
    quest_str && !quest_exp && quest_exp = query_level() * 1000;
    
    foreach(object ob in killers)
    {
        if(strlen(quest_str))
        {
            if(member_array(quest_str, ob->query_mini_quests()) >= 0)
                continue;
            else
                ob->set_mini_quest(quest_str, quest_exp, quest_str);
        }
    }
    
    //Can make monsters with no corpse
    if(!this_object()->query_property("no corpse"))
    {
        if(objectp(corpse = make_corpse()))
            corpse->move(environment(this_object()));
    }
    
    my_stuff = all_inventory(this_object());
    
    foreach(object ob in my_stuff)
    {
        if(!objectp(ob))
            continue;
     
        if(ob->query_property("monsterweapon") || !ob->query_short())
        {
            destruct(ob);
            continue;
        }
        
        if(objectp(corpse))
            ob->move(corpse);
        else
        {
            catch(ob->remove());
            objectp(ob) && destruct(ob);
        }
    }
    
    if(objectp(corpse) && has_value())
    {
        money = new("/std/obj/coins");
        curr = query_currencies();
        
        foreach(string str in curr)
        {
            if(!query_money(str))
                continue;
            
            money->add_money(str, query_money(str));
            add_money(str, -query_money(str));
        }
    
        money->has_value() && money->move(corpse);
    }
    
    if(this_object()->query_property("death effects"))
        catch(load_object("/daemon/death_effects_d")->get_death_effect(this_object()));
    
    set_heart_beat(heart_beat_on = 0);
    
    if(catch(this_object()->remove()) || (objectp(this_object()) && !this_object()->remove()))
        this_object()->move(ROOM_VOID);
    objectp(this_object()) && destruct(this_object());
    
    return;
}

int query_npc()
{
    return 1;
}

varargs void move_player(mixed dest, string msg)
{
    object prev, * inv;
    string here, going, temp1, temp2, temp3;
    int i, bzbd;

    if (!objectp(this_object())) {
        return;
    }
    if (!objectp(prev = ETO)) {
        return;
    }
    here = file_name(prev);
    if (stringp(dest)) {
        if (sscanf(dest, "/%s", temp1) != 1) {
            sscanf(here, "/%s", temp1);
            going = "";
            while (sscanf(temp1, "%s/%s", temp2, temp3) == 2) {
                going = going + "/" + temp2;
                temp1 = temp3;
            }
            temp1 = dest;
            if (file_size(going + "/" + temp1 + ".c") != -1) {
                dest = going + "/" + temp1;
            }
        }
    }
    if (move(dest) == MOVE_OK) {
        if (query_property("posed")) {
            remove_property("posed");
        }
        if (!id("summoned monster") || id("greater summon")) {
            if (!hiddenp(this_object()) && !(avatarp(TO) && query_invis())) {
                inv = all_inventory(prev);
                for (i = 0, bzbd = sizeof(inv); i < bzbd; i++) {
                    if (!living(inv[i]) || inv[i] == this_object()) {
                        continue;
                    }
                    if (query_magic_hidden() && !inv[i]->detecting_invis()) {
                        continue;
                    }
                    if (query_hidden()) {
                        continue;
                    }
                    if (!msg || msg == "") {
                        message("mmout", query_mmout(inv[i]), inv[i]);
                    }else {
                        if (TO->query_in_vehicle() && objectp(TO->query_in_vehicle())) {
                            message("mout", query_cap_name() + " rides " + TO->query_in_vehicle()->query_cap_name() + " " + msg + ".", inv[i]);
                        } else {
                            message("mout", query_mout(msg, inv[i]), inv[i]);
                        }
                    }
                }
                if (!objectp(TO) || !objectp(ETO)) {
                    return;
                }
                // If something's fucked up, don't even bother trying.
                inv = all_inventory(environment(this_object()));
                for (i = 0, bzbd = sizeof(inv); i < bzbd; i++) {
                    if (!living(inv[i])) {
                        continue;
                    }
                    if (inv[i] == this_object()) {
                        continue;
                    }

                    if (query_magic_hidden() && !inv[i]->detecting_invis()) {
                        continue;
                    }
                    if (query_hidden()) {
                        continue;
                    }
                    if (!msg || msg == "") {
                        message("mmin", query_mmin(inv[i]), inv[i]);
                    }else {
                        if (TO->query_in_vehicle() && objectp(TO->query_in_vehicle())) {
                            message("min", query_cap_name() + " enters riding " + TO->query_in_vehicle()->query_cap_name() + ".", inv[i]);
                        } else {
                            message("min", query_min(inv[i]), inv[i]);
                        }
                    }
                }
            }
        }
        if (query_followers()) {
            move_followers(prev);
        }
    }
}

/* Call_out taken out of move_around by Hanse 1/4/93 */
// *changes to respect files in restricted exit list (nogo) by Styx 8/2003
// Added in checks for locked and unlocked doors, and the ability to open
// unlocked ones -Ares 09/18/05
void move_around()
{
    string* exits, door;
    string exit, exitfile;  // *added local exitfile variable for use below

    if (!TO) {
        return;
    }
    if (!objectp(ETO)) {
        return;
    }
    if (no_moving) {
        return;
    }
    ETO->setupExits();
    if (query_current_attacker()) {
        return;
    }
    if (ETO) {
        exits = (string*)ETO->query_obvious_exits();
    }else {
        exits = 0;
    }
    if (sizeof(exits)) {
        exit = exits[random(sizeof(exits))];
        exitfile = (string)ETO->query_exit(exit);      // *need this to check below
        if (door = ETO->query_door(exit)) {
            if (member_array(exitfile, query_nogo()) != -1) {
                return;
            }
            if (ETO->query_locked(door)) {
                return;
            }
            if (!ETO->query_open(door) && !will_open) {
                return;
            }
            if (will_open) {
                command("open " + door);
            }
        }
        if (will_avoid_traps && ETO->query_trap_status(exit, exit)) {
            return;
        }
        if (member_array(exitfile, query_nogo()) == -1) { // *if it's not in the array, go ahead
            seteuid(UID_ROOT);
            if (objectp(find_object_or_load(exitfile))) {
                exitfile->init();
                if (exit != "temple") {
                    command(exit);
                }
            }
        }
    }
    moving = 0;
}

string query_title()
{
    return query_short();
}

void __SHINIT()
{
    enable_commands();
    seteuid(getuid(this_object()));
    init_limb_data();
    init_stats();
    init_skills(0);
    init_max_hp();
    init_living();
    set_heart_beat(heart_beat_on = 1);
    speed = 0;
    set_gender("neuter");
}

void set_hd(int dice, int bonus)
{
    int conbonus;
    hit_dice = dice;
    hit_dice_bonus = bonus;
    if (!query_classes() || query_classes() == ({})) {
        set_class("fighter");
    }
    set_level(dice);
    conbonus = (int)(query_stats("constitution") - 10) / 2;
    set_max_hp(roll_dice(dice, 12) + bonus + (dice * conbonus));
    set_hp(query_max_hp());
}

void do_exp(int dice, int bonus)
{
    if (bonus > 0) {
        dice++;
    }
    if (bonus < 0) {
        dice--;
    }
    if (dice < 1) {
        dice = 1;
    }
    if (dice > 13) {
        dice -= 13;
        set_exp((2000 + (dice * 200)));
        return;
    }
    switch (dice) {
    case 1:  set_exp(15);  return;

    case 2:  set_exp(35);  return;

    case 3:  set_exp(65);  return;

    case 4:  set_exp(120); return;

    case 5:  set_exp(120); return;

    case 6:  set_exp(175); return;

    case 7:  set_exp(270); return;

    case 8:  set_exp(390); return;

    case 9:  set_exp(500); return;

    case 10: set_exp(850); return;

    case 11: set_exp(960); return;

    case 12: set_exp(1150); return;

    case 13: set_exp(1250); return;

    default: set_exp(15);   return;
    }
}

int query_hd_bonus()
{
    return hit_dice_bonus;
}

int query_hd()
{
    return hit_dice;
}

void set_level(int x)
{
    level = x;
    set_hp(query_max_hp());
    set_stats("constitution", x * 3 / 2);
    set_stats("strength", x * 3 / 2);
    set_stats("intelligence", x * 3 / 2);
    set_stats("wisdom", x * 3 / 2);
    set_stats("dexterity", x * 3 / 2);
    set_stats("charisma", x * 3 / 2);
    set_max_mp((query_stats("intelligence") / 2) * x);
    set_mp(query_max_mp());
    set_mlevel(TO->query_class(), TO->query_level());
    if (!query_static_bab()) {
        static_bab = (int)TO->query_level();
    }
}

int query_level()
{
    level = query_highest_level();
    if (level == 0) {
        return TO->query_hd();
    }
    return level;
}

// Added by Valodin, June 28, 1993
// Sets the body type to a certain race using the race daemon
void set_race(string str)
{
    ::set_race(str);
    if (!body_type) {
        set_body_type(str);
    }
}

void set_body_type(string str)
{
    mapping monster_bod;
    string* mon_limbs;
    int i, max;

    if (!str || !RACE_D->is_monster_race(str)) {
        str = "human";
    }
    init_limb_data();

    monster_bod = (mapping)RACE_D->monster_body(str, query_max_hp());

    for (i = 0, max = sizeof(mon_limbs = keys(monster_bod)); i < max; i++) {
        add_limb(mon_limbs[i], monster_bod[mon_limbs[i]]["limb_ref"],
                 monster_bod[mon_limbs[i]]["max_dam"], 0, 0);
    }

    set_wielding_limbs((string*)RACE_D->query_monster_wielding_limbs(str));
    if (objectp(TO)) {
        TO->set_fingers((int)RACE_D->query_monster_fingers(str));

        // from weaponless_monsters.c
        TO->set_attack_limbs((string*)RACE_D->query_monster_wielding_limbs(str));
        TO->set_attacks_num(sizeof(TO->query_attack_limbs()));
    }

    body_type = str;
}

string query_body_type()
{
    if (body_type) {
        return body_type;
    }else {
        return query_race();
    }
}

void set_func_chance(int x)
{
    if (!funcs) {
        funcs = ({});
    }
    func_chance = x;
}

void set_funcs(string* arr)
{
    //changing this so that funcs can be changed - for fights
    //with phases or whatever - Saide
    //if(!funcs || funcs == ({})) funcs = arr;
    if (pointerp(arr)) {
        funcs = arr;
    }
}

int query_func_chance()
{
    if (funcs) {
        return func_chance;
    }
    return 0;
}

string* query_funcs()
{
    if (funcs) {
        return funcs;
    }
    return 0;
}

string get_random_func()
{
    if (!funcs) {
        return 0;
    }
    if (sizeof(funcs) < 2) {
        return funcs[0];
    }
    return funcs[random(sizeof(funcs))];
}

string get_random_spell()
{
    if (!spells) {
        return 0;
    }
    if (sizeof(spells["commands"]) < 2) {
        return spells["commands"][0];
    }
    return spells["commands"][random(sizeof(spells["commands"]))];
}

// These two functions remain for backwards Nightmare 1.* and 2.* compat

void set_chats(int x, string* arr)
{
    set_emotes(x, arr, 0);
}

void set_achats(int x, string* arr)
{
    set_emotes(x, arr, 1);
}

void set_emotes(int x, string* arr, int att)
{
    emotes[(att ? "attack chance" : "chance")] = x;
    emotes[(att ? "attack msg" : "msg")] = arr;
}

void set_alignment(int x)
{
    player_data["general"]["alignment"] = x;
}

void receive_message(string cl, string msg)
{
    string str1, str2;
    
    if(this_player() == this_object())
        return;
    
    if(!userp(this_player()))
        return;
    
    if(already_listened)
        return;
    
    already_listened = 1;
    
    if(is_npc)
    {
        if(userp(master_wiz))
            tell_object(master_wiz, "%%% " + msg + "\n");
        else
        {
            npc = 0;
            return;
        }
    }
    
    if(!no_catch_tell)
        this_object()->catch_tell(msg);
    
    if(cl == "say")
    {
        if(sscanf(msg, "%s:%s", str1, str2) != 2)
            sscanf(msg, "%s :%s", str1, str2);
        this_object()->catch_say(str2);
    }
}

//thief monsters
void set_thief_skill(string skill, int score)
{
    thief_skill[skill] = score;
}

int query_thief_skill(string skill)
{
    return thief_skill[skill];
}

void toggle_steal()
{
    if (!steal) {
        add_search_path("/cmds/mortal");
        steal = 1;
        return;
    }
    if (steal == 1) {
        steal = 0;
    }
}

int is_stealer()
{
    if (steal) {
        return 1;
    }
    return 0;
}

void steal_fun()
{
    string what;
    object who;
    object* items;
    int coin;
    int inven;

    who = "/daemon/find_target_d"->find_player_target(TO);
    if (who == TO) {
        return 1;
    }
    coin = random(2);
    if (coin == 0) {
        what = "money";
    }else {
        what = "item";
    }
    if (what == "money") {
        TO->force_me("pp " + who->query_name());
    }else {
        items = all_inventory(who);
        if (items == ({})) {
            return 1;
        }
        inven = random(sizeof(items));
        TO->force_me("steal " + items[inven]->query_name() + " from " + who->query_name());
    }
}

// this function flags the monster as charmed or uncharmed or offended
// thus the values to be used are:
//         charmed = 1
//         normal = 0
//         offended = -1

void set_charmed(int num)
{
    set_property("charmed", num);
    return;
}

void set_interaction_normal(string* action, string* func_name)
{
    int i;

    if ((!action) || (!func_name) || (sizeof(action) != sizeof(func_name))) {
        return;
    }
    if (!norm_int) {
        norm_int = ([]);
    }
    i = sizeof(action);
    while (i--) {
        norm_int[action[i]] = func_name[i];
    }
}

void set_interaction_charmed(string* action, string* func_name)
{
    int i;

    if ((!action) || (!func_name) || (sizeof(action) != sizeof(func_name))) {
        return;
    }
    if (!charmed_int) {
        charmed_int = ([]);
    }
    i = sizeof(action);
    while (i--) {
        charmed_int[action[i]] = func_name[i];
    }
}

void set_interaction_offended(string* action, string* func_name)
{
    int i;

    if ((!action) || (!func_name) || (sizeof(action) != sizeof(func_name))) {
        return;
    }
    if (!offend_int) {
        offend_int = ([]);
    }
    i = sizeof(action);
    while (i--) {
        offend_int[action[i]] = func_name[i];
    }
}

int check_action(string str)
{
    int charm, num;
    string verb;
    function temp;

    temp = 0;
    verb = query_verb();
    charm = (int)query_property("charmed");
    if (!norm_int[verb]) {
        norm_int[verb] = "function_default";
    }
    switch (charm) {
    case 1: if (charmed_int[verb]) {
            temp = (: call_other, TO, charmed_int[verb] :);
    }else {
            temp = (: call_other, TO, norm_int[verb] :);
    }
        break;

    case 0: temp = (: call_other, TO, norm_int[verb] :);
        break;

    case -1: if (!offend_int[verb]) {
            temp = (: call_other, TO, norm_int[verb] :);
    }else {
            temp = (: call_other, TO, offend_int[verb] :);
    }
        break;
    }
    if (temp == 0) {
        return 0;
    }
    num = (*temp)(str);
    return num;
}

int npc_mon(int npc, object wizard)
{
// added check for valid object to stop bugs *Styx*  3/17/03
    if (!objectp(wizard)) {
        return 0;
    }
    if (!avatarp(wizard)) {
        return 0;
    }
    if (is_npc == 1 && npc == 1) {
        return 0;
    }
    if (npc != 1 && npc != 0) {
        return 0;
    }
    if (!interactive(wizard)) {
        return 0;
    }
    master_wiz = wizard;
    is_npc = npc;
    return 1;
}

int force_NPC(string command)
{
    return this_object()->force_me(command);
}

void disable_catch_tell(int def_tell)
{
    no_catch_tell = def_tell;
}

void set_max_level(int lvl)
{
    max_level = lvl;
    if (intp(TO->query_highest_level())) {
        if (max_level < ((int)TO->query_highest_level() + 6)) {
            max_level = ((int)TO->query_highest_level() + 6);
        }
    }
}

int query_max_level()
{
    return max_level;
}

string query_short()
{
    string descr = ::query_short();
    if (query_unconscious() || query_bound() || query_tripped() || query_gagged()) {
        descr = descr + " (";
        if (query_unconscious()) {
            descr = descr + "unconscious ";
        }
        if (query_bound()) {
            descr = descr + "bound ";
        }
        if (query_tripped()) {
            descr = descr + "prone ";
        }
        if (query_gagged()) {
            descr = descr + "gagged ";
        }
        if (query_blindfolded()) {
            descr = descr + "blindfolded";
        }
        descr = descr + ")";
    }
    if (query_property("posed")) {
        descr = descr + " [" + query_property("posed") + "]";
    }
    return descr;
}

void saveMonster(string path)
{
    if (!stringp(path)) {
        path = base_name(TO);
    }
    seteuid(getuid());
    "/daemon/yuck_d"->save_inventory(this_object(), path);
    save_me(path);
}

void restoreMonster(string path)
{
    seteuid(getuid());
    if (!stringp(path)) {
        path = base_name(TO);
    }

    if (!file_exists(path + ".o")) {
        return;
    }
    restore_me(path);
    "/daemon/yuck_d"->load_inventory(this_object(), path);
}

void clearMonster(string path)
{
    string* oldfiles;
    int x;

    seteuid(getuid());

    if (!stringp(path)) {
        path = base_name(TO);
    }

    if (!file_exists(path + ".o")) {
        return;
    }
    rm(path + ".o");

    oldfiles = get_dir(path + "/");
    for (x = 0; x < sizeof(oldfiles); x++) {
        rm(path + "/" + oldfiles[x]);
    }
}

string query_destination()
{
    return destination;
}

/**
 * This function moves the mob along the path towards the destination,
 * if the is_walking variable has been set to 1
 */
varargs void do_walk(int iteration)
{
    string* finalpath, step, door;
    object startroom, endroom, * rooms;

    rooms = ({});
    finalpath = ({});

    if (!objectp(TO) || !objectp(ETO)) {
        stop_walking();
        return;
    }

    if (is_walking == 0 || !stringp(destination)) {
        return;
    }
    if (file_name(ETO) == destination) {
// changed this from a waystation check that wasn't working Lujke September 16 2005
        reach_destination();
        stop_walking();
        return;
    }

    startroom = ETO; // already done an objectp check on ETO

// If there is no path already set, find a the nearest waystation
// if the mob is not already at one. Otherwise, find the next
// waystation nearest the destination.

    if (path == ({})) {
        endroom = PATHFINDER->find_waystation(startroom, destination, 5);
//    endroom = PATHFINDER->find_waystation(startroom, destination, 5);

        if (!objectp(endroom)) {
            force_me("emote Looks around, as if unsure which way to go.");
            is_walking = 0;
            destination = "";
            return;
        }
        path = PATHFINDER->findpath(startroom, endroom, path, finalpath, rooms, 5, 1);

        if (path == ({})) {
            stop_walking();
            return;
        }
    }
// Once the path is found, or if one was already set, take the next step along it
    step = path[0];
//Addition by Lujke December 2016. If the mob is set with the 'sneaking' property
//make it sneak
    if (query_property("sneaking") == 1) {
        step = "sneak " + step;
    }
// additions by *Styx* 2/1/06
    if (will_open) {
        if (door = ETO->query_door(path[0])) {
            if (ETO->query_locked(door)) {
                stop_walking();
                return;
            }
            if (!ETO->query_open(door)) {
                command("open " + door);
            }
        }
    }
    force_me(step);

// After the mob has taken the next step along the path, check whether it
// has reached its destination and then trigger the appropriate
// function if it has.  Then remove the step that has just been completed
// from the remaining path array.

    if (objectp(ETO)) {
        if (file_name(ETO) == destination) {
            // This will mean that the mob has reached the destination
            stop_walking();
            reach_destination();
            return;
        }
    }else {
        force_me("say my environment is invalid");
    }

    // after walking, remove that step from the 'path' array
    if (sizeof(path) > 1) {
        path = path[1..(sizeof(path) - 1)];
    }else {
        path = ({});
    }
    if (iteration < 1) {
        switch (is_walking) {
        case 3:
            do_walk(1);

        case 2: //deliberately falling through
            call_out("do_walk", 1, 1);

        case 1:
            call_out("do_walk", 3, 0);
        }
    }
}

int* query_walking()
{
    //allows other object to check whether the monster is on the move
    return is_walking;
}

void reach_destination()
{
    // a virtual function, triggered when the mob gets to where it is going
}

/**
 * Starts the mob walking towards its destination.
 *
 * @param dest should be the filename of the destination room, without
 * the ".c" - i.e, exactly what is returned by
 * file_name(<destination>) The destination MUST have been set up with
 * waypoints, using the destinations_d.c daemon.
 */
void start_walking(string dest)
{
    destination = dest;
    is_walking = 1;
    call_out("do_walk", 1);
}

void stop_walking()
{
    // this function stops the mob from walking.
    is_walking = 0;
    destination = "";
}

void will_open_doors(int num)
{
    will_open = num;
    return;
}

void avoid_traps(int num)
{
    will_avoid_traps = num;
    return;
}

int query_exp_needed(int level)
{
    int exp;
    exp = total_exp_for_level(level);
    return exp;
}

/**
 * Automatically Sets monster exp based on exp needed towards next level
 *
 * @param level optional, monster level
 * @param perc optional, "very low" "low" "normal" "high" "very high" "boss",
 *        defaults to "normal", percentile based exp level
 */
varargs int set_new_exp(int level, string perc)
{
    int exp, div;

    if (!intp(level) || level < 1) {
        level = (int)TO->query_level();
        if (level < (int)TO->query_highest_level()) {
            level = (int)TO->query_highest_level();
        }
    }

    if (!stringp(perc) || perc == "" || perc == " ") {
        perc = "normal";
    }

    perc = lower_case(perc);

    switch (perc) {
    case "very low":
        div = 70;
        break;

    case "low":
        div = 85;
        break;

    case "normal":
        div = 100;
        break;

    case "high":
        div = 115;
        break;

    case "very high":
        div = 130;
        break;

    case "boss":
        div = 300;
        break;

    default:
        perc = "normal";
        break;
    }

    if (level == 0) {
        level = 1;
    }
    if (level > 100) {
        level = 100; exp = 300000000;
    } else {
        /*
           Fit data:
           [75,1],[1000,10],[75000,50]
         */
        exp = (90078000 * level * level - 180156000 * level + 378646100) / 2885681;
    }

    if (perc != "normal") {
        exp = (exp * div) / 100;
    }

    TO->set_property("new_exp_set", 1);
    TO->set_property("new_exp_amount", exp);
    TO->set_property("new_exp_level", level);
    TO->set_property("new_exp_perc", perc);
    TO->set_exp(exp);
    return exp;
}

void set_mob_magic_resistance(string perc)
{
    int base_level, modifier;

    base_level = TO->query_highest_level();
    base_level = base_level > 50 ? 50 : base_level;

    if (!stringp(perc) || perc == "" || perc == " ") {
        perc = "average";
    }


    perc = lower_case(perc);

    switch (perc) {
    case "none":
        modifier = base_level * 0;
        break;

    case "extremely low":
        //modifier = base_level * 10;
        modifier = 1;
        break;

    case "very low":
        //modifier = base_level * 80 / 100;
        modifier = 2;
        break;

    case "low":
        //modifier = base_level * 90 / 100;
        modifier = 3;
        break;

    case "average":
        //modifier = base_level;
        modifier = 5;
        break;

    case "high":
        //modifier = base_level * 105 / 100;
        modifier = 7;
        break;

    case "very high":
        //modifier = base_level * 110 / 100;
        modifier = 9;
        break;

    case "extremely high":
        //modifier = base_level * 125 / 100;
        modifier = 11;
        break;

    case "insanely high":
        //modifier = base_level * 150 / 100;
        modifier = 13;
        break;
    case "immune":
        modifier = 100;
        break;
    default:
        modifier = 0;
        break;
    }
    
    TO->set_property("magic resistance", modifier);
}

int move(mixed dest)
{
    if (!objectp(TO)) {
        return ::move(dest);
    }
    if (!TO->query_property("new_exp_set")) {
        if (TO->query_property("minion")) {
            TO->set_new_exp(1, "normal");
            TO->set_property("new_exp_set", 1);
        }else {
            TO->set_new_exp((int)TO->query_highest_level(), "normal");
            TO->set_property("new_exp_set", 1);
        }
    }

    if (!TO->query_property("has_random_treasure") && !TO->query_property("no_random_treasure")) {
        "/daemon/random_monster_treasure_d.c"->assign_treasure(TO);
    }
    return ::move(dest);
}

void mon_look(){
    string dsc;
    dsc = ETO->query_short();
    tell_object(TP, dsc);
    return;
}

int light_blind_remote(int actionbonus, object whichroom, int distance) {

  int _total_light;
  int _sight_bonus;
  int calc;

  if (!objectp(this_object())) {
      return 0;
  }
  if (!objectp(whichroom)) {
      return 0;
  }
  if (whichroom->query_property("ooc_room")) {
      return 0;
  }
  if (whichroom->query_property("ooc room")) {
      return 0;
  }
  if (geteuid(whichroom) == "Shadowgate") {
      return 0;
  }
  _total_light = total_light(whichroom);
  _sight_bonus = query_sight_bonus();

  if (!D_BUG_D->user_new_light()) {
      return (_total_light + _sight_bonus - actionbonus < 0);
  }

  if (_sight_bonus * _total_light < 0) {
      calc = _sight_bonus + _total_light;
  }else {
      calc = _total_light;
  }
  if (D_BUG_D->calc_message()) {
      tell_object(this_object(), "calc = " + calc);
  }

  if (member_array(query_race(), PLAYER_D->night_races()) != -1) {
      calc *= -1;
      _total_light *= -1;
  }

  if (intp(actionbonus)) {
      if (calc > (0 + actionbonus)) {
          if (_total_light < (LIGHT_MAX_RANGE - actionbonus)) {
              // proper light!
              return 0;
          } else {
              //      tell_object(TO,"first return");
              return (_total_light - (LIGHT_MAX_RANGE - actionbonus));
          }
      } else {
          //      tell_object(TO,"second return");
          return calc - actionbonus;
      }
  } else {
      //      tell_object(TO,"second if");
      if (calc > 0) {
          if (_total_light < LIGHT_MAX_RANGE) {
              return 0;
          }else {
              return (_total_light - LIGHT_MAX_RANGE);
          }
      }else {
          return (calc - 0);
      }
  }
  tell_object(this_object(), "Light error!");
  return 0;
}

int light_blind(int actionbonus)
{
    object room;

    if (!objectp(this_object()))
        return 0;

    room = environment(this_object());

    if (!objectp(room))
        return 0;

    return light_blind_remote(actionbonus, room, 0);
}
