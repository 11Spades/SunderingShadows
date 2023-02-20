// Branwen (6/4/22)
// Yniam Waystation - Shrine

#include <std.h>
#include "/d/dagger/yniam/defs.h"
inherit ROOM;

#define JUNK ({ "%^RESET%^%^CRST%^%^C153%^Papers strewn across the %^C101%^table%^C153%^ appear to be %^C152%^half-formed thoughts%^C153%^ and %^C152%^forgotten lyrics%^RESET%^%^C153%^, as well as the %^C152%^random doodle%^C153%^ or %^C152%^sketch%^C153%^.%^CRST%^ ", "%^RESET%^%^CRST%^%^C153%^Books are stacked up here and there, with topics ranging from the %^C152%^weird%^C153%^ to the %^C152%^mundane%^C153%^.%^CRST%^ ", "%^RESET%^%^CRST%^%^C152%^Cl%^C146%^othi%^C152%^ng%^C153%^ and %^C152%^co%^C146%^stum%^C152%^es%^RESET%^%^C153%^ have worked their way into almost every corner, gathered in %^C152%^small piles%^C152%^.%^CRST%^ ", "%^RESET%^%^CRST%^%^C153%^Some %^C152%^racier%^C153%^ items lay about, such as that %^C243%^ball gag%^C153%^ and those %^C243%^handcuffs%^C153%^. And is that phallic looking thing made from real %^C063%^sa%^C069%^pp%^C068%^hi%^C062%^re%^C068%^s%^RESET%^%^C153%^?%^CRST%^ ", "%^RESET%^%^CRST%^%^C101%^D%^C107%^irt%^C101%^y d%^C107%^ishe%^C101%^s%^RESET%^%^C153%^ from downstairs are starting to %^C107%^crust over%^C153%^, hopefully somebody comes to take them away soon because %^C058%^...ew%^C153%^.%^CRST%^ ", "%^RESET%^%^CRST%^%^C153%^A %^C064%^tobacco pipe%^C153%^, some %^C058%^rolling papers%^C153%^, a few bags of %^C070%^pungent herbs%^C153%^, and even a small mirror covered in %^C250%^white dust%^RESET%^%^C153%^ are left forgotten for now. Looks like somebody had a %^C152%^fun%^C153%^ time.%^CRST%^ ", "%^RESET%^%^CRST%^%^C153%^A %^C152%^deck of cards%^C153%^ is scattered across the floor, the game long abandoned.%^CRST%^ ", "%^RESET%^%^CRST%^%^C153%^A few %^C244%^small knives%^C153%^ jut outward from the %^C152%^s%^C153%^c%^C152%^arr%^C153%^e%^C152%^d w%^C153%^a%^C152%^ll%^RESET%^%^C153%^, right on target.%^CRST%^ " })
#define INHALE ({ "%^RESET%^%^CRST%^%^C255%^You %^C146%^relax%^C255%^ as you inhale the %^C253%^i%^C250%^n%^C252%^t%^C255%^ox%^C252%^ic%^C250%^at%^C253%^i%^C250%^n%^C253%^g s%^C250%^m%^C252%^o%^C255%^k%^C252%^e%^RESET%^%^C255%^.%^CRST%^", "%^RESET%^%^CRST%^%^C253%^A %^C247%^dreamy haze%^C253%^ hangs over the room, %^C247%^da%^C245%^nc%^C243%^in%^C245%^g and s%^C247%^wi%^C245%^rl%^C243%^in%^C245%^g%^RESET%^%^C253%^, mesmerizing.%^CRST%^", "%^RESET%^%^CRST%^%^C046%^Everything is so %^C040%^f%^C041%^u%^C042%^cki%^C041%^n%^C040%^g a%^C041%^m%^C042%^usi%^C041%^n%^C040%^g...%^CRST%^", "%^RESET%^%^CRST%^%^C153%^The %^C147%^ambient music%^C153%^ p%^C147%^u%^C153%^ls%^C147%^e%^RESET%^%^C153%^s in time with your %^C147%^heart%^C153%^, with your %^C147%^breath%^C153%^, with the %^C147%^wind%^RESET%^%^C153%^.%^CRST%^", "%^RESET%^%^CRST%^%^C153%^A snack would be %^C159%^amazing%^C153%^ right now.%^CRST%^", "%^RESET%^%^CRST%^%^C243%^You forg%^C245%^o%^C243%^t to think a%^C245%^b%^C243%^out what y%^C245%^o%^C243%^u just rem%^C245%^e%^C243%^mber%^C245%^e%^C243%^d.%^CRST%^", "%^RESET%^%^CRST%^%^C255%^Y%^C252%^o%^C255%^u rel%^C252%^a%^C255%^x back i%^C252%^n%^C255%^to the cu%^C252%^s%^C255%^hio%^C252%^n%^RESET%^%^C255%^s le%^C252%^t%^C255%^ting your car%^C252%^e%^C255%^s drift a%^C252%^w%^C255%^ay on a p%^C252%^u%^C255%^ff of smo%^C252%^k%^C255%^e.%^CRST%^", "%^RESET%^%^CRST%^%^C165%^A%^C170%^l%^C175%^l %^C180%^t%^C185%^h%^C190%^e %^C154%^c%^C149%^o%^C144%^l%^C139%^o%^C134%^r%^C129%^s %^C057%^a%^C062%^r%^C067%^e %^C072%^s%^C077%^o %^C082%^b%^C047%^e%^C042%^a%^C037%^u%^C032%^t%^C027%^i%^C093%^f%^C098%^u%^C103%^l%^C108%^.%^CRST%^" })
#define THOUGHTS ({ "%^RESET%^%^CRST%^%^C159%^There's nothing so tragic as seeing a family pulled apart by something as simple as a pack of wolves.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^I can picture in my mind a world without war, a world without hate. And I can picture us attacking that world, because they'd never expect it.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^It takes a big man to cry, but it takes a bigger man to laugh at that man.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^In the end, everything will be okay. If it's not okay, it's not yet the end.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^If you drop soap on the floor, is the floor clean or is the soap dirty?%^CRST%^", "%^RESET%^%^CRST%^%^C159%^Nothing is ever really on fire, but rather fire is on things.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^The word bed looks like a bed.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^Ice cubes float in a pool of their own blood.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^Right now, you are both the oldest you have ever been and the youngest you will ever be again.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^If life is unfair to everyone, does that mean it's actually fair?%^CRST%^", "%^RESET%^%^CRST%^%^C159%^You can never stand backwards on stairs.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^If you replace the W with a T in the words what, where, and when, you have your answer.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^You are younger right now than you are right now.%^CRST%^", "%^RESET%^%^CRST%^%^C159%^Which came first, the plant or the seed?%^CRST%^", "%^RESET%^%^CRST%^%^C159%^The world is so big, and you are so very.. very... small.%^CRST%^" })

int clutter;

void create(){
    ::create();
    set_terrain(BEACH);
    set_travel(DIRT_ROAD);
    set_property("light", 2);
    set_property("indoors", 0);
    set_name("cacia's shrine");
    set_short("%^RESET%^%^CRST%^%^C060%^Cacia's Shrine%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C101%^A %^C243%^stone path%^C101%^ leads to a circle of pavement that gives way to a raised %^C243%^m%^C245%^a%^C243%^r%^C245%^b%^C243%^l%^C245%^e %^C243%^pl%^C245%^at%^C243%^fo%^C245%^rm%^RESET%^%^C101%^ dominated by a %^C060%^beguiling sculpture%^RESET%^%^C101%^. Offerings are lain out at its feet or placed reverently in its upturned palms. An %^C102%^inscription%^RESET%^%^C101%^ wraps around the periphery of the dais. A large %^C194%^wa%^C195%^te%^C188%^r p%^C189%^ip%^C194%^e %^RESET%^%^C101%^has been set in front of the %^C060%^shrine%^C101%^, surrounded by a collection of comfortable %^C030%^c%^C029%^u%^C028%^s%^C029%^h%^C030%^i%^C031%^o%^C030%^n%^C029%^s%^RESET%^%^C101%^.\n\n%^RESET%^%^C059%^Little else flourishes here, and even the wind seems hesitant to expel its breath, the world stilled as if waiting for a ravenous predator to pass.\n%^CRST%^");
    set_smell("default","%^RESET%^%^CRST%^%^C156%^The scents of the plains are carried on the breeze.%^CRST%^");
    set_listen("default","%^RESET%^%^CRST%^%^C247%^The %^C244%^silence%^C247%^ is palpable.%^CRST%^");
    set_items(([
        "offerings" : "%^RESET%^%^CRST%^%^C109%^Placed with intention are traces of %^C245%^worldly vices%^C109%^: Bottles of spirits, cigarettes, pouches of pungent herbs. Splashes of blood, wine, and other curious substances are all %^C114%^reverently%^C109%^ left here by those seeking her favor.%^CRST%^",
        ({ "statue", "platform", "dais", "sculpture" }) : "%^RESET%^%^CRST%^%^C060%^A sinuous sculpture lurks before you, its %^C054%^alluring%^C060%^ feminine form encapsulated in solid %^C061%^darksteel%^RESET%^%^C060%^, the edge of each detail picked out in a sinister %^C053%^viol%^C052%^e%^C053%^t tarni%^C052%^s%^C053%^h%^RESET%^%^C060%^. A smile tugs at the corner of her %^C059%^swollen lips%^RESET%^%^C060%^, her comely gaze cast downward to take in your measure. Six supple arms grace her slender body, the two at her shoulders reaching high and low along her curves to seek out the %^C059%^tantalizing%^C060%^ swell of a breast and the %^C059%^shaded secrets%^C060%^ between clenched thighs. The other four slink outwards from the serpentine curve of her back, her delicate hands palm upwards, awaiting the %^C066%^offerings%^C060%^ of her supplicants.%^CRST%^",
        "inscription" : ({"%^RESET%^%^CRST%^%^C102%^Words have been carved into the curve of the stone base.%^CRST%^", "%^RESET%^%^CRST%^%^C059%^\"She Who Drinks of the World.\"%^CRST%^", "common"}),
        "water pipe" : "%^RESET%^%^CRST%^%^C194%^De%^C195%^li%^C188%^ca%^C189%^te %^C194%^gl%^C195%^a%^C188%^ss%^RESET%^%^C255%^ has been sculpted into a sinuous cylinder, with a tint of %^C194%^ir%^C195%^id%^C188%^es%^C189%^ce%^C194%^nt %^C195%^co%^C188%^lo%^C189%^ri%^C194%^ng%^RESET%^%^C255%^ as %^C195%^airy%^C255%^ and %^C195%^ethereal%^RESET%^%^C255%^ as %^C194%^s%^C195%^oa%^C194%^p b%^C188%^u%^C189%^b%^C194%^b%^C195%^l%^C188%^e%^C189%^s%^RESET%^%^C255%^. The small glass bowl is always packed full with %^C086%^s%^C085%^w%^C084%^e%^C083%^e%^C082%^t sm%^C040%^elli%^C082%^ng h%^C083%^e%^C084%^r%^C085%^b%^C086%^s%^RESET%^%^C255%^. This pipe has a small hole to cover with a finger, and then release when you're ready to fill your lungs with that %^C245%^en%^C146%^ti%^C245%^ci%^C146%^ng%^C245%^ly in%^C146%^to%^C245%^xica%^C146%^ti%^C245%^ng smoke%^RESET%^%^C255%^.%^CRST%^",
        ]));
    set_exits(([
        "north" : ROOMS"outpost_hub",
        ]));
        
    clutter = random(7) + 3;
    place_long();
    place_offerings();
}

void init(){
    ::init();
    add_action("smoke_fun", "smoke");
}

void reset(){
    ::reset();
    
    if(!present("ambiance device")) new("/realms/chernobog/events/vikaelis/liars/mon/ambiance_shrine")->move(this_object());
}

int smoke_fun(string str){
    object player, room;
    
    if(!str) return notify_fail("You could try to smoke the water pipe.");
    if(str != "the water pipe" && str != "water pipe") return notify_fail("You could try to smoke the water pipe.");
    
    player = this_player();
    room = this_object();
    tell_object(player, "%^RESET%^%^CRST%^%^C059%^You take a long hit from the water pipe, letting out a long breath of smoke before setting it back down.%^CRST%^");
    tell_object(player, INHALE[random(sizeof(INHALE))]);
    tell_room(room, "%^RESET%^%^CRST%^%^C059%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^ takes a long hit from the water pipe, letting out a long breath of smoke before setting it back down.%^CRST%^", player);
    player->add_intox(300);
    if(!random(3)) call_out("deep_thoughts", random(5) + 10, player);
    return 1;
}

void deep_thoughts(object player){
    tell_object(player, THOUGHTS[random(sizeof(THOUGHTS))]);
    tell_room(environment(player), "%^RESET%^%^CRST%^%^C245%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C245%^ stares into space with half-lidded eyes.%^CRST%^", player);
    return;
}

void place_long(){
    string long_desc;
    
    long_desc = "%^RESET%^%^CRST%^%^C101%^A %^C243%^stone path%^C101%^ leads to a circle of pavement that gives way to a raised %^C243%^m%^C245%^a%^C243%^r%^C245%^b%^C243%^l%^C245%^e %^C243%^pl%^C245%^at%^C243%^fo%^C245%^rm%^RESET%^%^C101%^ dominated by a %^C060%^beguiling sculpture%^RESET%^%^C101%^.";
    switch(clutter){
        case 3..4:
            long_desc += " A %^C144%^few %^C101%^offerings";
            break;
        case 5..7:
            long_desc += " A %^C144%^gathering %^C101%^of various offerings";
            break;
        case 8..10:
            long_desc += " A %^C144%^multitude %^C101%^of offerings";
            break;
    }
    long_desc += " are lain out at its feet or placed reverently in its upturned palms. An %^C102%^inscription%^RESET%^%^C101%^ wraps around the periphery of the dais.%^CRST%^\n\n%^RESET%^%^CRST%^%^C100%^A large %^C194%^wa%^C195%^te%^C188%^r p%^C189%^ip%^C194%^e %^RESET%^%^C100%^has been set in front of the %^C060%^shrine%^C100%^, surrounded by a collection of comfortable %^C060%^c%^C061%^u%^C062%^s%^C063%^h%^C062%^i%^C063%^o%^C062%^n%^C061%^s%^RESET%^%^C100%^.\n\n%^RESET%^%^C059%^Little else flourishes here, and even the wind seems hesitant to expel its breath, the world stilled as if waiting for a ravenous predator to pass.\n%^CRST%^";
    set_long(long_desc);
    return;
}

void place_offerings(){
    string offerings_desc, *offerings;
    int i, selection;
    
    offerings = ({ "%^CRST%^%^RESET%^%^C245%^a s%^C248%^m%^C245%^all fla%^C248%^s%^C245%^k%^CRST%^", "%^CRST%^%^RESET%^%^C059%^sil%^C243%^k%^C059%^y un%^C243%^de%^C059%^rgarm%^C243%^en%^C059%^ts%^CRST%^", "%^CRST%^%^RESET%^%^C058%^a half-smoked %^C130%^c%^C136%^i%^C130%^g%^C136%^a%^C130%^r%^CRST%^", "%^CRST%^%^RESET%^%^C250%^a %^C243%^s%^C245%^i%^C250%^lv%^C245%^e%^C243%^r %^C250%^ci%^C101%^g%^C250%^ar%^C245%^e%^C250%^tte ca%^C245%^s%^C250%^e%^CRST%^", "%^CRST%^%^RESET%^%^C248%^an unopened %^C101%^bottle%^C248%^ of %^C255%^v%^C250%^o%^C255%^dka%^CRST%^", "%^CRST%^%^RESET%^%^C109%^a ri%^C103%^bb%^C109%^ed gla%^C103%^s%^C109%^s dil%^C103%^d%^C109%^o%^CRST%^", "%^CRST%^%^RESET%^%^C021%^a de%^C026%^e%^C021%^p bl%^C026%^u%^C021%^e m%^C026%^u%^C021%^shro%^C026%^o%^C021%^m%^CRST%^", "%^CRST%^%^RESET%^%^C088%^a r%^C089%^e%^C088%^d-cap%^C089%^p%^C088%^ed m%^C089%^u%^C088%^shro%^C089%^o%^C088%^m%^CRST%^", "%^CRST%^%^RESET%^%^C101%^an empty %^C100%^whiskey %^C101%^bottle%^CRST%^", "%^CRST%^%^RESET%^%^C090%^a plate of p%^C096%^a%^C089%^s%^C090%^tr%^C096%^ie%^C090%^s%^CRST%^", "%^CRST%^%^RESET%^%^C104%^a b%^C122%^o%^C104%^wl of gr%^C122%^a%^C104%^pes%^CRST%^", "%^CRST%^%^RESET%^%^C243%^a set of shackles%^CRST%^", "%^CRST%^%^RESET%^%^C052%^a le%^C053%^a%^C052%^ther whip%^CRST%^", "%^CRST%^%^RESET%^%^C059%^an obsidian ring%^CRST%^", "%^CRST%^%^RESET%^%^C184%^a go%^C190%^ld%^C184%^en ri%^C190%^n%^C184%^g%^CRST%^", "%^CRST%^%^RESET%^%^C255%^a d%^C159%^i%^C250%^a%^C255%^mo%^C159%^n%^C255%^d ri%^C159%^n%^C255%^g%^CRST%^", "%^CRST%^%^RESET%^%^C136%^a p%^C142%^i%^C148%^l%^C226%^e o%^C190%^f c%^C226%^o%^C148%^i%^C142%^n%^C136%^s%^CRST%^", "%^CRST%^%^RESET%^%^C161%^c%^C160%^o%^C088%^l%^C089%^o%^C090%^r%^C091%^f%^C092%^u%^C093%^l %^C021%^g%^C020%^e%^C025%^m %^C030%^s%^C035%^h%^C040%^a%^C047%^r%^C084%^d%^C085%^s%^CRST%^" });
    offerings += ({ "%^CRST%^%^RESET%^%^C188%^a small pouch of %^C195%^white powder%^CRST%^", "%^CRST%^%^RESET%^%^C124%^a sprinkling of %^C196%^r%^C124%^e%^C196%^d du%^C124%^s%^C196%^t%^CRST%^", "%^CRST%^%^RESET%^%^C101%^a %^C102%^pipe%^C101%^ packed full of %^C082%^h%^C076%^e%^C082%^rbs%^CRST%^", "%^CRST%^%^RESET%^%^C094%^c%^C095%^ho%^C094%^col%^C095%^at%^C094%^e %^C124%^st%^C088%^r%^C125%^a%^C124%^wberr%^C125%^i%^C088%^e%^C124%^s%^CRST%^", "%^CRST%^%^RESET%^%^C243%^a sp%^C060%^ik%^C243%^ed c%^C060%^o%^C243%^ll%^C060%^a%^C243%^r%^CRST%^", "%^CRST%^%^RESET%^%^C189%^a half-empty %^C183%^wine%^C189%^ glass%^CRST%^", "%^CRST%^%^RESET%^%^C101%^half of a %^C102%^bottle%^C101%^ of %^C100%^rum%^CRST%^", "%^CRST%^%^RESET%^%^C150%^a gl%^C144%^a%^C150%^ss e%^C144%^y%^C150%^e%^CRST%^", "%^CRST%^%^RESET%^%^C100%^a w%^C101%^o%^C100%^rn w%^C101%^o%^C100%^od%^C101%^e%^C100%^n dil%^C101%^d%^C100%^o%^CRST%^", "%^CRST%^%^RESET%^%^C243%^a ball gag%^CRST%^", "%^CRST%^%^RESET%^%^C159%^a p%^C158%^a%^C157%^i%^C156%^r %^C157%^o%^C158%^f %^C157%^d%^C158%^i%^C159%^r%^C158%^t%^C157%^y %^C156%^p%^C157%^a%^C158%^n%^C159%^t%^C158%^i%^C157%^e%^C156%^s%^CRST%^", "%^CRST%^%^RESET%^%^C143%^a small dish of %^C136%^h%^C142%^o%^C136%^ney%^CRST%^", "%^CRST%^%^RESET%^%^C102%^an empty %^C101%^beer stein%^CRST%^", "%^CRST%^%^RESET%^%^C191%^a sheaf of %^C184%^wheat%^CRST%^", "%^CRST%^%^RESET%^%^C083%^a bouquet of %^C127%^w%^C126%^i%^C125%^l%^C124%^d %^C196%^f%^C197%^l%^C198%^o%^C199%^w%^C200%^e%^C201%^r%^C207%^s%^CRST%^", "%^CRST%^%^RESET%^%^C255%^milky drippings%^CRST%^", "%^CRST%^%^RESET%^%^C053%^a %^C052%^scourge%^C053%^ whip%^CRST%^", "%^CRST%^%^RESET%^%^C250%^a %^C253%^shiny %^C243%^d%^C245%^a%^C247%^gg%^C245%^e%^C243%^r%^CRST%^", "%^CRST%^%^RESET%^%^C243%^a razor-edged poker%^CRST%^", "%^CRST%^%^RESET%^%^C231%^a jug of %^C195%^m%^C231%^o%^C195%^onshi%^C231%^n%^C195%^e%^CRST%^", "%^CRST%^%^RESET%^%^C059%^a t%^C058%^u%^C059%^ft of d%^C058%^a%^C059%^rk f%^C058%^u%^C059%^r%^CRST%^", "%^CRST%^%^RESET%^%^C176%^f%^C177%^u%^C176%^zzy h%^C177%^a%^C176%^n%^C177%^dc%^C176%^uf%^C177%^f%^C176%^s%^CRST%^", "%^CRST%^%^RESET%^%^C089%^a %^C124%^blo%^C088%^o%^C124%^dy%^C089%^ finger%^CRST%^", "%^CRST%^%^RESET%^%^C245%^a %^C243%^charred%^C245%^ portrait%^CRST%^", "%^CRST%^%^RESET%^%^C189%^a %^C195%^crusty drawing%^C189%^ of a %^C183%^woman%^CRST%^", "%^CRST%^%^RESET%^%^C101%^an old l%^C100%^u%^C101%^te%^CRST%^", "%^CRST%^%^RESET%^%^C124%^a single %^C088%^red%^C124%^ rose%^CRST%^", "%^CRST%^%^RESET%^%^C255%^a jar of milk%^CRST%^", "%^CRST%^%^RESET%^%^C040%^a %^C035%^l%^C030%^o%^C025%^n%^C020%^g %^C021%^p%^C026%^e%^C031%^a%^C036%^c%^C041%^o%^C046%^c%^C082%^k %^C047%^f%^C042%^e%^C037%^a%^C032%^t%^C027%^h%^C033%^e%^C038%^r%^CRST%^", "%^CRST%^%^RESET%^%^C076%^a small bag of %^C082%^c%^C083%^r%^C084%^y%^C085%^s%^C086%^t%^C158%^a%^C157%^l%^C156%^l%^C157%^i%^C158%^z%^C086%^e%^C085%^d %^C084%^h%^C083%^e%^C082%^r%^C083%^b%^C084%^s%^CRST%^", "%^CRST%^%^RESET%^%^C250%^a s%^C245%^c%^C101%^a%^C250%^tter%^C245%^i%^C101%^n%^C250%^g of %^C255%^ci%^C250%^ga%^C245%^r%^C101%^e%^C250%^tt%^C255%^es%^CRST%^", "%^CRST%^%^RESET%^%^C070%^a cup of %^C065%^green tea%^CRST%^", "%^CRST%^%^RESET%^%^C101%^a %^C243%^wafting %^C101%^stick of %^C103%^incense%^CRST%^", "%^CRST%^%^RESET%^%^C125%^a sensual %^C124%^r%^C088%^e%^C124%^d c%^C088%^a%^C124%^ndle%^CRST%^" });
    offerings_desc = "%^RESET%^%^CRST%^%^C109%^Placed with intention are traces of %^C245%^worldly vices%^C109%^, all %^C114%^reverently%^C109%^ left here by those seeking her favor. At a glance, you can see: %^CRST%^";
    for(i = 0; i < clutter; i++){
        selection = random(sizeof(offerings));
        if((i + 1) == clutter) offerings_desc += "and "+offerings[selection]+".%^CRST%^";
        else offerings_desc += offerings[selection]+", ";
        
        offerings -= ({ offerings[selection] });
        continue;
    }
    remove_item("offerings");
    add_item("offerings", offerings_desc);
    return;
}

