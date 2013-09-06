/**
 * tooltipクラスの実装.
 * @file metatools_tooltip.cpp.
 * @author yatagai.
 */

#include "metatools_tooltip.h"
#include "ui_metatools_tooltip.h"
#include "../plugin/plugin.h"
#include <assert.h>

namespace meta_tools
{

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 *  @param   in  parent 親ウィジェット.
 *  @param   in  plugin このウィジェットを持ったプラグイン.
 */
MetaToolsToolTip::MetaToolsToolTip(QWidget *parent, const IPlugin *plugin) :
    QWidget(parent),
    m_plugin(plugin),
    m_ui(new Ui::MetaToolsToolTip),
    m_child(nullptr)
{
    m_ui->setupUi(this);
    connect(m_ui->close_button, SIGNAL(clicked()), this, SLOT(OnClickCloseButton()));

    // m_ui->caption_bar->setObjectName("metatools_tool_tip_caption_bar");
}

/**
 *  @brief      デストラクタ.
 *  @author		yatagaik.
 */
MetaToolsToolTip::~MetaToolsToolTip()
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
void MetaToolsToolTip::SetChildWidget(QWidget *child)
{
    if (m_child)
    {
        m_child->setParent(nullptr);
        m_ui->main_widget_layout->removeWidget(m_child);
    }
    m_child = child;
    if (m_child)
    {
        resize(child->geometry().width() + 5, height());
        child->setParent(m_ui->main_widget);
        m_ui->main_widget_layout->addWidget(child);
    }
}

/**
 *  @brief      ラベルのセット.
 *  @author		yatagaik.
 *  @param  in  label セットするラベル.
 */
void MetaToolsToolTip::SetLabel(const char* label)
{
    m_ui->caption->setText(label);
}

/**
 *  @brief      閉じるボタンが押された.
 *  @author		yatagaik.
 */
void MetaToolsToolTip::OnClickCloseButton()
{
    assert(m_plugin);
    const_cast<IPlugin*>(m_plugin)->OnClickCloseButton(m_child);
}

void MetaToolsToolTip::paintEvent(QPaintEvent */*event*/)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

}   // end namespace meta_tools.
