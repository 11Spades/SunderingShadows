#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit DAEMON;

int is_prestige_class() { return 0; }

void create() { ::create(); }

string *search_paths() { return ({  }); }

int caster_class() { return 1; }

string *restricted_races() {
    return ({  });
}

string *restricted_classes() { return ({ }); }

int *restricted_alignments() { return ({ }); }

string *restricted_gods() { return ({}); }

mapping stat_requirements() {
    return ([ "intelligence" : 14, ]);
}

int *saving_throws() { return ({ 1,0,1 }); }

string *combat_styles() {
    return ({});
}

string *class_feats(string myspec)
{
    return ({ "simple weapon proficiency",
                "martial weapon proficiency",
                "light armor proficiency",
                "spell focus"});
}

mapping class_featmap(string myspec) {
    return ([ 1 : class_feats()+({"arcane pool", "spell combat", "magus armor"}), 2 : ({"spellstrike"}), 4 : ({"spell recall"}), 7 : ({"medium armor proficiency"}), 10 : ({"fighter training"}), 11 : ({"improved spell recall"}), 13 : ({"heavy armor proficiency"}), 16 : ({"spell counterstrike"}), 20 : ({"legendary blade"})]);
}

string *class_skills()
{
    return ({ "perception", "athletics", "academics", "dungeoneering" });
}

int skill_points() { return 4; }

string old_save_type() { return "magus"; }

string new_save_type() { return "magus"; }

void advanced_func(object player)
{
    player->set_guild_level("magus",(int)player->query_class_level("magus"));
    return;
}

int hit_dice() { return 8; }  // hit dice rolled for hitpoints each level

int default_hitpoints() { return 4; } // hitpoints per level above level 20

string armor_allowed() { return "fighter"; }

string weapons_allowed() { return "fighter"; }

int max_stance_offensive() { return 5; }

int max_stance_defensive() { return 5; }

int attack_bonus(object player)
{
    int level,bonus;
    level = player->query_prestige_level("magus");
    bonus = (level*3) / 4;
    return bonus;
}

int number_of_attacks(object player)
{
    int num;
    if(!objectp(player)) { return 0; }
    num = "/daemon/bonus_d.c"->attack_bonus("magus", player->query_class_level("magus"), player);
    num = num / 7;
    return num;
}

string query_casting_stat(){
   return "intelligence";
}

mapping query_class_spells()
{
    return(([]));
}

void newbie_func(object who)
{
    object ob;
    if(!objectp(who)) return;
    return 1;
}

int caster_level_calcs(object player, string the_class)
{
    int level;
    if(!objectp(player)) { return 0; }
    switch(the_class)
    {
        case "magus":
        default:
            return player->query_class_level(the_class);
    }
    return 0;
}

int fighter_training(object player)
{
    int fighter_level = 0;
    if (FEATS_D->usable_feat(player, "fighter training")) {
        fighter_level += player->query_class_level("magus") / 2;
    }
    return fighter_level;
}

int spell_combat(object player)
{
    int damage_mod = 1;
    if (player->query_class_level("magus") > 7) {
        damage_mod ++;
    }
	if (player->query_class_level("magus") > 13) {
		damage_mod ++;
	}
    return damage_mod;
}