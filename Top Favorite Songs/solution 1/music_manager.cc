#include "common.h"
#include "music_manager.h"

struct CMusicManager::PimplMember {
    vecSpISong vSongs;
    vecSpISong vPlaylist;
    uint32_t play_count;
    PimplMember()
    :play_count(0){}
};

CMusicManager::CMusicManager()
: m_member(std::make_shared<PimplMember>()) {
}

auto CMusicManager::GetPlayList() -> vecSpISong {
    assert(m_member != nullptr);
    
    vecSpISong ret;
    
    for(auto &iter : m_member->vPlaylist)
     {
         ret.emplace_back(iter);
     }
    
    return ret;
}

void CMusicManager::AddSongs(vvMusicAttribute& song_list) {
    assert(m_member != nullptr);
    
     for(auto &v_iter : song_list)
     {
         umMusicAttribute song_map;
         for(auto &iter : v_iter)
         {
             song_map.emplace( std::get<0>(iter), MusicMetaType(std::get<1>(iter)));
         }
         spISong song = std::make_shared<CSong>(song_map);
         m_member->vSongs.emplace_back(song);
     }
}

void CMusicManager::AddToPlayList(vvMusicAttribute& song_list) {
    assert(m_member != nullptr);

     m_member->vPlaylist.clear();
     for(auto &v_iter : song_list)
     {
         for(auto &iter : m_member->vSongs)
         {
             bool b_add_to_playlist = iter->CheckAttribute(v_iter);
             if(b_add_to_playlist) m_member->vPlaylist.emplace_back(iter);
         }
     }
}

void CMusicManager::PlaySong(int32_t n=-1) { // -1 : play all songs from playlist
    assert(m_member != nullptr);
    m_member->play_count = n;
}

auto CMusicManager::TotalSongsPlayed() -> uint32_t {
    assert(m_member != nullptr);
    return m_member->play_count;
}

auto CMusicLastNSongs::GetTopN(vecSpISong& vsong, uint32_t songs_played, uint32_t n=10) -> void {
     auto min = std::min(songs_played, n);

     auto song_iter = vsong.begin();
     while(min-- && song_iter != vsong.end()) {
         auto attr = (*song_iter)->GetAttribute();
         std::cout<<"Author: "<<std::get<std::string>(attr[music::author].value)
         <<" Song: \""<<std::get<std::string>(attr[music::name].value)
         <<"\" Music: "<<std::get<uint64_t>(attr[music::release].value)
                  <<"\n";
         song_iter++;
     }
     std::cout<<"--------\n";
}

CSimpleMusicManager::CSimpleMusicManager()
: topMusic(std::make_shared<CMusicLastNSongs>()) {
}

auto CSimpleMusicManager::GetTopSongs() -> void {
     auto v_playlist = GetPlayList();
    topMusic->GetTopN(v_playlist, 10, 10);
}
