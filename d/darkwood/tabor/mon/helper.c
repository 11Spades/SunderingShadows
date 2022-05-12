// Original code by Vanadis
// Low Level Quest Helper
// Updated by Chernobog & Titania (5/11/22)

#include <std.h>
#include <move.h>
inherit NPC;

int queststep;


void create(){
    ::create();
    set_name("Cynthia");
    set_id(({"Cynthia", "cynthia", "old woman", "old lady", "woman", "lady", "storyteller", "aged woman", "grandma"}));
    set_short("%^CRST%^%^RESET%^%^C138%^Cynthia, an %^C139%^old lady%^C138%^ in a %^C137%^rocking chair%^CRST%^ [%^C153%^knitting%^CRST%^]");
    set_long("%^CRST%^%^RESET%^%^C153%^This old woman has %^C243%^gr%^C245%^iz%^C247%^zl%^C243%^ed %^C245%^gr%^C247%^ay %^C243%^ha%^C245%^ir%^RESET%^%^C153%^ and %^C144%^wri%^C137%^nk%^C144%^led s%^C137%^k%^C144%^in%^RESET%^%^C153%^. She wears an %^C182%^old-f%^C111%^a%^C182%^shio%^C111%^n%^C105%^e%^C182%^d dre%^C105%^s%^C182%^s%^C153%^ and a %^C182%^la%^C111%^r%^C105%^g%^C182%^e sh%^C111%^a%^C105%^w%^C182%^l%^RESET%^%^C153%^. Her eyes are clear and piercing when she looks at people passing through the hall, but most of the time she is occupied with her %^C069%^knitting%^C153%^. She rocks back and forth in her chair while her knitting needles clank rapidly and rhythmically.%^CRST%^\n");
    set_gender("female");
    set_race("human");
    set_body_type("human");
    set_hd(2,1);
    set_stats("strength",6);
    set_stats("charisma",12);
    set_stats("dexterity",6);
    set_stats("constitution",12);
    set_stats("wisdom",22);
    set_stats("intelligence",18);
    set_exp(1);
    force_me("speech say lightly");
    set_spoken("wizish");

    queststep = 0;
}

void catch_say(string msg){
    object player;
    
    player = this_player();
    if(!userp(player)) return;
    if(player->query_invis()){
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M stirs.%^CRST%^");
        force_me("say Who's there?");
        return;
    }
    call_out("reply_func", 1, msg, player);
}

void reply_func(string msg, object player){
    object current, obj;

    if(!msg || !objectp(player)) return;

    if(strsrch(msg,"Hi") != -1 || strsrch(msg,"hail") != -1 || strsrch(msg,"reeting") != -1 || strsrch(msg,"ello") != -1 || strsrch(msg,"Hail") != -1){
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M glances up from her knitting to look at you.%^CRST%^");
        if(player->query_level() > 15){
            force_me("say Hello dear. I don't think I have any %^C153%^tips%^CRST%^ an accomplished adventurer like you don't already know.");
            force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$Mat cynthia %^CRST%^%^RESET%^%^C138%^$M smiles affably.%^CRST%^");
            return;
        }
        force_me("say Hello dear. My name is Cynthia, but everybody calls me grandma. You may not believe me, but I once was an adventurer like you!");
        force_me("say Ask me for %^C153%^tips%^RESET%^, perhaps these old bones has some wisdom in them still.");

        if(member_array("An invitation for Rosinden", this_player()->query_mini_quests()) == -1){
            force_me("say Oh, and while you're here... Could you do me a favor? Would you bring this letter to Rosinden?");
            queststep = 1;
        }
        return;
    }
    
    if(strsrch(msg,"tip") != -1 || strsrch(msg,"advice") != -1 || strsrch(msg,"Tip") != -1 || strsrch(msg,"Advice") != -1 || strsrch(msg,"knowledge") != -1 || strsrch(msg,"Knowledge") != -1 || strsrch(msg,"wisdom") != -1 || strsrch(msg,"Wisdom") != -1){
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M nods as she rocks her chair.%^CRST%^");
        force_me("say There are two places a new adventurer could try their luck. The first is the %^C153%^goblin keep%^CRST%^, just southeast of Tabor. The second are the %^C153%^Ekibi caverns%^CRST%^ to the north, past the Meadowlands. ");
        force_me("say But before heading out of town, I would recommend you get a %^C153%^map%^RESET%^ of the surrounding area. The %^C153%^scribe%^CRST%^ is a darling, I'm sure you'll get one for free if you ask nicely.");
        force_me("say Or did you have any other %^C153%^questions%^CRST%^, dear?");
        return;
    }

    if(strsrch(msg,"knitting") != -1 ){
        force_me("say I'm knitting a pair of nice, warm woolen socks. I can't find my old pair - The goblins must have stolen them, that's what I'm thinking!");
        return;
    }


    if(strsrch(msg,"question") != -1  || strsrch(msg,"Question") != -1 ){
        force_me("say You can ask me for %^C153%^tips%^CRST%^, dear. Or I can tell you about %^C153%^Tabor%^CRST%^ and the surrounding %^C153%^areas%^RESET%^.");
        force_me("say I don't pay much attention to %^C153%^rumors%^CRST%^ these days, but I might have heard of a %^C153%^quest%^CRST%^ or two. Perhaps I can point the way if you need directions. ");
        return;
    }

    if(strsrch(msg,"scribe") != -1 || strsrch(msg,"Scribe") != -1 ){
        force_me("say The scribe's shop is in the center of Tabor, just opposite the general store, south of the bank.");
        return;
    }

    if(strsrch(msg,"rumors") != -1 || strsrch(msg,"Rumors") != -1 ){
        force_me("say Let's see... I could tell you where to find the %^C153%^Goblin Keep%^CRST%^, the %^C153%^Ekibi Caverns%^CRST%^, the %^C153%^Dragon Den's caves%^CRST%^, the %^C153%^Grasslands%^CRST%^, the %^C153%^Meadowland%^CRST%^, the %^C153%^Orc Cave%^CRST%^, the %^C153%^Echoes Mountain%^CRST%^, %^C153%^Koenig%^CRST%^, the %^C153%^Darkwood Forest%^CRST%^, %^C153%^Shadow%^CRST%^ and %^C153%^Rhapsody%^CRST%^.");
        force_me("say I might know of a few other places as well. What rumors have you heard?");
        tell_object(player, "\n%^BOLD%^%^GREEN%^Use the command <rumors> to see a list of areas appropriate for your level.%^RESET%^");
        return;
    }

    if(strsrch(msg,"map") != -1 || strsrch(msg,"Map") != -1 ){
        force_me("say Every adventurer should study maps before they head out! The %^C153%^scribe%^CRST%^ can give you one, or you can take a look at the map in the %^C153%^tavern%^RESET%^.");
        return;
    }

    if(strsrch(msg,"Dragon Den") != -1 || strsrch(msg,"dragon den") != -1  || strsrch(msg,"Dragon den") != -1 ){
        force_me("say From the %^C153%^Meadowlands%^CRST%^ you need to go east quite a bit along the Quiet Forest Road. Take the road north to the %^C153%^Echoes mountains%^CRST%^. Find the dwarves' mine. The Dragon Den's caverns are due east from the mines.");
        return;
    }

    if(strsrch(msg,"Echoes mountains") != -1 || strsrch(msg,"echoes mountains ") != -1   || strsrch(msg,"Echoes Mountains") != -1){
        force_me("say From the %^C153%^Meadowlands%^CRST%^ you need to go east quite a bit along the Quiet Forest Road. There's a road going north to the Echoes Mountains. There's a big sign where the road forks to the north. You can't miss it!");
        return;
    }

    if(strsrch(msg,"Meadowland") != -1 || strsrch(msg,"meadowland") != -1 ){
        force_me("say Go out the northwestern gate, then follow the road northwest past the %^C153%^grasslands%^CRST%^. Continue north, then west and north again. You should be safe as long as you stick to the path. ");
        return;
    }

    if(strsrch(msg,"Grassland") != -1 || strsrch(msg,"grassland") != -1 ){
        force_me("say The grasslands are very close. Go out the northwestern gate, then follow the road northwest.");
        return;
    }

    if(strsrch(msg,"nereid") != -1 || strsrch(msg,"Nereid") != -1 || strsrch(msg,"riddle") != -1 || strsrch(msg,"Riddle") != -1){
        force_me("say Some say a nereid rewards to adventurers who answer her riddles correctly. ");
        force_me("say She's said to live near Koenig. It's just a rumor, dear. I have no idea where the nereid is, or if she's even real! But aren't nereids nymphs of streams and oceans?");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M nods.%^CRST%^");
        force_me("say I would look near water if I were to try and find her.");
        return;
    }

    if(strsrch(msg,"orc cave") != -1 || strsrch(msg,"Orc cave") != -1 || strsrch(msg,"Orc Cave") != -1 ){
        force_me("say The orc cave is just southeast of the ruined village of %^C153%^Koenig%^CRST%^. ");
        return;
    }

    if(strsrch(msg,"village") != -1 || strsrch(msg,"Village") != -1 || strsrch(msg,"Koenig") != -1 || strsrch(msg,"koenig") != -1 ){
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M frowns grimly.%^CRST%^");
        force_me("say A terrible thing, what happened to Koenig... All the dead people...");
        force_me("say To find the ruined village of Koenig, go out the northwestern gate. Then follow the road northeast. When you reach the fork in the road, go north across the streams.");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M sighs heavily and continues to knit.%^CRST%^");
        return;
    }

    if(strsrch(msg,"Darkwood") != -1 || strsrch(msg,"darkwood") != -1  ){
        force_me("say The Darkwood forest is southeast of %^C153%^Shadow%^CRST%^.");
        return;
    }

    if(strsrch(msg,"tavern") != -1 || strsrch(msg,"Tavern") != -1 ){
        force_me("say There's a nice tavern south of here, just past the stables. There's a map in the common hall, and they serve the most delicious deer eyes!");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M giggles to herself.%^CRST%^");
        return;
    }

    if(strsrch(msg,"Rhapsody") != -1 || strsrch(msg,"rhapsody") != -1 ){
        force_me("say Rhapsody was where all the adventurers met back in my days!");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M giggles with delight.%^CRST%^");
        force_me("say It's a lovely little inn with the best ale on the continent. It's southwest of %^C153%^Shadow%^CRST%^, past the road to %^C153%^Darkwood Forest%^CRST%^. ");
        return;
    }

    if(strsrch(msg,"abor") != -1 ){
        force_me("say This is such a lovely town, don't you think? It's a quiet place, except for those blasted goblins! When you get tired of this this lazy old town, you might want to go to %^C153%^Shadow%^CRST%^ next.");
        return;
    }

    if(strsrch(msg,"randma") != -1 || strsrch(msg,"Cynthia") != -1 ){
        force_me("say I had such adventures when I was your age! Yes, I lived fully, even though I never had any children of my own. And now in my old age I find it a true pleasure helping young adventurers like yourself.");
        return;
    }

    if(strsrch(msg,"help") != -1 || strsrch(msg,"Help") != -1 ){
        force_me("say Do you need help, dear? Perhaps I can help. It's many years since my adventuring days, but I might have some %^C153%^tips%^CRST%^ for you. ");
        return;
    }

    if(strsrch(msg,"city") != -1 || strsrch(msg,"country") != -1 || strsrch(msg,"cities") != -1 || strsrch(msg,"area") != -1 || strsrch(msg,"world") != -1 ){
        force_me("say There are many cities in the world you can visit. Go ask the %^C153%^scribe%^CRST%^ for a %^C153%^map%^CRST%^ if you haven't done so already. There is also a map in the %^C153%^tavern%^CRST%^ just east of the stables to the south.");
        force_me("say When you get tired of this this lazy old town, you might want to go to %^C153%^Shadow%^CRST%^ next.");
        return;
    }

    if(strsrch(msg,"hadow") != -1 ){
        force_me("say Shadow is a magnificent city if ever I saw one! But what makes it so special is that it is very well connected indeed. Shadow has a portal service that quickly lets you travel all over the world! ");
        force_me("say Shadow lies east of %^C153%^Tabor%^CRST%^. You can walk there of course, both the northern road and the southern road eventually takes you there. But the quickest way to get there is the river %^C153%^ferry%^CRST%^. ");
        force_me("say When I was young, I often met adventurers like you in the town square in Shadow. It's a good place to go to make new friends and perhaps get yourself a travel companion. Or you could just try the %^C153%^tavern%^CRST%^ of course.");
        return;
    }

    if(strsrch(msg,"adventure") != -1 || strsrch(msg,"Adventure") != -1){
        force_me("say Oh yes, I was an adventurer!");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M nods to herself.%^CRST%^");
        force_me("say Come back some day, we can have some tea and share stories.");
        return;
    }

    if(strsrch(msg,"ferry") != -1 || strsrch(msg,"Ferry") != -1){
        force_me("say The ferry takes you all the way to %^C153%^Shadow%^CRST%^. You'll find the dock just southwest of Tabor. ");
        return;
    }

    if(strsrch(msg,"Tharis") != -1 || strsrch(msg,"tharis") != -1){
        force_me("say Don't go to Tharis, dear. It's a city full of thieves.");
        return;
    }

    if(strsrch(msg,"quest") != -1 || strsrch(msg,"Quests") != -1){
        force_me("say There is a %^C153%^gnome%^CRST%^ who owns a farm north of Tabor. I hear he's in trouble.");
        force_me("say There are also rumors of a beautiful %^C153%^nereid%^CRST%^ in a cave. They say she gives rewards to those who answers her riddles... But who knows how many didn't live to warn about the danger?");
        force_me("say Oh, and I almost forgot, there's a %^C153%^collector%^CRST%^ searching for lost items. You'll find the collector in the %^C153%^tavern%^CRST%^.");
        return;
    }

    if(strsrch(msg,"goblin") != -1 ){
        force_me("say The goblins are a nuisance to the town! And the guards aren't doing a good job keeping them in check, bless their hearts. The keep is just south of %^C153%^Tabor%^CRST%^.");
        return;
    }

    if(strsrch(msg,"Ekibi") != -1 ){
        force_me("say The Ekibi caves are far from here, but %^C153%^Rosinden%^CRST%^ might make it worth your trouble if you need bit of gold.");
        force_me("say To find the caves, go out the northwestern gate, then follow the road northwest to the %^C153%^grasslands%^CRST%^. Continue north. The caves are northeast of the %^C153%^Meadowlands%^CRST%^. Bring a %^C153%^map%^CRST%^ in case you get lost.");
        return;
    }

    if(strsrch(msg,"osinden") != -1 ){
        force_me("say Rosinden needs... minerals... or something... Go talk to her. You'll find her near the %^C153%^Ekibi caverns%^CRST%^.");
        return;
    }

    if(strsrch(msg,"eep gnome") != -1 ){
        force_me("say I'm not entirely sure where the deep gnome caves are, dear. My guess is they're under the chasm. You have to go north from Shadow along the Dragon Pass road, past the Dragon's Den mountains. When you have passed the crossroads, take the next eastern exit, and you'll find the crack in the earth somewhere around there.");
        return;
    }

    if(strsrch(msg,"gnome") != -1 || strsrch(msg,"Gnome") != -1 || strsrch(msg,"farm") != -1 || strsrch(msg,"Farm") != -1 || strsrch(msg,"Piaf") != -1 || strsrch(msg,"piaf") != -1){
        force_me("say North of Tabor is the abandoned village of %^C153%^Koenig%^CRST%^. Southwest of that village you will find the gnome's farm.");
        return;
    }

    if(strsrch(msg,"collector") != -1 || strsrch(msg,"Collector") != -1){
        force_me("say The collectors are searching for lost items. There's always one in the %^C153%^tavern%^CRST%^. The items are spread all over the place. ");
        force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M frowns.%^CRST%^");
        force_me("say It might be a trick to get you killed, so be careful!");
        return;
    }

    if(strsrch(msg,"Centaur") != -1 || strsrch(msg,"centaur") != -1){
        force_me("say I hear there are some centaurs who live in the Yntala forest, on the eastern side of the river. Their home is hidden though, so you will have to search for it.");
        return;
    }

    if(strsrch(msg,"yntala") != -1 || strsrch(msg,"Yntala") != -1){
        force_me("say Yntala forest is the large forest south of Tabor. A river runs though it, but there are places to cross the river if you search for them. ");
        return;
    }

    if(strsrch(msg,"kildare") != -1 || strsrch(msg,"Kildare") != -1){
        force_me("say Kildare Glen is a lovely little village northwest of Shadow. You'll get there by following the rocky path from north of the the old wagon trail. An alternative route would be to go to the meadowlands, then take the abandoned trail northwards until you reach the fence. Jump the fence and you're there.");
        return;
    }

    if(strsrch(msg,"muileann") != -1 || strsrch(msg,"Muileann") != -1){
        force_me("say Muileann is a small hidden town northeast of Shadow. It is a good place for adventurers to gain some experience, but I imagine it's a terrible place to live... ");
        force_me("say Go north from Shadow until you reach a crossroads with the old wagon trail heading west and a dusty road going east. Travel east from there to the vast corn field. Northeast of the field you will find a sign and the entrance to Muileann. ");
        return;
    }

    if(strsrch(msg,"cryptkeeper") != -1 || strsrch(msg,"Cryptkeeper") != -1){
        force_me("say I've heard of a cryptkeeper in Muileann, yes. He'd probably be near the graveyard.");
        return;
    }


    if(strsrch(msg,"gentleman") != -1 || strsrch(msg,"Gentleman") != -1){
        force_me("say The rumor is there's a tower in Muileann where the dreaded gentleman can be found. If you plan to go there, bring some extra food and perhaps a bloodshard if you can afford one.");
        return;
    }

    if(strsrch(msg,"bloodshard") != -1 || strsrch(msg,"Bloodshard") != -1){
        force_me("say There are times you will find yourself caught in a place you cannot easily leave not even with magic. A bloodshard can get you out of such places. I recommend always to carry at least one with you on your journeys.");
        return;
    }

    if(strsrch(msg,"pyramid") != -1 || strsrch(msg,"Pyramid") != -1){
        force_me("say There are some pyramids in Yntala, but they're hard to find, even for those with magical sight. I asked an old wizard about it once. He laughed at me and said 'It's all about what you wear.' Whatever that means.");
        return;
    }

    if(strsrch(msg,"feyren") != -1 || strsrch(msg,"Feyren") != -1 || strsrch(msg,"spider") != -1 || strsrch(msg,"Spider") != -1 ){
        force_me("say Last I heard Feyren farm is still swarming with spiders. You'll find it just west of Shadow. There are some caves down in the basement, and if you search thoroughly you might find some hidden places. ");
        return;
    }

    if(strsrch(msg,"dark trail") != -1 || strsrch(msg,"Dark Trail") != -1 || strsrch(msg,"Dark trail") != -1 ){
        force_me("say The dark trail is east of Antioch. From there, go as far east as you can, then follow the trail north.");
        return;
    }

    if(strsrch(msg,"King's forest") != -1 || strsrch(msg,"king's forest") != -1 || strsrch(msg,"King's Forest") != -1 || strsrch(msg,"kings forest") != -1 || strsrch(msg,"Kings Forest") != -1 ){
        force_me("say The king's forest is west of Antioch.");
        return;
    }

    if(strsrch(msg,"Antioch") != -1 || strsrch(msg,"antioch") != -1  ){
        force_me("say Antioch is a beautiful city north of Shadow, and well worth a visit. Follow the Dragon Pass Road northwards through the Charu mountains. Eventually you will find some desolate ruins. Head west from there and you'll reach Antioch.");
        return;
    }

    if(strsrch(msg,"gore") != -1 || strsrch(msg,"Gore") != -1){
        force_me("say Gore is a leader among the orcs. He has a camp west of the Meadowlands.");
        return;
    }

    if(queststep == 1 && (strsrch(msg,"yes") != -1|| strsrch(msg,"Yes") != -1|| strsrch(msg,"I will")!= -1)){
        object invitation;

        tell_object(player,"Cynthia looks under her shawl and produces a piece of paper.");
        invitation = new("/d/darkwood/tabor/obj/invitation.c");
        if((int)(invitation->move(player))!= MOVE_OK){
            force_me("say Thank you, dear. What's that, you have your hands full? I'll leave the letter to Rosinden here.");
            force_me("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M places the piece of paper on the floor.%^CRST%^");
            invitation->move(environment(player));
            queststep = 0;
            return 1;
        }
         else{
            force_me("say Thank you, dear, Here it is, a letter to Rosinden.");
            tell_room(environment(this_object()),"Cynthia gives a piece of paper to "+TPQCN+"",player);
            tell_object(player,"Cynthia hands you a piece of paper.");
            invitation->move(player);
            queststep = 0;
            return 1;
        }
    }

    force_me("say Sorry dear, what was that? Speak up please.");
    return;
}

void init(){
    object player;
    
    ::init();

    player = this_player();
    setup();
    if(player->query_level() > 8) return;
    if(!userp(player)){
        return;
    }

    if (player->query_invis()) {
        return;
    }

    // Seems not to work, possibly because the room is in a temple dir, not in Tabor's dir?
    //   if (query_bad_race(TP)) {
    //        return;
    //   }

    call_out("notify_newcomers", 1);
}

void notify_newcomers(){
    if(member_array("An invitation for Rosinden", this_player()->query_mini_quests()) == -1) {
        command("emoteat cynthia %^CRST%^%^RESET%^%^C138%^$M looks up with a friendly smile.%^CRST%^");
        command("say Hello there, dear.");
    }
}

void setup(){
    // I encountered a problem with set_emote. They didn't trigger if I left the room
    // and returned. This was a problem whether the code was in create or init.
    // For some reason this works, putting the code in a setup function
    // and calling it from init. - Vanadis

    set_emotes(10,({
        "%^CRST%^%^RESET%^%^C138%^Cynthia rocks in her chair.%^CRST%^",
        "%^CRST%^%^RESET%^%^C138%^Cynthia coughs and takes a deep breath.%^CRST%^",
        "%^CRST%^%^RESET%^%^C138%^Cynthia knits intently.%^CRST%^",
        "%^CRST%^%^RESET%^%^C138%^Cynthia closes her eyes and slumbers for a few moments.%^CRST%^"}),0);
}

