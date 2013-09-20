#include "tool_widget_form.h"
#include "ui_tool_widget_form.h"
#include "../plugin/plugin.h"
#include "../plugin/plugin_manager/plugin_manager.h"
#include <assert.h>

namespace meta_tools
{

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 *  @param   in  plugin このウィジェットを持ったプラグイン.
 *  @param   in  main_view メインビュー.
 */
ToolWidgetForm::ToolWidgetForm(const IPlugin *plugin, QWidget *main_view) :
    QDockWidget("meta_tools", main_view),
    m_plugin(plugin),
    m_ui(new Ui::ToolWidgetForm),
    m_child(nullptr)
{
    m_ui->setupUi(this);
}

/**
 *  @brief      デストラクタ.
 *  @author		yatagaik.
 */
ToolWidgetForm::~ToolWidgetForm()
{
    SetChildWidget(nullptr);
    delete m_ui;
    m_ui = nullptr;
}

/**
 *  @brief      子ウィジェットのセット.
 *  @author		yatagaik.
 *  @param  in  child 子ウィジェット.
 */
void ToolWidgetForm::SetChildWidget(QWidget *child)
{
    if (m_child)
    {
        m_child->setParent(nullptr);
        m_ui->main_layout->layout()->removeWidget(m_child);
    }
    m_child = child;
    if (m_child)
    {
        m_child->setParent(m_ui->main_layout);
        m_ui->main_layout->layout()->addWidget(m_child);
    }
}

/**
 *  @brief      閉じるボタンが押された.
 *  @author		yatagaik.
 */
void ToolWidgetForm::closeEvent(QCloseEvent * close_event)
{
    close_event->ignore();
    assert(m_plugin);
    bool cancel = false;
    const_cast<IPlugin*>(m_plugin)->OnClickCloseButton(m_child, cancel);

    if (!cancel)
    {
        PluginManager::Order()->RemoveWidget(m_plugin, m_child);
    }
}

}           // namespace meta_tools.
