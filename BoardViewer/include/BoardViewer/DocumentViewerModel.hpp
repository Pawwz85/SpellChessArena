#pragma once

#include "BoardViewerModel.hpp"

#include <SpellChess/SpellChessDocument.h>

#include <memory>

class QObject;

namespace BoardViewer {
    class DocumentViewerModel : public Model {
        void handleMakeMove(SpellChessLib::SpellChessMove move) override;
        public:
        DocumentViewerModel(std::shared_ptr<SpellChessLib::SpellChessDocument> document, QObject * parent = nullptr);
        SpellChessLib::SpellChessDocument::Handle getCurrentPosition() const override;
        std::shared_ptr<const SpellChessLib::SpellChessDocument> getDocument() const override;
        bool canUserSubmitMove() override;
        QString getWhitePlayerName() const override;
        QString getBlackPlayerName() const override;
    };
}

