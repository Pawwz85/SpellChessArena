#include <GameStatisticsDialog.hpp>

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include <algorithm>
#include <array>

namespace {

QString accuracy(const SpellChessLib::PlayerStatistics & statistics) {
    if (statistics.totalMoves == 0)
        return QObject::tr("N/A");

    const double value = std::clamp(
        100.0 * (static_cast<double>(statistics.totalMoves) / statistics.totalAccuracyReciprocals),
        0.0, 100.0);
    return QObject::tr("%1%").arg(value, 0, 'f', 2);
}

const std::array<QString, 5> classificationNames {
    QObject::tr("Unclasified"),
    QObject::tr("Blunders"),
    QObject::tr("Mistakes"),
    QObject::tr("Inaccuracies"),
    QObject::tr("Good moves")
};

const std::array<QString, 5> classificationColors {
    QString(),
    QStringLiteral("red"),
    QStringLiteral("orange"),
    QStringLiteral("yellow"),
    QStringLiteral("green")
};

void addSide(QGridLayout * layout, int column, const QString & player,
             const SpellChessLib::PlayerStatistics & statistics, bool white) {
    layout->addWidget(new QLabel(QStringLiteral("<b>%1</b>").arg(player)), 0, column);

    auto * accuracyLabel = new QLabel(QObject::tr("Accuracy: %1").arg(accuracy(statistics)));
    accuracyLabel->setAlignment(Qt::AlignCenter);
    accuracyLabel->setStyleSheet(white
        ? QStringLiteral("QLabel { background-color: white; color: black; border: 1px solid black; padding: 6px; }")
        : QStringLiteral("QLabel { background-color: black; color: white; border: 1px solid white; padding: 6px; }")
    );
    layout->addWidget(accuracyLabel, 1, column);
    layout->addWidget(new QLabel(QObject::tr("Moves: %1").arg(statistics.totalMoves)), 2, column);

    for (size_t index = 0; index < classificationNames.size(); ++index) {
        const auto count = statistics.moveClassCounter.at(index);
        auto * classificationLabel = new QLabel(QObject::tr("%1: %2")
                                                     .arg(classificationNames.at(index))
                                                     .arg(count));
        if (!classificationColors.at(index).isEmpty())
            classificationLabel->setStyleSheet(
                QStringLiteral("QLabel { color: %1; }").arg(classificationColors.at(index)));
        layout->addWidget(classificationLabel, static_cast<int>(index) + 3, column);
    }
}

}

GameStatisticsDialog::GameStatisticsDialog(const SpellChessLib::GameStatistics & statistics,
                                           const QString & whitePlayer,
                                           const QString & blackPlayer,
                                           QWidget * parent)
    : QDialog(parent) {
    setWindowTitle(tr("Game statistics"));
    setModal(true);

    auto * layout = new QGridLayout;
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    addSide(layout, 0, whitePlayer, statistics.whitePlayerStats, true);
    addSide(layout, 1, blackPlayer, statistics.blackPlayerStats, false);

    auto * buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto * outer = new QVBoxLayout(this);
    outer->addLayout(layout);
    outer->addWidget(buttons);
}