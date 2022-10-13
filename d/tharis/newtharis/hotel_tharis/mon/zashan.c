// Chernobog (1/9/22)
// Pokiir Dealer - Designed by Maenoh

#include <std.h>

inherit "/d/shadow/mon/dealer.c";

void create(){
	::create();
	set_name("Zashan");
	set_id(({"zashan","dealer","card dealer","Zashan"}));
	set_short("%^RESET%^%^C028%^Z%^C034%^a%^C042%^s%^C082%^h%^C034%^a%^C028%^n%^RESET%^%^C058%^, a card dealer%^RESET%^");
	set_long("%^RESET%^%^C058%^Zashan is an %^C074%^en%^C075%^i%^C074%^gm%^C073%^a%^C074%^t%^C075%^i%^C074%^c %^C058%^man with a %^C094%^swarthy %^C058%^complexion and %^RESET%^C241%^l%^C245%^u%^C241%^str%^C250%^o%^C245%^u%^C241%^s black hair %^RESET%^%^C058%^that he keeps slicked back from his handsome face. Beneath full %^C241%^brows %^RESET%^%^C058%^are a pair of %^RESET%^%^C028%^v%^C034%^e%^C042%^r%^C082%^i%^C034%^d%^C034%^i%^C028%^an e%^RESET%^%^C076%^y%^C034%^e%^C028%^s%^RESET%^%^C058%^, their %^RESET%^%^C035%^cry%^C120%^st%^C122%^al%^C120%^l%^RESET%^%^C035%^ine %^C058%^depths bisected by vertically sl%^RESET%^%^C241%^i%^RESET%^%^C058%^t %^RESET%^%^C241%^pupils%^RESET%^%^C058%^. His aquiline nose rests above a wide mouth that smiles easily, revealing glimpses of a %^C138%^forked tongue %^RESET%^%^C058%^and %^C230%^fangs%^RESET%^%^C058%^. He is well-dressed in a %^RESET%^%^C015%^white linen shirt%^C058%^, the sleeves rolled up to the elbows, a %^RESET%^%^C102%^tw%^C101%^e%^C103%^e%^C102%^d vest%^C058%^, and %^C242%^charcoal gray trousers%^RESET%^%^C058%^. His long, lean form lounges confidently in his seat at the head of the Pokiir table.%^RESET%^");
	   set_gender("male");
	   set_race("yuan-ti");
	   set_hd(30,5);
	   set_alignment(5);
	   set_max_hp(900);
	   set_hp(query_max_hp());
	   set_overall_ac(-30);
	   set_class("fighter");
	   set_mlevel("fighter",30);
	   set("aggressive",0);
}

