#include "fontcreator_plugin.h"
#include "fontcreator_widget.h"

/**
 *  @brief		コンストラクタ.
 *  @param  in  app_functions アプリケーション関数.
 */
FontCreatorPlugin::FontCreatorPlugin(const meta_tools::IPlugin::AppFunctions &app_functions) :
    IPlugin(app_functions)
  , m_window(new FontCreatorWidget())
{
    m_widget_icon->addFile(":/font_creator_resource/img/font_icon.png");
}

/**
 *  @brief		デストラクタ.
 */
FontCreatorPlugin::~FontCreatorPlugin()
{
    if (m_window)
    {
        delete m_window;
        m_window = nullptr;
    }
}

/**
 *  @breif      スタート時処理.
 */
bool FontCreatorPlugin::OnStart()
{
    AddToolWidget(m_window, "FontCreator");
    m_window->OnStart();
    return true;
}

/**
 *  @breif      スタート時処理.
 */
bool FontCreatorPlugin::OnClose()
{
    RemoveWidget(m_window);
    m_window->OnClose();
    return true;
}
