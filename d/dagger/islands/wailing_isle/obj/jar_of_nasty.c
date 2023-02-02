// Chernobog & Titania (2/25/22)
// Wailing Isle - Jar of Nasty

inherit "/std/food.c";

void create(){
    ::create();
    set_name("jar of nasty");
    set_id(({"jar"}));
    set_short("%^RESET%^%^CRST%^small jar full of nasty stuff%^CRST%^");
    set_long("%^RESET%^%^CRST%^This is a dirty glass jar full of things you don't want.\n%^CRST%^");
    set_destroy();
    set_strength(40);
    set_weight(5);
    set_value(0);
    
    set_jar();
    set_my_mess("You open the jar and consume the questionable contents.");
    set_your_mess("opens a jar and pours the questionable contents into their mouth.");
}

void set_jar(){
    switch(random(4)){
        case 0 :
            set_id(({"jar", "jar of fish eyeballs", "jar of eyeballs", "jar of nasty"}));
            set_short("%^CRST%^%^RESET%^%^C195%^j%^C194%^a%^C102%^r %^C102%^o%^C186%^f %^C187%^f%^C188%^i%^C102%^s%^C195%^h %^C194%^e%^C193%^y%^C102%^eb%^C187%^a%^C188%^l%^C189%^l%^C102%^s%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C187%^This %^C101%^dirty glass jar%^C187%^ has been filled with a myriad of %^C188%^f%^C194%^i%^C230%^s%^C231%^h %^C195%^e%^C189%^y%^C188%^e%^C194%^b%^C230%^a%^C231%^l%^C195%^l%^C189%^s%^RESET%^%^C187%^, all %^C188%^bobbing%^C187%^ and %^C188%^swirling%^C187%^ around each other in some kind of %^C193%^brine%^C187%^. Even with a sealed lid, this jar reeks of the ocean.%^CRST%^");
            break;
        case 1 :
            set_id(({"jar", "jar of pickled fish guts", "jar of fish guts", "jar of nasty"}));
            set_short("%^CRST%^%^RESET%^%^C112%^jar of %^C106%^pi%^C107%^ck%^C113%^le%^C112%^d f%^C106%^is%^C107%^h g%^C113%^ut%^C112%^s%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C187%^This %^C101%^dirty glass jar%^C187%^ has been filled with a %^C114%^st%^C108%^ra%^C107%^ng%^C101%^e o%^C102%^li%^C106%^ve %^C114%^li%^C108%^qu%^C107%^id%^RESET%^%^C187%^ that smells heavily of %^C108%^vinegar%^C187%^. The %^C143%^vi%^C142%^sc%^C143%^er%^C144%^al %^C143%^le%^C142%^ft%^C143%^ov%^C144%^er%^C143%^s%^RESET%^%^C187%^ and refuse from %^C194%^filleting fish%^C187%^ seem to have been stored here for some unknown reason.%^CRST%^");
            break;
        case 2 :
            set_id(({"jar", "jar of jellyfish", "jar of nasty"}));
            set_short("%^CRST%^%^RESET%^%^C195%^jar of %^C188%^j%^C194%^e%^C230%^l%^C224%^l%^C225%^y%^C231%^f%^C195%^i%^C189%^s%^C188%^h%^RESET%^%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C195%^Blobs of %^C188%^tr%^C194%^an%^C230%^sl%^C224%^uc%^C225%^en%^C231%^t j%^C195%^el%^C189%^ly%^C188%^fi%^C194%^sh%^RESET%^%^C195%^ have been packed into this glass jar. You're not sure if they're still alive or not, as there's no room for any of them to move.%^CRST%^");
            break;
        case 3 :
            set_id(({"jar", "jar of octopus suckers", "jar of suckers", "jar of nasty"}));
            set_short("%^CRST%^%^RESET%^%^C187%^jar of %^C224%^oc%^C223%^to%^C222%^pu%^C221%^s s%^C222%^uc%^C223%^ke%^C224%^rs%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C187%^Strange %^C188%^w%^C194%^h%^C230%^i%^C224%^t%^C225%^i%^C231%^s%^C195%^h r%^C189%^i%^C188%^n%^C194%^g%^C230%^s%^RESET%^%^C187%^ float about each other within this %^C101%^dirty glass jar%^C187%^. They seem %^C194%^rough%^C187%^ and %^C194%^rubbery%^C187%^ and thoroughly disgusting.%^CRST%^");
            break;
    }
    return;
}

int is_quest_jar(){ return 1; }