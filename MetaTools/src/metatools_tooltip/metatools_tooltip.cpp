/**
 * tooltipクラスの実装.
 * @file metatools_tooltip.cpp.
 * @author yatagai.
 */

#include "metatools_tooltip.h"
#include "ui_metatools_tooltip.h"


/**
 * コンストラクタ.
 * @param in parent 親ウィジェット.
 */
MetaToolsToolTip::MetaToolsToolTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetaToolsToolTip),
    m_child(nullptr)
{
    ui->setupUi(this);
}

/**
 * デストラクタ.
 */
MetaToolsToolTip::~MetaToolsToolTip()
{
    SetChildWidget(nullptr);
    delete ui;
}

/**
 *  子ウィジェットのセット.
 *  @param in child 子ウィジェット.
 */
void MetaToolsToolTip::SetChildWidget(QWidget *child)
{
    if (m_child)
    {
        m_child->setParent(nullptr);
        ui->main_widget_layout->removeWidget(m_child);
    }
    m_child = child;
    if (m_child)
    {
        resize(child->geometry().width() + 5, height());
        child->setParent(ui->main_widget);
        ui->main_widget_layout->addWidget(child);
    }
}

/**
 *  ラベルのセット.
 *  @param in label セットするラベル.
 */
void MetaToolsToolTip::SetLabel(const char* label)
{
    ui->caption->setText(label);
}
