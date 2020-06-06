#include "common.h"
#include "song_factory.h"

SongFactory::SongFactory() {
}

spISong SongFactory::CreateSongObj(umMusicAttribute& song_map) {
    spISong ret = nullptr;
    ret = std::make_shared<CSong>(song_map);
    return ret;
}
