#include "common.h"

int main()
{
    CSimpleMusicManager manager;



    // all songs in the store
    vvMusicAttribute vsongs = {
                        {{music::author, {"AR Rehman"}}, {music::name, {"Pray for me Brother"}}, {music::release, {2005}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Mast magan"}}, {music::release, {2019}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Hindustani"}}, {music::release, {2000}}},
                        {{music::author, {"Rashid Ali"}}, {music::name, {"Nazarlayena"}}, {music::release, {2010}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Jai Ho"}}, {music::release, {2002}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Laal Isqh"}}, {music::release, {2017}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Humse Muqabla"}}, {music::release, {2010}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Kabhi Jo Badal barse"}}, {music::release, {2012}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Chaiya Chiya"}}, {music::release, {1998}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Tum hi ho"}}, {music::release, {2015}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Satrangi rey"}}, {music::release, {1999}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Chana mereya"}}, {music::release, {2012}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Radha kaisey na Jale"}}, {music::release, {2003}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Orey chori"}}, {music::release, {2001}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Raabta"}}, {music::release, {2014}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Dreams on Fire"}}, {music::release, {2012}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Geruya"}}, {music::release, {2006}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Taal sey Taal"}}, {music::release, {2005}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Nahi Samney"}}, {music::release, {2002}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Osana"}}, {music::release, {2010}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Take it easy Urvasi"}}, {music::release, {2013}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Khamoshiya"}}, {music::release, {2011}}},
                        {{music::author, {"Jubin Nautiyal"}}, {music::name, {"Zindagi Kuch Toh Bata"}}, {music::release, {2018}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Agar Tum Sathe ho"}}, {music::release, {2017}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Gopala Gopala"}}, {music::release, {2002}}},
                        {{music::author, {"Arijit Singh"}}, {music::name, {"Tujhe Kinta Chahey aur hum"}}, {music::release, {2019}}},
                        {{music::author, {"Jubin Nautiyal"}}, {music::name, {"Tujhe Kinta Chahey aur hum"}}, {music::release, {2019}}},
                        {{music::author, {"Rashid Ali"}}, {music::name, {"Kabhi Kabhi Aditi"}}, {music::release, {2004}}},
                        {{music::author, {"AR Rehman"}}, {music::name, {"Dil se"}}, {music::release, {2008}}}
                    };

    manager.AddSongs(vsongs);

   // add songs in the playlist, based on vector of search attributes
   vvMusicAttribute vsongs_playlist = {
                                   {{music::author, {"Rashid Ali"}}},
                                   {{music::author, {"Jubin Nautiyal"}}}
                               };
   manager.AddToPlayList(vsongs_playlist);
   manager.GetTopSongs(); // Get top 10 fequently played song.

   // add songs in the playlist, based on vector of search attributes
   vvMusicAttribute vsongs_playlist1 = {
                                   {{music::author, {"Arijit Singh"}}}
                               };
   manager.AddToPlayList(vsongs_playlist1);
   manager.GetTopSongs(); // Get top 10 fequently played song.

    // add songs in the playlist, based on vector of search attributes
    vvMusicAttribute vsongs_playlist2 = {
                                    {{music::name, {"Tujhe Kinta Chahey aur hum"}}}
                                };
    manager.AddToPlayList(vsongs_playlist2);
    manager.GetTopSongs(); // Get top 10 fequently played song.

    // add songs in the playlist, based on vector of search attributes
    vvMusicAttribute vsongs_playlist3 = {
                                    {{music::release, {2012}}}
                                };
    manager.AddToPlayList(vsongs_playlist3);
    manager.GetTopSongs(); // Get top 10 fequently played song.
    
    return 0;
}
