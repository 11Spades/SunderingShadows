// Chernobog (8/26/22)
// Yniam - Ambiance

#include <std.h>
#include <daemons.h>
inherit MONSTER;

void create(){
    ::create();
    set_name("ambiance device");
    set_id(({"ambiance device"}));
    set_short("");
    set_long("");
    add_limb("body", "", 0, 0, 0);
    set_property("no detect", 1);
    set_invis();
    set_emotes(3,({
        "%^CRST%^%^RESET%^%^CRST%^%^RESET%^%^C081%^A %^C087%^gl%^C159%^a%^C087%^ssy-ey%^C159%^e%^C087%^d%^RESET%^%^C081%^ young man meanders by, a %^C153%^merry s%^C147%^o%^C153%^ng%^C081%^ on his lips.%^CRST%^",
        "%^CRST%^%^RESET%^%^C105%^An %^C099%^elated giggle%^C105%^ comes from deeper in the %^C103%^fields%^C105%^.%^CRST%^",
        "%^CRST%^%^RESET%^%^C144%^A small group of revelers up the way %^C138%^philosophize%^C144%^ about life as they pass around a %^C143%^small pipe%^RESET%^%^C144%^.%^CRST%^",
        "%^CRST%^%^RESET%^%^C070%^The pungent scent of %^C040%^burning herbs%^C070%^ wafts through the air.%^CRST%^",
        "%^CRST%^%^RESET%^%^C145%^A %^C144%^naked couple%^C145%^ runs past, %^C139%^laughing%^C145%^ as they chase each other into the %^C137%^fields%^RESET%^%^C145%^.%^CRST%^",
        "%^CRST%^%^RESET%^%^C073%^Passing a bottle of %^C101%^whiskey%^C073%^ back and forth, a pair of %^C072%^farmers%^C073%^ make their way past.%^CRST%^",
        "%^CRST%^%^RESET%^%^C102%^Birds%^C182%^ take flight as cries of %^C090%^sheer ecstasy%^RESET%^%^C182%^ trill out over the plains.%^CRST%^",
        "%^CRST%^%^RESET%^%^C097%^Music plays from somewhere, the %^C103%^mellow flow%^C097%^ compelling you to move.%^CRST%^",
        "%^CRST%^%^RESET%^%^C137%^A nearly nude %^C138%^large breasted woman%^C137%^ twirls by with her arms swaying, %^C139%^dancing%^C137%^ to her own beat.%^CRST%^",
        "%^CRST%^%^RESET%^%^C101%^The enticing %^C100%^earthy scent%^C101%^ of %^C107%^hashish%^RESET%^%^C101%^ drifts by in %^C108%^hazy clouds%^C101%^ of %^C102%^smoke%^C101%^.%^CRST%^",
        "%^CRST%^%^RESET%^%^C146%^Echoes of %^C140%^distant laughter%^C146%^ carry from the nearby plains.%^CRST%^",
        "%^CRST%^%^RESET%^%^C250%^The %^C187%^feverish clucks%^C250%^ of a %^C255%^chicken%^C250%^ ring out as it %^C188%^scurries%^RESET%^%^C250%^ past, %^C255%^f%^C250%^e%^C255%^athe%^C250%^r%^C255%^s%^RESET%^%^C250%^ scattering in its wake.%^CRST%^",}), 0);
}

void set_invis(){
    if(this_object()->query_invis()) return;
    else ::set_invis();
    return;
}

void die(object ob){}
int do_damage(string str, int i){ return 0;}
int is_invincible(){ return 1;}
int is_detectable(){ return 0;}
