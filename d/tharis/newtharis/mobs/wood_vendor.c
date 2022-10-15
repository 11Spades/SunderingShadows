#include <std.h>
#include "../tharis.h"

inherit VENDOR;

void create() {
 ::create();
  set_gender("female");
  set_name("Agnes Demsy, wood dealer");
  set_race("human");
  set_alignment(5);
  set_hd(50,8);
  set_hp(8000);
  set_stats("strength",16);
  set_stats("dexterity",14);
  set_stats("constitution",18);
  set_stats("wisdom",20);
  set_stats("intelligence",20);
  set_stats("charisma",14);
  set_items_allowed("material");
  set_id(({ "Agnes", "agnes", "vendor","dealer","wood vendor"}));
  set_short("%^RESET%^%^C088%^Agnes Demsy%^RESET%^%^C058%^, %^RESET%^%^C094%^w%^C130%^o%^C136%^o%^C094%^d %^RESET%^%^C058%^dealer%^CRST%^");
  set_long("%^RESET%^%^C058%^A %^RESET%^%^C248%^w%^C249%^i%^C250%^t%^C251%^h%^C250%^e%^C249%^r%^C248%^e%^C247%^d %^RESET%^%^C248%^c%^C249%^r%^C250%^o%^C249%^n%^C248%^e %^RESET%^%^C058%^of a human woman stands hunched in her stall surrounded by piles of clearly labeled %^RESET%^%^C094%^w%^C130%^o%^C136%^o%^C094%^d%^RESET%^%^C058%^. Her weathered face is possessed of an oversized nose with flared nostrils and heavy, wrinkled eyelids that make her %^RESET%^%^C240%^eyes %^RESET%^%^C058%^seem especially %^RESET%^%^C241%^b%^C242%^e%^C243%^a%^C242%^d%^C241%^y%^RESET%^%^C058%^. When she grins her %^RESET%^%^C241%^missing teeth %^RESET%^%^C058%^are as noticeable as the jagged %^RESET%^%^C230%^y%^C228%^e%^C230%^l%^C221%^l%^C230%^o%^C227%^w %^RESET%^%^C058%^ones which remain. A %^RESET%^%^C101%^roughspun dress %^RESET%^%^C058%^covered in %^RESET%^%^C230%^saw dust %^RESET%^%^C058%^and %^RESET%^%^C144%^splinters %^RESET%^%^C058%^adorns her bony, bent body and her %^RESET%^%^C255%^m%^C254%^a%^C253%^t%^C254%^t%^C253%^e%^C252%^d %^RESET%^%^C255%^h%^C254%^a%^C253%^i%^RESET%^%^C255%^r %^RESET%^%^C058%^likewise seems to have been dragged across a %^RESET%^%^C136%^lumberyard %^RESET%^%^C058%^floor. Her gnarled fingers are stained %^RESET%^%^C240%^black%^RESET%^%^C058%^ and she watches the crowd in the bazaar with %^RESET%^%^C024%^k%^C031%^e%^C038%^e%^C045%^n %^RESET%^%^C045%^i%^C038%^n%^C031%^t%^C024%^e%^C031%^r%^C038%^e%^C045%^s%^C038%^t%^RESET%^%^C058%^, most notably in the %^RESET%^%^C051%^y%^C087%^o%^C123%^u%^C159%^n%^C123%^g%^C087%^e%^C051%^r %^RESET%^%^C058%^children who are present.%^CRST%^\n%^RESET%^%^C244%^Use %^RESET%^%^C015%^<list>%^RESET%^%^C244%^ to view her wares and %^RESET%^%^C015%^<help shop>%^RESET%^%^C244%^ to learn how to buy.%^CRST%^");
  set_storage_room(STORAGE"wood_vendor.c");

 
}