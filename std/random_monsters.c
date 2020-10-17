/* 11/29/02 enhancing flexibility to allow changing choices of mobs if prior ones get dested, and allow limiting how often they will re-spawn by setting random chance (as noted)
Also cleans up controlled mobs when the room cleans up (or prevents clean up if the mobs are interracting - combat or in a room with a user)
See /doc/help/tutorials/poster-l-croom or refer to topic "l" on the poster in the builders lounge for proper usage and examples
*Styx*
*/

// added to make it ignore repop rate on first load *Styx*  3/19/05


// added monster_party(int mon_speed) and form_monster_party(int speed) to maintain
// consistency with CROOM. Setting a speed of -1 will make a stationary
// party of otherwise moving mobs - Ares 8/21/05

//Moved to 1 file - not sure why we ever did two different ones to begin with - Saide - April 2016

#include <std.h>
#include <move.h>
#define VOID "/d/shadowgate/void"


int interacting_mob(object ob);
void form_monster_party(int speed);
void place_mobs();
nosave int repop;
int mon_speed;

nosave mapping mons;

void create()
{
    if(!mapp(mons)) mons = ([]);
    if(!intp(mon_speed)) mon_speed = 0;
    if(!intp(repop)) repop = random(100);
    return;
}

query_monsters() { return mons; }

set_monsters(string *files, int * amounts){
   int i,j;
   if(!mons) mons = ([]);

   	if(sizeof(files) != sizeof(amounts))
	{
    	return;
   	}
// added function to allow changing what it spawns/controls during longer reboots
// this check prevents re-assignment if there are mobs left alive from previous set
   	if(has_mobs())   return;
    //if the below is commented out as I found it - then it just adds to the monsters, does not change them - Saide - April 2016
	mons = ([]);
   	j = sizeof(files);
   	for(i=0;i<j;i++)
	{
      mons[files[i]] = allocate(amounts[i]);
   	}
}

void monster_party(int speed) {
    if(speed) { mon_speed = speed; return; }
}

void place_mobs()
{
    string *aKeys;
    object CroomMon;
   	int i,j,k,l, pflag, rnum;
    mixed catch_error;
// added this to check if should repop any given reset based on chance set in room
   	if(!repop) repop = random(100);
// added to make it ignore repop rate on first load *Styx*  3/19/05
    rnum = (int)TO->query_reset_number();
    TO->remove_property("lastresetmobs");
    TO->set_property("lastresetmobs", rnum);
   	if(repop < random(100) && rnum > 1)  return;
    if(mapp(mons) && mons != ([]))
	{
        aKeys = keys(mons);
        j = sizeof(aKeys);
        for(i=0;i<j;i++)
        {
            l = sizeof(mons[aKeys[i]]);
            for(k=0;k<l;k++)
            {
                if(!objectp(mons[aKeys[i]][k]))
                {
                    if(catch_error = catch(CroomMon = new(aKeys[i])))
                    {
                        log_file("errors/mob_load", "Monster Failed to Load - Error was = "+identify(catch_error)+". Happened in "+file_name(TO)+" on file "+identify(aKeys[i])+". Attempting to "+
                        "clone again.\n");
                        if(catch_error = catch(CroomMon = new(aKeys[i])))
                        {
                            log_file("errors/mob_load", "Monster failed to load - Error was = "+identify(catch_error)+". Happened in "+file_name(TO)+" on file "+identify(aKeys[i])+" twice.\n");
                            continue;
                        }
                    }
                    //CroomMon = new(aKeys[i]);
                    if(objectp(CroomMon))
                    {
                        mons[aKeys[i]][k] = CroomMon;
                        CroomMon->set_property("croom_track",1);
                        if(CroomMon->move(TO) != MOVE_OK)
                        {
                            log_file("errors/mob_load", base_name(TO) + " failed to move "+base_name(mons[aKeys[i][k]]) + " in reset.");
                        }
                        else pflag = 1;
                    }
                }
                continue;
            }
        }
    }
    if(mon_speed && pflag) { form_monster_party(mon_speed); } // called if speed is set with monster_party() -Ares
    return;
}


void reset()
{
    //find object or load efun will call
    //place mobs now on the first reset, after the
    //reset is all the way finished - does this fix
    //the too deep recursion errors in new()? Saide, December 2016
    //if((int)TO->query_reset_number() < 2) return;
    //place_mobs();
    return;
}

// this function added to check if mobs exist before allowing to change
int has_mobs()
{
	string *aKeys;
   	int i,j,k,l, active;
  	active = 0;
    if(mapp(mons) && mons != ([]))
    {
        aKeys = keys(mons);
        j = sizeof(aKeys);
        for(i=0;i<j;i++)
        {
            l = sizeof(mons[aKeys[i]]);
            for(k=0;k<l;k++)
            {
                if(objectp(mons[aKeys[i]][k]))
                {
                    active++;
                    break;
                }
                continue;
            }
            if(active) break;
            continue;
        }
    }
    return active;
}

void form_monster_party(int speed)
{
    string *aKeys;
    int i,j,k,l;
    object leader,guard;

    if(!has_mobs()) { return; }
    if(speed == -1) { speed = 0; }

    if(mapp(mons) && mons != ([]))
    {
        aKeys = keys(mons);
        j = sizeof(aKeys);
        for(i=0;i<j;i++)
        {
            l = sizeof(mons[aKeys[i]]);
            for(k=0;k<l;k++)
            {
                if(objectp(mons[aKeys[i]][k]))
                {
                    guard = mons[aKeys[i]][k];
                    if(environment(guard) != TO) { continue; }
                    if(!leader)
                    {
                        leader = guard;
                        leader->set_speed(speed);
                        continue;
                    }
                    guard->set_speed(0);
                    leader->add_follower(guard);
                    continue;
                }
            }
            continue;
        }
    }
    return;
}

// added so can set in room to control random chance on reset of re-spawning *Styx*
void set_repop(int chance) {
   repop = chance;
}

int query_repop() { return repop; }

int interacting_mob(object mob) {
    object *inv;
    int i;

    if (!objectp(mob)) return 0;
    if ( !environment(mob) ) return 0;
    if ( sizeof(mob->query_attackers()) != 0 ) return 1;
    if (!environment(mob)->query_property("croom_dirty")) {
      return environment(mob)->query_property("croom_clean");
    }

    //    inv = all_inventory(environment(mob));
    //    for(i = 0; i < sizeof(inv); i++){
    //      if(interactive(inv[i])) return 1;
    //    }

    if (sizeof(filter_array(all_inventory(environment(mob)), "__interactive","/daemon/filters_d"))) {
      environment(mob)->remove_property("croom_clean");
      environment(mob)->set_property("croom_clean",1);
	  environment(mob)->remove_property("croom_dirty");
      return 1;
    } else {
      environment(mob)->remove_property("croom_clean");
	  environment(mob)->remove_property("croom_dirty");
      return 0;
    }
}

// putting it back again now that lag is otherwise better *Styx* 12/26/03, last change before was 12/13/03
//added by Grendel to dest controlled mobs (if not interacting) before room cleans up

int clean_up() {
  string *aKeys;
  object * allmons;
  object * tempmons;
  int i,j,k,l;
  int continueClean = 1;

  if(mons && sizeof(mons)){
    aKeys = keys(mons);
    j = sizeof(aKeys);
    for(i=0;i<j;i++){
      /*********************************
      l = sizeof(mons[aKeys[i]]);
      for(k=0;k<l;k++){
	if( !objectp(mons[aKeys[i]][k]) ) continue;
	if( !interacting_mob(mons[aKeys[i]][k]) ){
	  mons[aKeys[i]][k]->move(VOID);
	  mons[aKeys[i]][k]->remove();
	  if(objectp(mons[aKeys[i]][k])) destruct(mons[aKeys[i]][k]);
	} else {
	  continueClean = 0;
	}
      }
      ********************************/
      allmons = mons[aKeys[i]];
      if (sizeof(tempmons=filter_array(allmons, "interacting_mob",TO))) {
	continueClean = 0;
      } else {
	continueClean = 1;
      }
      allmons -= tempmons;
      allmons->move(VOID);
      allmons->remove();

      l = sizeof(allmons);
      for (k=0;k<l;k++)
	if (objectp(allmons[k]))
	  destruct(allmons[k]);
    }
  }
  if( continueClean )
  {
    return 1;
  }
  return 1;

// changing to 1 again to see if that helps clean things up better without making lag too bad since the lag seems to have been from other causes *Styx*, 12/30/03
// This really should be a 1 so it continues to get called over and over, but it causes horrendous clean_up lag if allowed to continue. - garrett
// Changed to 1 to see if it works.
// Garrett.
}

int is_control_room() { return 1; }
