/**
 * tooltipクラスの定義.
 * @file metatools_tooltip..
 * @author yatagai.
 */

#ifndef METATOOLS_TOOLTIP_H
#define METATOOLS_TOOLTIP_H

#include <QWidget>

namespace Ui {
class MetaToolsToolTip;
}

/**
 *  ツールチップクラス.
 *  @author yatagai.
 */
class MetaToolsToolTip : public QWidget
{
    Q_OBJECT
    
public:
    explicit MetaToolsToolTip(QWidget *parent = 0);
    ~MetaToolsToolTip();
    
private:
    Ui::MetaToolsToolTip *ui;
};

#endif // METATOOLS_TOOLTIP_H
