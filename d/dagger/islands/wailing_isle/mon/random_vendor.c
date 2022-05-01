// Chernobog & Titania (2/7/22)
// The Wailing Isle - Random Wood/Metal/Cloth Vendor

#include "../defs.h"
inherit VENDOR;

void create() {
    ::create();
    pick_vendor(random(3));
    
    set("aggressive", 0);
    set_level(10);
    set_alignment(6);
    set_race("human");
    set_hd(10,0);
    set_exp(10);
    set_max_hp(query_hp());
    add_money("copper", random(200));
    set_property("no_random_treasure",1);
}

void pick_vendor(int vendor){
    switch(vendor){
        case 0:
            set_name("Valentino");
            set_id(({"valentino", "Valentino", "merchant", "cloth merchant"}));
            set_short("%^RESET%^%^CRST%^%^C244%^Valentino, the Cloth Merchant%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C244%^This is a man of Attayan blood, in his early twenties, with %^C059%^long dark hair%^C244%^ and %^C059%^dark eyes%^C244%^. He is dressed in a loose-fitting %^C059%^black cotton shirt%^C244%^ and an %^C072%^aquamarine vest%^RESET%^%^C244%^, and breezy %^C059%^black pantaloons%^C244%^. His feet are slid into comfortable %^C101%^hemp sandals%^C244%^. He is one of the more %^C246%^serene%^C244%^ fellows on Wailing Isle, as he politely peddles his cloth to interested parties, never seeming particularly phased by anything.%^CRST%^\n");
            set_gender("male");
            set_storage_room(STOR"cloth_storage");
            break;
        case 1:
            set_name("Emilie");
            set_id(({"emilie", "Emilie", "merchant", "metal merchant"}));
            set_short("%^RESET%^%^CRST%^%^C073%^Emilie, the Metal Merchant%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C073%^Here is a young lady with a %^C059%^dark pixie cut%^C073%^ wrapped up in a %^C160%^red scarf%^C073%^. Her eyes are those of a predator, %^C082%^piercing green slits%^C073%^ that seem to catch every movement. She's not bad on the eyes, although the %^C066%^sharpened teeth%^C073%^ are a little disconcerting. The %^C142%^g%^C220%^o%^C142%^ld%^C136%^e%^C142%^n%^RESET%^%^C073%^ one might be worth something, but her grin tightens if she catches anyone staring. Her demeanor carries some menace, lurking just beneath the surface in her dealings.%^CRST%^\n");
            set_gender("female");
            set_storage_room(STOR"metal_storage");
            break;
        case 2:
            set_name("Abram");
            set_id(({"abram", "Abram", "merchant", "wood merchant"}));
            set_short("%^RESET%^%^CRST%^%^C101%^Abram, the Wood Merchant%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C101%^This lanky man limps around the marketplace, his right foot little more than a %^C100%^peg%^C101%^ he uses for balance. He is an %^C107%^elderly gentleman%^C101%^ of some sixty years, with a %^C249%^lo%^C247%^ng %^C243%^gray %^C247%^be%^C249%^ar%^C247%^d%^RESET%^%^C101%^ and %^C249%^bu%^C247%^sh%^C244%^y e%^C247%^ye%^C249%^br%^C247%^ow%^C244%^s%^RESET%^%^C101%^. He has a gaunt face and rough skin, with penetrating %^C033%^bl%^C027%^ue ey%^C033%^es%^C101%^ that glimmer with youthful mischief. He assures you that his %^C100%^wood%^C101%^ is the best that ever was, and that never has there been a greater bargain since the beginning of time.%^CRST%^\n");
            set_gender("male");
            set_storage_room(STOR"wood_storage");
            break;
    }
    return;
}

void init(){
    ::init();
    add_action("hit_fun", "hit");
}

int hit_fun(string str){
    object npc;
    npc = this_object();
    
    if(str != "merchant" && str != "abram" && str != "Abram" && str != "emilie" && str != "Emilie" && str != "valentino" && str != "Valentino") return 0;
    if(npc->query_hp() > 0){
        force_me("emoteat "+this_player()->query_name()+" $M gives $N a wary look, taking a step back.");
        return 0;
    }
    this_player()->set("reputation wailing isle", -10);
    return 0;
}

void die(){
    object room, npc;
    object* attackers;
    int i;
    
    npc = this_object();
    room = environment(npc);
    attackers = npc->query_attackers();
    
    for(i = 0; sizeof(attackers), i < sizeof(attackers); i++){
        if (!objectp(attackers[i])) continue;
        if (userp(attackers[i])) {
            attackers[i]->set("reputation wailing isle", -10);
            continue;
        }
        continue;
    }
    ::die();
}

