#include <DocumentViewerModel.hpp>
#include <QString>
#include <QStringLiteral>

#include <optional>
#include <string>

#include <SpellChess/Board.h> // for SpellChessMove
#include <SpellChess/Arbiter.h> // for arbite

class QObject;


BoardViewer::DocumentViewerModel::DocumentViewerModel(std::shared_ptr<SpellChessLib::SpellChessDocument> document, QObject * parent) : BoardViewer::Model(parent) {
    this->document = document;
    this->currentPosition = document->getTail();
}

SpellChessLib::SpellChessDocument::Handle 
BoardViewer::DocumentViewerModel::getCurrentPosition() const {
    return currentPosition;
}

std::shared_ptr<const SpellChessLib::SpellChessDocument>
BoardViewer::DocumentViewerModel::getDocument() const {
    return document;
}

bool 
BoardViewer::DocumentViewerModel::canUserSubmitMove() {
    auto currentState = document->getGameState(currentPosition);
    auto movesSinceRoot = document->getMovesSinceRoot(currentPosition);
    SpellChessLib::ArbiterVerdict verdict = SpellChessLib::arbite(currentState, movesSinceRoot);
    return verdict == SpellChessLib::ArbiterVerdict::None;
}

QString BoardViewer::DocumentViewerModel::getWhitePlayerName() const {
    const auto tag = document->getTag("White");
    return tag.has_value() && !tag->empty() && *tag != "?" ? QString::fromStdString(*tag) : QStringLiteral("White");
}

QString BoardViewer::DocumentViewerModel::getBlackPlayerName() const {
    const auto tag = document->getTag("Black");
    return tag.has_value() && !tag->empty() && *tag != "?" ? QString::fromStdString(*tag) : QStringLiteral("Black");
}

void
BoardViewer::DocumentViewerModel::handleMakeMove(SpellChessLib::SpellChessMove move) {
    currentPosition = document->makeMove(currentPosition, move);
    documentChanged(*document);
};

// rnbqkbnr/1ppp1ppp/8/p3p3/1P2P3/2P5/P2P1PPP/RNBQKBNR b KQkq - 0 1 - - F50/J20/f50/j20