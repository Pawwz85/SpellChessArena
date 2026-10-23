#pragma once

#include <QDialog>
#include <QString>

#include <SpellChess/DocumentAnnotator.h>

class GameStatisticsDialog final : public QDialog {
public:
    GameStatisticsDialog(const SpellChessLib::GameStatistics & statistics,
                         const QString & whitePlayer,
                         const QString & blackPlayer,
                         QWidget * parent = nullptr);
};