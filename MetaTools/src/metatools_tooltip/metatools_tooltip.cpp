/**
 * tooltip�N���X�̎���.
 * @file metatools_tooltip.cpp.
 * @author yatagai.
 */

#include "metatools_tooltip.h"
#include "ui_metatools_tooltip.h"


/**
 * �R���X�g���N�^.
 * @param in parent �e�E�B�W�F�b�g.
 */
MetaToolsToolTip::MetaToolsToolTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetaToolsToolTip)
{
    ui->setupUi(this);
}

/**
 * �f�X�g���N�^.
 */
MetaToolsToolTip::~MetaToolsToolTip()
{
    delete ui;
}
