// Chernobog & Titania (2/22/22)
// Wailing Isle - Fish

inherit "/std/food.c";

void create(){
    ::create();
    set_name("fish");
    set_id(({"fish"}));
    set_short("%^RESET%^%^CRST%^small generic fish%^CRST%^");
    set_long("%^RESET%^%^CRST%^This is a small little fish from a pond.\n%^CRST%^");
    set_destroy();
    set_poison(0);
    set_strength(0);
    set_weight(0);
    set_value(0);
    set_raw(3);
}

void set_fish(int quality, int location){
    int variety;
    
    if(quality == 1){
        if(location == 1){
            variety = random(7);
            switch(variety){
                case 0 :
                    set_id(({"fish", "catfish"}));
                    set_short("%^CRST%^%^RESET%^%^C058%^c%^C059%^a%^C060%^tfi%^C059%^s%^C058%^h%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C066%^The flat-headed fish has 4 barbels protruding from the sides of its mouth and chin.%^CRST%^");
                    break;
                case 1 :
                    set_id(({"fish", "whiting"}));
                    set_short("%^CRST%^%^RESET%^%^C152%^wh%^C151%^iti%^C152%^ng%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C151%^This %^C150%^y%^C152%^e%^C151%^ll%^C152%^ow%^C150%^is%^C152%^h%^RESET%^%^C150%^ gr%^C152%^a%^C150%^y f%^C152%^i%^C150%^sh%^C151%^ has a %^C250%^si%^C247%^lv%^C243%^ery b%^C247%^el%^C250%^ly%^RESET%^%^C151%^. It has a distinctive %^C059%^black blotch%^RESET%^%^C151%^ near the base of its pectoral fin.%^CRST%^");
                    break;
                case 2 :
                    set_id(({"fish", "pompano"}));
                    set_short("%^CRST%^%^RESET%^%^C250%^p%^C247%^o%^C244%^m%^C243%^p%^C244%^a%^C247%^n%^C250%^o%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C255%^This %^C243%^si%^C245%^lv%^C247%^er%^C250%^y c%^C247%^ol%^C245%^or%^C243%^ed %^C245%^f%^C247%^i%^C249%^s%^C251%^h%^RESET%^%^C255%^ has sickle-shaped fins and a deeply forked tail.%^CRST%^");
                    break;
                case 3 :
                    set_id(({"fish", "bluefish"}));
                    set_short("%^CRST%^%^RESET%^%^C108%^bl%^C074%^ue%^C108%^f%^C074%^i%^C108%^sh%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C068%^The %^C108%^grayish %^C074%^blue-green %^C068%^coloring on this fish fades to %^C252%^white %^C068%^on the lower sides and belly. Its single row of teeth are quite sharp.%^CRST%^");
                    break;
                case 4 :
                    set_id(({"fish", "blowfish", "quest_item_blowfish"}));
                    set_short("%^CRST%^%^RESET%^%^C243%^bl%^C059%^o%^C243%^wfi%^C059%^s%^C243%^h%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C243%^Ve%^C059%^no%^C243%^mo%^C059%^us %^C243%^and %^C059%^pri%^C243%^ck%^C059%^ly, %^RESET%^%^C243%^th%^C059%^i%^C243%^s f%^C059%^i%^C243%^sh is %^C059%^gr%^C243%^a%^C059%^yi%^C243%^s%^C059%^h%^RESET%^%^C243%^ in c%^C059%^o%^C243%^lor a%^C059%^n%^C243%^d is %^C059%^do%^C243%^t%^C059%^ted%^C243%^ w%^C059%^i%^C243%^th %^C059%^bla%^C243%^c%^C059%^k s%^C243%^p%^C059%^ots%^C243%^.%^CRST%^");
                    break;
                case 5 :
                    set_id(({"fish", "flounder"}));
                    set_short("%^CRST%^%^RESET%^%^C058%^fl%^C059%^o%^C058%^un%^C059%^d%^C058%^er%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C058%^This brown fish is marked with %^C059%^spots%^C058%^ and %^C059%^blotches%^C058%^. Both eyes are always on the left side of the head as it lies on their right side.%^CRST%^");
                    break;
                case 6 :
                    set_id(({"crab", "blue crab"}));
                    set_short("%^CRST%^%^RESET%^%^C074%^b%^C068%^lu%^C074%^e %^C045%^crab%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C074%^Hard-bodied and hefty, this %^C068%^bluish crab%^C074%^ has five pairs of spindly %^C045%^p%^C074%^al%^C045%^e l%^C074%^eg%^C045%^s%^CRST%^%^C074%^, the foremost pair of which ends in claws.%^CRST%^");
                    break;
            }
            set_strength(10);
            set_weight(1);
            set_value(random(25) + 25);
            if(variety == 4) set_poison(1);
            return;
        }
        if(location == 2){
            variety = random(5);
            switch(variety){
                case 0 :
                    set_id(({"fish", "kingfish"}));
                    set_short("%^CRST%^%^RESET%^%^C109%^k%^C108%^i%^C102%^n%^C109%^gf%^C108%^i%^C102%^s%^C109%^h%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C109%^This is a medium sized, %^C108%^oli%^C109%^v%^C108%^e-h%^C109%^u%^C108%^ed fi%^C109%^s%^C108%^h%^RESET%^%^C109%^ with a %^C102%^si%^C244%^lv%^C248%^ery %^C244%^b%^C243%^el%^C102%^ly%^RESET%^%^C109%^ and a %^C183%^ro%^C189%^sy %^C195%^ir%^C231%^id%^C225%^es%^C219%^ce%^C213%^nc%^C219%^e%^RESET%^%^C109%^ on its side.%^CRST%^");
                    break;
                case 1 :
                    set_id(({"fish", "cobia"}));
                    set_short("%^CRST%^%^RESET%^%^C058%^co%^C059%^b%^C058%^ia%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C058%^This large flat-headed fish has %^C059%^beady eyes%^C058%^, a jutting lower jaw, and %^C064%^ni%^C059%^gh%^C060%^tma%^C059%^ri%^C064%^sh t%^C059%^e%^C060%^e%^C064%^th%^RESET%^%^C058%^ that line the jaws, the tongue, and the roof of the mouth.%^CRST%^");
                    break;
                case 2 :
                    set_id(({"octopus"}));
                    set_short("%^CRST%^%^RESET%^%^C137%^o%^C138%^c%^C139%^top%^C138%^u%^C137%^s%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C139%^This %^C138%^octopus%^C139%^ has a %^C144%^bulbous head%^C139%^ and eight %^C144%^su%^C138%^ck%^C144%^er-co%^C138%^ver%^C144%^ed te%^C138%^nt%^C144%^a%^C138%^cl%^C144%^es%^RESET%^%^C139%^ of nearly  feet in length.%^CRST%^");
                    break;
                case 3 :
                    set_id(({"turtle", "sea turtle"}));
                    set_short("%^CRST%^%^RESET%^%^C034%^s%^C041%^e%^C048%^a %^C084%^t%^C077%^u%^C070%^r%^C065%^t%^C072%^l%^C077%^e%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C077%^This %^C076%^sm%^C070%^oo%^C064%^th-sh%^C070%^el%^C076%^le%^C070%^d t%^C064%^ur%^C070%^tl%^C076%^e%^RESET%^%^C077%^ has a %^C064%^sp%^C058%^ot%^C059%^te%^C065%^d h%^C064%^ea%^C058%^d%^RESET%^%^C077%^ and big %^C064%^flippers%^C077%^ that allow it to dive deep beneath the waves.%^CRST%^");
                    break;
                case 4 :
                    set_id(({"fish", "mahi-mahi"}));
                    set_short("%^CRST%^%^RESET%^mahi-mahi%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C152%^This %^C151%^dazzling fish%^C152%^ is %^C142%^g%^C136%^o%^C148%^l%^C142%^d%^C136%^e%^C148%^n%^RESET%^%^C152%^ on the sides, with %^C081%^br%^C080%^ig%^C081%^ht b%^C080%^lu%^C081%^e%^RESET%^%^C152%^ and %^C078%^g%^C077%^ree%^C078%^n%^RESET%^%^C152%^ on the back, and %^C159%^ir%^C051%^id%^C087%^es%^C159%^ce%^C051%^nt %^C045%^b%^C044%^lu%^C045%^e f%^C044%^in%^C045%^s%^RESET%^%^C152%^.%^CRST%^");
                    break;
            }
            set_strength(30);
            set_weight(5);
            set_value(random(40) + 40);
            return;
        }
    }
    if(quality == 2){
        if(location == 1){
            variety = random(2);
            switch(variety){
                case 0 :
                    set_id(({"fish", "sea trout", "trout"}));
                    set_short("%^CRST%^%^RESET%^%^C142%^s%^C148%^e%^C136%^a %^C142%^t%^C148%^r%^C136%^o%^C142%^u%^C148%^t%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C148%^Prominent %^C227%^canine teeth%^C148%^ jut out from this fish's mouth. In the water, it takes on a %^C142%^g%^C148%^o%^C136%^ld%^C148%^e%^C142%^n s%^C148%^h%^C136%^e%^C148%^e%^C142%^n%^RESET%^%^C148%^.%^CRST%^");
                    break;
                case 1 :
                    set_id(({"fish", "mackerel"}));
                    set_short("%^CRST%^%^RESET%^%^%^C045%^m%^C050%^ac%^C045%^ke%^C050%^re%^C045%^l%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C029%^This slender fish has a %^C030%^b%^C037%^l%^C044%^u%^C051%^e-g%^C044%^r%^C037%^e%^C030%^e%^C037%^n %^C044%^s%^C051%^h%^C044%^e%^C037%^e%^C030%^n%^RESET%^%^C029%^, a %^C059%^s%^C244%^i%^C247%^l%^C250%^v%^C253%^e%^C255%^r%^C253%^y %^C250%^b%^C247%^e%^C244%^l%^C243%^l%^C059%^y%^RESET%^%^C029%^, and a deeply forked tail.%^CRST%^");
                    break;
            }
            set_strength(50);
            set_weight(10);
            set_value(random(1000) + 1000);
            return;
        }
        if(location == 2){
            variety = random(2);
            switch(variety){
                case 0 :
                    set_id(({"fish", "sailfish"}));
                    set_short("%^CRST%^%^RESET%^%^C019%^s%^C025%^ai%^C019%^lf%^C025%^is%^C019%^h%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C019%^This blue fish has a %^C087%^w%^C123%^h%^C159%^ite und%^C123%^e%^C087%^r%^C123%^b%^C159%^el%^C123%^l%^C087%^y%^RESET%^%^C019%^, and a %^C033%^spectacular%^C019%^ dorsal fin that is much higher than its body is thick.%^CRST%^");
                    break;
                case 1 :
                    set_id(({"fish", "swordfish", "quest_item_swordfish"}));
                    set_short("%^CRST%^%^RESET%^%^C244%^sw%^C247%^or%^C250%^d%^C247%^fi%^C244%^sh%^CRST%^");
                    set_long("%^CRST%^%^RESET%^%^C244%^This %^C059%^big-eyed fish%^C244%^ has a long, flattened bill that looks like a %^C253%^s%^C250%^w%^C245%^o%^C250%^r%^C253%^d%^RESET%^%^C244%^ and a broad crescent-shaped tail.%^CRST%^");
                    break;
            }
            set_strength(70);
            set_weight(20);
            set_value(random(1500) + 1500);
            return;
        }
    }
    return;
}

