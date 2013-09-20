/**
 * プラグインウィジェット.
 * @file plugin_widget.cpp.
 * @author yatagai.
 */
#include "../../plugin.h"
#include "plugin_widget.h"
#include "ui_plugin_widget.h"
#include "plugin_manager_widget.h"
#include "../../plugin_manager/plugin_manager.h"
#include <assert.h>

/**
 *  @brief		コンストラクタ.		
 *  @author		yatagaik.
 *  @param	in	plugin	このウィジェットのプラグイン.
 *  @param	in	plugin_manager_widget	プラグインマネージャのウィジェット.
 */ 
PluginWidget::PluginWidget(meta_tools::IPlugin* plugin, PluginManagerWidget *plugin_manager_widget)
        : QWidget()
        , m_ui(new Ui::Plugin())
        , m_plugin(plugin)
        , m_plugin_manager_widget(plugin_manager_widget)
{
    m_ui->setupUi(this);

    // ウィジェットのセットアップ. 
    SetUpWidget();
}

/**
 * @brief		デストラクタ.		
 * @author		yatagaik.
 */ 
PluginWidget::~PluginWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

/**
 * @brief		マウスクリックイベント.		
 * @author		yatagaik.
 * @param	in	mouse_event	マウスイベント.
 */
void PluginWidget::mouseReleaseEvent(QMouseEvent * /*mouse_event*/)
{
    if (!m_plugin->IsExecute())
    {
        meta_tools::PluginManager::Order()->OpenPlugin(m_plugin);
    }
    UnSelect();
    m_plugin_manager_widget->close();
}

/**
 * @brief		マウス移動イベント.		
 * @author		yatagaik.
 * @param  in	mouse_event	マウスイベント.
 */ 
void PluginWidget::mouseMoveEvent(QMouseEvent * /*mouse_event*/)
{
    assert(m_plugin);
    std::string set_text = "プラグインの概要:\n";
    set_text += "State:\t\t";
    set_text += m_plugin->IsStartUp() ? "StartUP " : "";
    set_text += m_plugin->IsExecute() ? "Running" : "Not Runing";
    set_text += ".\n";
    set_text += "Name:\t\t";
    set_text += m_plugin->GetName();
    set_text += ".\n";
    set_text += "Version:\t\t";
    set_text += m_plugin->GetVersion();
    set_text += ".\n";
    set_text += "Author:\t\t";
    set_text += m_plugin->GetAuthor();
    set_text += ".\n";
    set_text += "説明:\t\t";
    set_text += m_plugin->GetExp();
    set_text += ".\n";
    m_plugin_manager_widget->ChangePluginExplanationText(set_text);
    m_ui->Frame->setAutoFillBackground(true);
}

/**
 * @brief		Leaveイベント.		
 * @author		yatagaik.
 * @param  in	event	イベント.
 */ 
void PluginWidget::leaveEvent(QEvent * /*event*/)
{
    UnSelect();
}

/**
 * @brief		ウィジェットのセットアップ.		
 * @author		yatagaik.
 */ 
void PluginWidget::SetUpWidget()
{
    assert(m_plugin);

	// 名前のセット.
	m_ui->PluginName->setText(QString::fromLocal8Bit(m_plugin->GetName()));

	// アイコンのセット.
    QIcon *icon = m_plugin->GetWidgetIcon();
    if (!icon->isNull())
    {
        m_ui->PluginIcon->setPixmap(icon->pixmap(90));
    }
}

/**
 * @brief		選択の解除.		
 * @author		yatagaik.
 */ 
void PluginWidget::UnSelect()
{
    std::string set_text = "プラグインの概要:\n";
    m_plugin_manager_widget->ChangePluginExplanationText(set_text);
    m_ui->Frame->setAutoFillBackground(false);
}
