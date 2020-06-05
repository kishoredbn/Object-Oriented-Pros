#pragma once

#include "common.h"
#include "song_attribute.h"

class ISong {
public:
    virtual auto GetAttribute() -> umMusicAttribute = 0;
    virtual auto CheckAttribute(vMusicAttribute&) -> bool = 0;
};

using spISong = std::shared_ptr<ISong>;
using vecSpISong = std::vector<spISong>;

class CSong : public ISong {
private:
    struct PimplMember;
    std::shared_ptr<PimplMember> m_member;
public:
    CSong(){}
    CSong(umMusicAttribute&);
    virtual auto GetAttribute() -> umMusicAttribute override;
    virtual auto CheckAttribute(vMusicAttribute&) -> bool override;
};
