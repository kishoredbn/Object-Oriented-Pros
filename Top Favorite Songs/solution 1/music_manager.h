#pragma once

// abstract class music manager
class IMusicManager {
public:
    virtual auto GetPlayList() -> vecSpISong = 0;
    virtual void AddSongs(vvMusicAttribute&) = 0;
    virtual void AddToPlayList(vvMusicAttribute&) = 0;
    virtual void PlaySong(int32_t) = 0;
    virtual auto TotalSongsPlayed() -> uint32_t = 0;
    virtual ~IMusicManager(){}
};

using spIMusicManager = std::shared_ptr<IMusicManager>;

// abstract class top N music
class IMusicTopN {
public:
    virtual auto GetTopN(vecSpISong&, uint32_t, uint32_t) -> void = 0;
    virtual ~IMusicTopN(){}
};

using spIMusicTopN = std::shared_ptr<IMusicTopN>;

// concrete class music manager
class CMusicManager : public IMusicManager {
private:
    struct PimplMember;
    std::shared_ptr<PimplMember> m_member;
public:
    CMusicManager();
    virtual auto GetPlayList() -> vecSpISong override;
    virtual void AddSongs(vvMusicAttribute&) override;
    virtual void AddToPlayList(vvMusicAttribute&) override;
    virtual void PlaySong(int32_t) override;
    virtual auto TotalSongsPlayed() -> uint32_t override;
};

// concrete class top N music
class CMusicLastNSongs : public IMusicTopN {
public:
    virtual auto GetTopN(vecSpISong&, uint32_t, uint32_t) -> void override;
};

class CSimpleMusicManager : public CMusicManager {
private:
    spIMusicTopN topMusic;
public:
    CSimpleMusicManager();
    virtual auto GetTopSongs() -> void;
};
