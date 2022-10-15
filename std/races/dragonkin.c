#include <std.h>
inherit DAEMON;

void create()
{
    ::create();
}

// age at which each age cat starts: normal, middle, old, venerable
int* age_brackets()
{
    return ({ 20, 82, 116, 200 });
}

int* restricted_alignments(string subrace)
{
    return ({  });
}

string* restricted_classes(string subrace)
{
    return ({  });
}

string *restricted_deities(string subrace) {
    return ({  });
}

// stats in order: str, dex, con, int, wis, cha
int* stat_mods(string subrace)
{
    return ({ 2, -2, 0, 0, 0, 2 });
}

mapping skill_mods(string subrace)
{
    return ([ "influence" : 2 ]);
}

int natural_AC(string subrace)
{
    return 2;
}

int sight_bonus(string subrace)
{
    return 2;
}

mapping daily_uses(string subrace)   // needs charm person if possible down the track
{
    return ([ ]);
}

int misc_bonuses(string subrace, string bonus)
{
    return 0;
}

// ---------------------------------------------------------------------------------------------------
// Below: mods prior to racial overhaul; some may still be in use in some places. -N, 10/10.

// stats in order: str, dex, con, int, wis, cha
int* min_stats()
{
    return ({ 12, 7, 8, 8, 3, 2 });
}

int* max_stats()
{
    return ({ 19, 18, 14, 17, 16, 14 });
}

int* stat_adj()
{
    return ({ 0, 0, 0, 0, 0, 0 });
}

int is_restricted()
{
    return 1;
}                                 // restricted races by approval

int is_rollable() { return 0; } // rollable in creation

int is_pk_race()
{
    return 0;
}

// Stuff needed to replace what was in the old race database

string race_name()
{
    return "dragonkin";
}

// gets used in a forumla based on con to determine actual weight
int weight()
{
    return 11000;
}

int fingers()
{
    return 5;
}

mapping query_racial_innate(string subrace)
{
    return ([ ]);
}

string* wielding_limbs()
{
    return ({ "right hand", "left hand" });
}

mapping monster_stat_rolls()
{
    return ([ "str" : 1, "con" : 1, "int" : -1, "wis" : 0, "dex" : 0, "cha" : -1 ]);
}

int size()
{
    return 2;
}

string* limbs()
{
    return ({ "head",
                "right arm",
                "right hand",
                "left arm",
                "left hand",
                "left leg",
                "left foot",
                "right leg",
                "right foot",
                "waist",
                "neck" });
}

// minimum height for the race = base, max height for the race = base + mod
int height_base(string gender)
{
    return 65;
}

int height_mod(string gender)
{
    return 12;
}

// minimum weight for the race = base, max weight for the race = base + (modifier x height mod)
// height mod = player height minus base height.
int weight_base(string gender)
{
    return 200;
}

int weight_mod(string gender)
{
    return 8;
}

// used by /daemon/player_d
mapping weight_values(string gender, int height)
{
    mapping map=([]);

    map["num"]  = 8;

    switch(gender)
    {
    case "male":
        map["base"] = 150;
        switch(height)
        {
        case 60..65: map["adjust"] = -40; map["die"] = 15; break;
        case 66..74: map["adjust"] = -10; map["die"] = 10; break;
        case 75..80: map["adjust"] = 20;  map["die"] = 15; break;
        case 81..86: map["adjust"] = 30;  map["die"] = 25; break;
        default:     map["adjust"] = 0;   map["die"] = 10; break;
        }
    default:
        map["base"] = 110;
        switch(height)
        {
        case 55..60: map["adjust"] = -10; map["die"] = 14; break;
        case 61..69: map["adjust"] = -5;  map["die"] = 10; break;
        case 70..75: map["adjust"] = 0;   map["die"] = 15; break;
        case 76..81: map["adjust"] = 15;  map["die"] = 15; break;
        default:     map["adjust"] = 0;   map["die"] = 10; break;
        }
    }

    return map;
}

string *query_hair_colors(string who) { return ({"bald"}); }

string *query_eye_colors(string subrace) {
    string *choices = ({});
    choices += ({"sapphire","azure","cyan","emerald"});
    choices += ({"green","blue"});
    return choices;
}

string *query_subraces(object who) {
    return ({"flame", "wind", "wave", "stone"});
}

string* query_languages(string subrace)
{
    switch(subrace)
    {
        case "stone":
        return ([ "required" : ({ "common", "draconic" }), "optional" : ({ "terran", "dwarvish", "undercommon", "drow", "elven", "abyssal" }) ]);
        break;
        case "flame":
        return ([ "required" : ({ "common", "draconic" }), "optional" : ({ "ignan", "infernal", "undercommon", "elven", "orcish" "goblin" }) ]);
        break;
        case "wind":
        return ([ "required" : ({ "common", "draconic" }), "optional" : ({ "auran", "undercommon", "elven", "celestial", "halfling", "gnomish" }) ]);
        break;
        case "wave":
        return ([ "required" : ({ "common", "draconic" }), "optional" : ({ "aquan", "undercommon", "elven", "yuan-ti", "aklo", "gnomish" }) ]);
        break;
        default:
        return ([ "required" : ({ "common", "draconic" }), "optional" : ({ "dwarvish", "elven", "gnomish", "orcish", "goblin" }) ]);
        break;
    }
}
