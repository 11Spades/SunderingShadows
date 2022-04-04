// Chernobog & Titania (2/25/22)
// Wailing Isle - Seafood

inherit "/std/food.c";

void create(){
    ::create();
    set_name("seafood");
    set_id(({"seafood"}));
    set_short("%^RESET%^%^CRST%^piece of seafood%^CRST%^");
    set_long("%^RESET%^%^CRST%^Some piece of meat that used to live in the sea.\n%^CRST%^");
    set_destroy();
    set_poison(0);
    set_strength(0);
    set_weight(2);
    set_value(0);
    set_raw(3);
    
    set_seafood();
}

void set_seafood(){
    switch(random(5)){
        case 0 :
            set_id(({"seafood", "crab", "food"}));
            set_short("%^RESET%^%^CRST%^%^C189%^crab%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C189%^This %^C188%^hard-bodied %^C182%^hefty crab%^C189%^ has five pairs of %^C182%^sp%^C188%^in%^C194%^dl%^C188%^y p%^C182%^al%^C188%^e l%^C194%^eg%^C188%^s%^RESET%^%^C189%^, the foremost pair of which ends in %^C180%^claws%^RESET%^%^C189%^.%^CRST%^");
            set_strength(20);
            set_value(50);
            break;
        case 1 :
            set_id(({"seafood", "lobster", "food"}));
            set_short("%^RESET%^%^CRST%^%^C088%^lobster%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C088%^The %^C052%^darkly colored lobster%^C088%^ has some %^C053%^fierce%^C052%^ looking pincers and %^C059%^beady black eyes%^RESET%^%^C088%^.%^CRST%^");
            set_strength(40);
            set_value(200);
            break;
        case 2 :
            set_id(({"seafood", "shrimp", "food"}));
            set_short("%^RESET%^%^CRST%^%^C159%^shrimp%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C195%^This %^C194%^little monster%^C195%^ of the sea has a %^C117%^bluish tinged%^C195%^ tr%^C159%^ans%^C195%^l%^C159%^uce%^C195%^nt b%^C159%^od%^RESET%^%^C195%^y you can stare right into.%^CRST%^");
            set_strength(10);
            set_value(10);
            break;
        case 3 :
            set_id(({"seafood", "octopus", "food"}));
            set_short("%^RESET%^%^CRST%^%^C144%^octopus%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C144%^That %^C138%^bulbous head%^C144%^, %^C243%^empty eye sockets%^C144%^ and eight %^C143%^su%^C137%^ck%^C143%^er-co%^C137%^ver%^C143%^ed ar%^C137%^m%^C143%^s%^RESET%^%^C144%^ look so appetizing...%^CRST%^");
            set_strength(30);
            set_value(80);
            break;
        case 4 :
            set_id(({"seafood", "shark fillet", "food"}));
            set_short("%^RESET%^%^CRST%^%^C243%^shark fillet%^CRST%^");
            set_long("%^RESET%^%^CRST%^%^C243%^This %^C247%^juicy %^C253%^white filet%^C243%^ is still wrapped in its %^C059%^thick dark skin%^RESET%^%^C243%^.%^CRST%^");
            set_strength(50);
            set_value(350);
            break;
    }
    return;
}

