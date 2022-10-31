// Chernobog (3/15/22)
// Yniam Waystation - Meeting Hall

#include <std.h>
#include "../defs.h"
inherit VAULT;

int tapestry, chandelier, chairs, benches;

void create(){
    ::create();
    set_terrain(VILLAGE);
    set_travel(DIRT_ROAD);
    set_property("indoors", 1);
    set_property("light", 2);
    set_name("A meeting hall within the waystation");
    set_short("%^RESET%^%^CRST%^%^C046%^A %^C136%^meeting hall %^C046%^within the %^C144%^waystation%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C136%^Smooth timber walls frame this structure, varnished and affecting a rugged warmth in the light offered by a large %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C214%^ch%^C220%^an%^C226%^de%^C220%^li%^C214%^er %^RESET%^%^C136%^overhead. The focal point is a %^C130%^large oblong table %^C136%^near the far wall, surrounded by six wooden chairs. It is overseen by a large tapestry displayed on the wall behind, that of the %^C144%^Yniam Plains insignia %^C136%^in bold %^C046%^gre%^C040%^e%^C046%^ns %^C136%^and %^C255%^whit%^C252%^e%^C255%^s%^RESET%^%^C136%^. There are wooden banisters in place to bisect the room, with a couple rows of benches leading to the entrance.%^CRST%^\n");
    set_smell("default", "%^RESET%^%^CRST%^%^C058%^Hints of oak and varnish flit through the air.%^CRST%^");
    set_listen("default", "%^RESET%^%^CRST%^%^C202%^You can hear the occasional hiss of the %^C214%^wax c%^C220%^a%^C226%^ndl%^C220%^e%^C214%^s %^RESET%^%^C202%^overhead.%^CRST%^");
    set_items(([
        ({"chandelier", "candles"}) : "%^RESET%^%^CRST%^%^C130%^A circle of %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C130%^has been suspended from the ceiling, intersected by spokes like that of a wheel. At each juncture around the rim rest a setting for a %^C214%^wax c%^C220%^a%^C226%^nd%^C220%^l%^C214%^e%^C130%^, the whole offering illumination to the entire room below. A few tattered undergarments hang loosely from a spoke like a defeated flag of surrender.%^CRST%^",
        ({"table", "chairs"}) : "%^RESET%^%^CRST%^%^C130%^Two large chairs sit central to the table, with two smaller chairs flanking on either side. Each is fashioned from %^C136%^mahogany %^C130%^and shaped by a skillful hand, with the %^C144%^insignia of Yniam %^C130%^carved into the center of each back. The edge of the table facing the rest of the room has been left empty, so that those seated may address supplicants. One of the chairs has been thrown to the side in disarray.%^CRST%^",
        "benches" : "%^RESET%^%^CRST%^%^C130%^These are simple wooden benches, likely here for any supplicants awaiting their turn to address the council. It would appear by the stains present that some of the them have been put to more lascivious use.%^CRST%^",
        ({"tapestry", "insignia"}) : "%^RESET%^%^CRST%^%^C130%^The insignia of %^C144%^Yniam %^C130%^has been picked out in durable cloth, that of an %^C040%^e%^C046%^me%^C040%^r%^C046%^a%^C040%^l%^C046%^d c%^C040%^i%^C046%^rcl%^C040%^e %^C130%^containing a white stylized silhouette of gathered %^C144%^stalks of wheat %^C130%^alongside a %^C136%^pair of barrels%^C130%^. It hangs from a %^C243%^s%^C245%^i%^C247%^lv%^C245%^e%^C243%^r b%^C245%^a%^C243%^r%^RESET%^%^C130%^, suspended by bleached rope%^C130%^.%^CRST%^",
        ]));  
    set_exits(([
        "southeast" : ROOMS"outpost_hub",
        ]));
    
    chandelier = random(2);
    chairs = random(2);
    tapestry = random(2);
    benches = random(2);
    
    place_long();
    place_items();
}

void place_long(){
    string long_desc;
    if(chandelier) long_desc = "%^RESET%^%^CRST%^%^C136%^Smooth timber walls frame this structure, varnished and affecting a rugged warmth in the partially %^C059%^ob%^C243%^s%^C059%^cu%^C243%^re%^C059%^d %^RESET%^%^C136%^light offered by a large %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C214%^ch%^C220%^an%^C226%^de%^C220%^li%^C214%^er %^RESET%^%^C136%^overhead.";
    else long_desc = "%^RESET%^%^CRST%^%^C136%^Smooth timber walls frame this structure, varnished and affecting a rugged warmth in the light offered by a large %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C214%^ch%^C220%^an%^C226%^de%^C220%^li%^C214%^er %^RESET%^%^C136%^overhead.";
    if(chairs) long_desc += " The focal point is a %^C130%^large oblong table %^C136%^near the far wall, though several of the chairs are %^C130%^missing %^RESET%^%^C136%^from their places.";
    else long_desc += " The focal point is a %^C130%^large oblong table %^C136%^near the far wall, surrounded by six wooden chairs.";
    if(tapestry) long_desc += " It is overseen by a large crooked tapestry displayed on the wall behind, that of the %^C144%^Yniam Plains insignia %^C136%^in bold %^C046%^gre%^C040%^e%^C046%^ns %^C136%^and %^C255%^whit%^C252%^e%^C255%^s%^RESET%^%^C136%^, though the vibrant colors are marred by %^C101%^st%^C100%^a%^C101%^i%^C100%^ns %^RESET%^%^C136%^and %^C143%^f%^C137%^il%^C131%^t%^C143%^h%^RESET%^%^C136%^.";
    else long_desc += " It is overseen by a large tapestry displayed on the wall behind, that of the %^C144%^Yniam Plains insignia %^C136%^in bold %^C046%^gre%^C040%^e%^C046%^ns %^C136%^and %^C255%^whit%^C252%^e%^C255%^s%^RESET%^%^C136%^.";
    if(benches) long_desc += " There are wooden banisters in place to bisect the room, with a gathering of scattered and %^C058%^dirty %^RESET%^%^C136%^benches leading to the entrance.%^CRST%^\n";
    else long_desc += " There are wooden banisters in place to bisect the room, with a couple rows of benches leading to the entrance.%^CRST%^\n";
    set_long(long_desc);
    return;
}

void place_items(){
    remove_item("chandelier");
    remove_item("candles");
    remove_item("table");
    remove_item("chairs");
    remove_item("benches");
    remove_item("tapestry");
    remove_item("insignia");
    
    if(chandelier){
        add_item("chandelier", "%^RESET%^%^CRST%^%^C130%^A circle of %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C130%^has been suspended from the ceiling, intersected by spokes like that of a wheel. At each juncture around the rim rest a setting for a %^C214%^wax c%^C220%^a%^C226%^nd%^C220%^l%^C214%^e%^C130%^, the whole offering illumination to the entire room below. A few %^C224%^t%^C218%^at%^C212%^t%^C224%^e%^C218%^re%^C212%^d %^C224%^u%^C218%^nd%^C212%^e%^C224%^r%^C218%^ga%^C212%^r%^C224%^m%^C218%^en%^C212%^t%^C224%^s %^RESET%^%^C130%^hang loosely from a spoke like a defeated flag of surrender.%^CRST%^");
        add_item("candles", "%^RESET%^%^CRST%^%^C130%^A circle of %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C130%^has been suspended from the ceiling, intersected by spokes like that of a wheel. At each juncture around the rim rest a setting for a %^C214%^wax c%^C220%^a%^C226%^nd%^C220%^l%^C214%^e%^C130%^, the whole offering illumination to the entire room below. A few %^C224%^t%^C218%^at%^C212%^t%^C224%^e%^C218%^re%^C212%^d %^C224%^u%^C218%^nd%^C212%^e%^C224%^r%^C218%^ga%^C212%^r%^C224%^m%^C218%^en%^C212%^t%^C224%^s %^RESET%^%^C130%^hang loosely from a spoke like a defeated flag of surrender.%^CRST%^");
    }
    else{
        add_item("chandelier", "%^RESET%^%^CRST%^%^C130%^A circle of %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C130%^has been suspended from the ceiling, intersected by spokes like that of a wheel. At each juncture around the rim rest a setting for a %^C214%^wax c%^C220%^a%^C226%^nd%^C220%^l%^C214%^e%^C130%^, the whole offering illumination to the entire room below.%^CRST%^");
        add_item("candles", "%^RESET%^%^CRST%^%^C130%^A circle of %^C059%^wrought %^C245%^ir%^C247%^o%^C245%^n %^RESET%^%^C130%^has been suspended from the ceiling, intersected by spokes like that of a wheel. At each juncture around the rim rest a setting for a %^C214%^wax c%^C220%^a%^C226%^nd%^C220%^l%^C214%^e%^C130%^, the whole offering illumination to the entire room below.%^CRST%^");
    }
    if(chairs){
        add_item("table", "%^RESET%^%^CRST%^%^C130%^Two large chairs sit central to the table, with two smaller chairs flanking on either side. Each is fashioned from %^C136%^mahogany %^C130%^and shaped by a skillful hand, with the %^C144%^insignia of Yniam %^C130%^carved into the center of each back. The edge of the table facing the rest of the room has been left empty, so that those seated may address supplicants. Several of the chairs have been thrown to the side in %^C059%^di%^C243%^s%^C059%^ar%^C243%^r%^C059%^ay%^RESET%^%^C130%^, with scattered piles of %^C255%^wh%^C252%^i%^C255%^t%^C252%^e %^C255%^d%^C252%^u%^C255%^st %^RESET%^%^C130%^arrayed in messy lines on the table top.%^CRST%^");
        add_item("chairs", "%^RESET%^%^CRST%^%^C130%^Two large chairs sit central to the table, with two smaller chairs flanking on either side. Each is fashioned from %^C136%^mahogany %^C130%^and shaped by a skillful hand, with the %^C144%^insignia of Yniam %^C130%^carved into the center of each back. The edge of the table facing the rest of the room has been left empty, so that those seated may address supplicants. Several of the chairs have been thrown to the side in %^C059%^di%^C243%^s%^C059%^ar%^C243%^r%^C059%^ay%^RESET%^%^C130%^, with scattered piles of %^C255%^wh%^C252%^i%^C255%^t%^C252%^e %^C255%^d%^C252%^u%^C255%^st %^RESET%^%^C130%^arrayed in messy lines on the table top.%^CRST%^");
    }
    else{
        add_item("table", "%^RESET%^%^CRST%^%^C130%^Two large chairs sit central to the table, with two smaller chairs flanking on either side. Each is fashioned from %^C136%^mahogany %^C130%^and shaped by a skillful hand, with the %^C144%^insignia of Yniam %^C130%^carved into the center of each back. The edge of the table facing the rest of the room has been left empty, so that those seated may address supplicants.%^CRST%^");
        add_item("chairs", "%^RESET%^%^CRST%^%^C130%^Two large chairs sit central to the table, with two smaller chairs flanking on either side. Each is fashioned from %^C136%^mahogany %^C130%^and shaped by a skillful hand, with the %^C144%^insignia of Yniam %^C130%^carved into the center of each back. The edge of the table facing the rest of the room has been left empty, so that those seated may address supplicants.%^CRST%^");
    }
    if(tapestry){
        add_item("tapestry", "%^RESET%^%^CRST%^%^C130%^The insignia of %^C144%^Yniam %^C130%^has been picked out in durable cloth, that of an %^C040%^e%^C046%^me%^C040%^r%^C046%^a%^C040%^l%^C046%^d c%^C040%^i%^C046%^rcl%^C040%^e %^C130%^containing a white stylized silhouette of gathered %^C144%^stalks of wheat %^C130%^alongside a %^C136%^pair of barrels%^C130%^. It hangs crookedly from a %^C243%^s%^C245%^i%^C247%^lv%^C245%^e%^C243%^r b%^C245%^a%^C243%^r%^RESET%^%^C130%^ that has been partially yanked from the wall, and suspended by bleached rope%^C130%^. A corner of the tapestry is %^C058%^wet %^C130%^and %^C101%^st%^C100%^a%^C101%^i%^C100%^ne%^C101%^d %^RESET%^%^C130%^by the results of %^C143%^j%^C137%^ub%^C131%^i%^C143%^l%^C137%^an%^C131%^t %^C143%^e%^C137%^xc%^C131%^e%^C143%^s%^C137%^s%^RESET%^%^C130%^, which continues down the wall and onto the floor.%^CRST%^");
        add_item("insignia", "%^RESET%^%^CRST%^%^C130%^The insignia of %^C144%^Yniam %^C130%^has been picked out in durable cloth, that of an %^C040%^e%^C046%^me%^C040%^r%^C046%^a%^C040%^l%^C046%^d c%^C040%^i%^C046%^rcl%^C040%^e %^C130%^containing a white stylized silhouette of gathered %^C144%^stalks of wheat %^C130%^alongside a %^C136%^pair of barrels%^C130%^. It hangs crookedly from a %^C243%^s%^C245%^i%^C247%^lv%^C245%^e%^C243%^r b%^C245%^a%^C243%^r%^RESET%^%^C130%^ that has been partially yanked from the wall, and suspended by bleached rope%^C130%^. A corner of the tapestry is %^C058%^wet %^C130%^and %^C101%^st%^C100%^a%^C101%^i%^C100%^ne%^C101%^d %^RESET%^%^C130%^by the results of %^C143%^j%^C137%^ub%^C131%^i%^C143%^l%^C137%^an%^C131%^t %^C143%^e%^C137%^xc%^C131%^e%^C143%^s%^C137%^s%^RESET%^%^C130%^, which continues down the wall and onto the floor.%^CRST%^");
    }
    else{
        add_item("tapestry", "%^RESET%^%^CRST%^%^C130%^The insignia of %^C144%^Yniam %^C130%^has been picked out in durable cloth, that of an %^C040%^e%^C046%^me%^C040%^r%^C046%^a%^C040%^l%^C046%^d c%^C040%^i%^C046%^rcl%^C040%^e %^C130%^containing a white stylized silhouette of gathered %^C144%^stalks of wheat %^C130%^alongside a %^C136%^pair of barrels%^C130%^. It hangs from a %^C243%^s%^C245%^i%^C247%^lv%^C245%^e%^C243%^r b%^C245%^a%^C243%^r%^RESET%^%^C130%^, suspended by bleached rope%^C130%^.%^CRST%^");
        add_item("insignia", "%^RESET%^%^CRST%^%^C130%^The insignia of %^C144%^Yniam %^C130%^has been picked out in durable cloth, that of an %^C040%^e%^C046%^me%^C040%^r%^C046%^a%^C040%^l%^C046%^d c%^C040%^i%^C046%^rcl%^C040%^e %^C130%^containing a white stylized silhouette of gathered %^C144%^stalks of wheat %^C130%^alongside a %^C136%^pair of barrels%^C130%^. It hangs from a %^C243%^s%^C245%^i%^C247%^lv%^C245%^e%^C243%^r b%^C245%^a%^C243%^r%^RESET%^%^C130%^, suspended by bleached rope%^C130%^.%^CRST%^");
    }
    if(benches) add_item("benches", "%^RESET%^%^CRST%^%^C130%^These are simple wooden benches, likely here for any supplicants awaiting their turn to address the council. %^C058%^Da%^C243%^r%^C059%^k %^C058%^wet %^C101%^st%^C100%^a%^C101%^i%^C100%^ns %^C130%^hint at the benches being put to more %^C099%^l%^C105%^as%^C111%^c%^C099%^i%^C105%^vi%^C111%^o%^C099%^u%^C105%^s %^RESET%^%^C130%^use recently.%^CRST%^");
    else add_item("benches", "%^RESET%^%^CRST%^%^C130%^These are simple wooden benches, likely here for any supplicants awaiting their turn to address the council.%^CRST%^");
    return;
}

