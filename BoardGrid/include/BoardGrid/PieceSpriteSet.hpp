#pragma once

#include <SpriteSet/SpriteSet.hpp>
#include <SpriteSet/SpriteSetScheme.hpp>
#include <Misc/Singleton.h>
#include <QString>

namespace Board {

    extern SpriteSet::SpriteSetScheme makePieceSetSchemeFromFolder(const QString & pieceSetFolder);
    extern SpriteSet::SpriteSetScheme makeDefaultPieceSetScheme();
    
    class PieceSpriteSet : public SpriteSet::SpriteSet, public Misc::Singleton<PieceSpriteSet> {
        public:
        PieceSpriteSet();
    };
};