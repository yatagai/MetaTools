/**
 * プラグインマネージャウィジェット.
 * @file plugin_manager_widget.cpp.
 * @author yatagai.
 */

#include "plugin_manager_widget.h"
#include "plugin_widget.h"
#include "../../../main/mainwindow.h"
#include <vector>
#include <QMouseEvent>
#include <QDebug>
#include "ui_plugin_manager.h"

/**
 * @brief		コンストラクタ.		
 * @author		yatagaik.
 */ 
PluginManagerWidget::PluginManagerWidget()
    : QWidget(),
      m_ui(new Ui::PluginManager())
{
     m_ui->setupUi(this);
     setWindowFlags(Qt::Tool |
                    Qt::FramelessWindowHint     |
                    Qt::WindowSystemMenuHint    |
                    Qt::WindowStaysOnTopHint    |
                    Qt::WindowFullscreenButtonHint);
     setWindowState(windowState() | Qt::WindowFullScreen);
}

/**
 * @brief		デストラクタ.		
 * @author		yatagaik.
 */ 
PluginManagerWidget::~PluginManagerWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

/**
 * @brief		プラグインウィジェットの追加.
 * @author		yatagaik.
 * @param  in	plugin	追加するウィジェットのプラグイン.
 */
void PluginManagerWidget::AddPluginWidget(meta_tools::IPlugin *plugin)
{
    PluginWidget *new_widget = new PluginWidget(plugin, this);
    new_widget->setParent(m_ui->PluginList);
    static int i;
    m_ui->PluginListLayout->addWidget(new_widget, 0, i++);
}

/**
 * @brief		表示.
 * @author		yatagaik.
 */
void PluginManagerWidget::Show()
{
    ChangePluginExplanationText("プラグインの概要:");

    setWindowOpacity(0.9f);

    show();

    // メインウインドウのあるモニタに最大化表示.
    setGeometry(MainWindow::Order()->geometry());
    setWindowState(windowState() | Qt::WindowFullScreen);
}

/**
 * @brief		プラグインの説明テキスト変更.
 * @author		yatagaik.
 * @param  in	explanation 説明文.
 */
void PluginManagerWidget::ChangePluginExplanationText(const std::string &explanation)
{
    m_ui->PluginExp->setText(QString::fromLocal8Bit(explanation.c_str()));
}

/**
 * @brief		マウスPressイベント.
 * @author		yatagaik.
 * @param  in	event   マウスイベント.
 */ 
void PluginManagerWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
	{
		close();
	}
}

/**
 * @brief		リサイズイベント.
 * @author		yatagaik.
 * @param  in	event   マウスイベント.
 */
void PluginManagerWidget::resizeEvent(QResizeEvent *event)
{
    static const float WIDGET_WIDTH(185.0f);
    static const float WIDGET_HEIGHT(110.0f);

    // clear.
    std::vector<QWidget*> m_widget_list;
    for (int i = 0; i < m_ui->PluginListLayout->count(); ++i)
    {
        m_widget_list.push_back(m_ui->PluginListLayout->itemAt(i)->widget());
    }
    for (auto it = m_widget_list.begin(); it != m_widget_list.end(); ++it)
    {
        m_ui->PluginListLayout->removeWidget(*it);
    }

    const int COLUMN_COUNT((event->size().width() - 20.0f) / WIDGET_WIDTH);
    const int ROW_COUNT((static_cast<int>(m_widget_list.size()) / COLUMN_COUNT) + ((static_cast<int>(m_widget_list.size()) % COLUMN_COUNT) == 0 ? 0 : 1));

    // resize
    m_ui->PluginList->setMinimumHeight(WIDGET_HEIGHT * ROW_COUNT);

    // readd.
    int column_index = 0;
    int row_index = 0;
    for (unsigned int i = 0; i < m_widget_list.size(); ++i)
    {
        m_ui->PluginListLayout->addWidget(m_widget_list[i], row_index, column_index++);
        if (column_index >= COLUMN_COUNT)
        {
            column_index = 0;
            ++row_index;
        }
    }
}

