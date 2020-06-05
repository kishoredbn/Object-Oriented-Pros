#include "common.h"
#include "song.h"

struct CSong::PimplMember : public MusicAttributes
{
    PimplMember(umMusicAttribute metadata)
        : MusicAttributes(metadata) {}
};

CSong::CSong(umMusicAttribute& attr)
: m_member(std::make_shared<PimplMember>(attr))
{
}

auto CSong::GetAttribute() -> umMusicAttribute {
    assert(m_member);
    
    umMusicAttribute ret;
     for(auto &iter : m_member->metadata) ret[iter.first] = iter.second.value;
    
    return ret;
}


auto CSong::CheckAttribute(vMusicAttribute& v_attr) -> bool {
    bool ret = false;
    assert(m_member != nullptr);

     for(auto &iter : v_attr) {
         auto find_attr = m_member->metadata.find(std::get<Attributes>(iter));
         if(find_attr == m_member->metadata.end()) return ret;
         if(!(find_attr->second == std::get<MusicMetaType>(iter).value)) return ret;
     }
     ret = true;

    return ret;
}
