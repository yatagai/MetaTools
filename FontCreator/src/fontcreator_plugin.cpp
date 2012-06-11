#include "fontcreator_plugin.h"


FontCreatorPlugin::FontCreatorPlugin(const meta_tools::IPlugin::AppFunctions &app_functions) :
    IPlugin(app_functions)
{
    m_widget_icon->addFile(":/font_creator_resource/img/font_icon.png");
}
