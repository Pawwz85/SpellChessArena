#pragma once

#include <QString>
#include <QObject>
#include <QWidget>

#include "EngineTool.hpp"
#include "EngineRolesService.hpp"

class QTextEdit;

class EngineLogsWidget : public QWidget, public EngineTools::EngineTool {
    Q_OBJECT
    QTextEdit * textEdit;

    int engineId;
    QMetaObject::Connection loggerConnection;
    void disconnectEngine() override;
    void connectEngine(const EngineServiceEntry & engineEntry) override;

    private slots:
    void onNewLineLogged(QString line);

    public:
    EngineLogsWidget(EngineTools::EngineRole role, QWidget* parent = nullptr );
};