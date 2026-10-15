#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <QWidget>
#include <QColor>

#include <SpellChess/Board.h>

#include "EngineTool.hpp"
#include "EngineRolesService.hpp"

class QLabel;
class QLineEdit;

namespace UCILoader { 
    class EventReceiver;
    class UciScore;
}

class VariationLineWidget : public QWidget {
    Q_OBJECT
    QLabel * evaluationLabel;
    QLineEdit * variationLine;
    QColor evaluationColor;
    
    private slots:
    void evalChanged(UCILoader::UciScore score, const SpellChessLib::GameState & context);
    void variationChanged(const std::string & variation);

    public:
    VariationLineWidget(QWidget * parent = nullptr);

    signals:
    void setEval(UCILoader::UciScore score, const SpellChessLib::GameState & context);
    void setVariation(const std::string & variation);
};

class PrincipalVariationPanel : public QWidget, public EngineTools::EngineTool {
    Q_OBJECT
    VariationLineWidget * variationLines;
    size_t numVariations;
    SpellChessLib::GameState context;

    std::shared_ptr<UCILoader::EventReceiver> infoBatchHandler = nullptr;
    std::shared_ptr<UCILoader::EventReceiver> searchRequestHandler = nullptr;

    void disconnectEngine() override;
    void connectEngine(const EngineServiceEntry & engineEntry) override;

    std::string formatVariationLine(const std::vector<SpellChessLib::SpellChessMove> & moves);

    public:
    PrincipalVariationPanel(EngineTools::EngineRole role, size_t numVariations = 1, QWidget * parent = nullptr);
    ~PrincipalVariationPanel();

    public slots:
    void contextChanged(const SpellChessLib::GameState & context);
};