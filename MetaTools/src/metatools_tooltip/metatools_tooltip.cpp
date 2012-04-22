#include "metatools_tooltip.h"
#include "ui_metatools_tooltip.h"

MetaToolsToolTip::MetaToolsToolTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetaToolsToolTip)
{
    ui->setupUi(this);
}

MetaToolsToolTip::~MetaToolsToolTip()
{
    delete ui;
}
