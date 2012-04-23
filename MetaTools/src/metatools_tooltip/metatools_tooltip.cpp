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
    ui(new Ui::MetaToolsToolTip)
{
    ui->setupUi(this);
}

/**
 * デストラクタ.
 */
MetaToolsToolTip::~MetaToolsToolTip()
{
    delete ui;
}
