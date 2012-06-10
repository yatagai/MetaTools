#include "tool_widget_form.h"
#include "ui_tool_widget_form.h"
#include "../plugin/plugin.h"
#include <assert.h>

namespace meta_tools
{

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 *  @param   in  plugin このウィジェットを持ったプラグイン.
 */
ToolWidgetForm::ToolWidgetForm(const IPlugin *plugin) :
    QWidget(),
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
        m_ui->main_layout->removeWidget(m_child);
    }
    m_child = child;
    if (m_child)
    {
        resize(child->geometry().width() + 5, height());
        child->setParent(this);
        m_ui->main_layout->addWidget(child);
    }
}

/**
 *  @brief      リサイズイベント.
 *  @author		yatagaik.
 *  @param  in  event イベント.
 */
void ToolWidgetForm::resizeEvent(QResizeEvent * /*event*/)
{
    if (m_child)
    {
        m_child->setGeometry(geometry());
    }
}

/**
 *  @brief      閉じるボタンが押された.
 *  @author		yatagaik.
 */
void ToolWidgetForm::OnClickCloseButton()
{
    assert(m_plugin);
    const_cast<IPlugin*>(m_plugin)->OnClickCloseButton(m_child);
}

}           // namespace meta_tools.
