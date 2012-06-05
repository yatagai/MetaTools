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
    
public:
    void SetChildWidget(QWidget *child);
    void SetLabel(const char* label);
private:
    Ui::MetaToolsToolTip *ui;
    QWidget* m_child;
};

#endif // METATOOLS_TOOLTIP_H
