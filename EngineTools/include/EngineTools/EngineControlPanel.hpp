#pragma once

#include <QWidget>
#include "EngineTool.hpp"
#include "EngineRolesService.hpp"

namespace UCILoader { class EngineOptionProxy; }

class EngineControlPanel : public QWidget, public EngineTools::EngineTool {
    
    QWidget * addCheckBox(UCILoader::EngineOptionProxy & option);
    QWidget * addSpinBox(UCILoader::EngineOptionProxy & proxy);
    QWidget * addComboBox(UCILoader::EngineOptionProxy & proxy);
    QWidget * addStringInput(UCILoader::EngineOptionProxy & proxy);
    QWidget * addButton(UCILoader::EngineOptionProxy & proxy);

    void disconnectEngine() override;
    void connectEngine(const EngineServiceEntry & engineEntry) override;

    public:
    EngineControlPanel(EngineTools::EngineRole role, QWidget * parent = nullptr);
};