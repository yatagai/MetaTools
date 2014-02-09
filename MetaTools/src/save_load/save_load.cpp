#include "assert.h"
#include "save_load.h"
#include "../plugin/plugin.h"

namespace
{
const char SAVE_DATA_FILE_NAME[] = "meta_tools_save.json";
const char APP_SAVE_DATA_NAME[] = "meta_tools_info";
const char PLUGIN_EXECUTE_PREFIX[] = "execute_plugin_";
QString GetPluginExecuteName(const meta_tools::IPlugin *plugin)
{
    QString ret = plugin->GetName();
    return PLUGIN_EXECUTE_PREFIX + ret.toLower();
}

const char PLUGIN_SAVE_DATA_PREFIX[] = "save_data_plugin_";
QString GetPluginSaveDataName(const meta_tools::IPlugin *plugin)
{
    QString ret = plugin->GetName();
    return PLUGIN_SAVE_DATA_PREFIX + ret.toLower();
}

}

namespace meta_tools
{
SaveLoad *SaveLoad::sm_this = NULL;

/**
 * @brief      コンストラクタ.
 * @autor      yatagaik.
 */
SaveLoad::SaveLoad()
{
    sm_this = this;
    Load();
}

/**
 * @brief      デストラクタ.
 */
SaveLoad::~SaveLoad()
{
    Save();
    sm_this = nullptr;

    std::map<QString, QJsonObject*>::iterator it = m_plugin_save_object.begin();
    for (; it != m_plugin_save_object.end(); ++it)
    {
        delete it->second;
    }
}

/**
 * @brief      読み込み.
 */
void SaveLoad::Load()
{
    QFile file(SAVE_DATA_FILE_NAME);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        m_save_object = doc.object();
        QStringList keys = m_save_object.keys();
        for (int i = 0; i < keys.size(); ++i)
        {
            if (keys[i] == APP_SAVE_DATA_NAME)
            {
                m_app_save_object = m_save_object[keys[i]].toObject();
            }
            else if (keys[i].indexOf(PLUGIN_SAVE_DATA_PREFIX) == 0)
            {
                m_plugin_save_object[keys[i]] = new QJsonObject();
                *m_plugin_save_object[keys[i]] = m_save_object[keys[i]].toObject();
            }
        }
    }
}

/**
 * @brief      保存.
 */
void SaveLoad::Save()
{
    QJsonDocument doc;

    // アプリ情報をセット.
    m_save_object[APP_SAVE_DATA_NAME] = m_app_save_object;

    // プラグイン情報をセット.
    std::map<QString, QJsonObject*>::iterator it = m_plugin_save_object.begin();
    for (; it != m_plugin_save_object.end(); ++it)
    {
        m_save_object[it->first] = *it->second;
    }

    // 書き出し.
    doc.setObject(m_save_object);
    QFile file(SAVE_DATA_FILE_NAME);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << doc.toJson().data();
        file.close();
    }
}

/**
 *  @brief		アプリケーションセーブデータの取得.
 *  @author     yatagaik.
 *  @param  in  param_name パラメータ名.
 *  @return 保存値 idUndefinedで無効.
 */
const QJsonValue SaveLoad::GetAppSaveData(const std::string param_name)
{
    if (m_app_save_object.contains(param_name.c_str()))
    {
        return m_app_save_object[param_name.c_str()];
    }

    return QJsonValue(QJsonValue::Undefined);
}

/**
 *  @brief		アプリケーションセーブデータのセット.
 *  @author     yatagaik.
 *  @param  in  param_name パラメータ名.
 * 　@param  in  set_value セットする値.
 */
void SaveLoad::SetAppSaveData(const std::string param_name, const QJsonValue &set_value)
{
    m_app_save_object[param_name.c_str()] = set_value;
}

/**
 *  @brief      プラグイン実行状態取得.
 *  @author     yatagaik.
 *  @param  in  entry_plugin プラグイン.
 *  @return trueで実行中 falseで実行されていない.
 */
bool SaveLoad::IsLastExecute(const IPlugin *entry_plugin)
{
    QString param_name = GetPluginExecuteName(entry_plugin);
    if (m_save_object.contains(param_name) &&
        m_save_object[param_name].isBool() &&
        m_save_object[param_name].toBool())
    {
        return true;
    }

    return false;
}

/**
 *  @brief      プラグイン実行状態取得.
 *  @author     yatagaik.
 *  @param  in  entry_plugin プラグイン.
 *  @param  in  last_execute 実行状態.
 */
void SaveLoad::SetLastExecute(const IPlugin *entry_plugin, bool last_execute)
{
    QString param_name = GetPluginExecuteName(entry_plugin);
    m_save_object[param_name] = last_execute;
}

/**
 *  @brief		プラグインセーブデータの取得.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  param_name パラメータ名.
 *  @return 保存値 idUndefinedで無効.
 */
const QJsonValue SaveLoad::GetSaveData(const IPlugin *entry_plugin, const std::string param_name)
{
    QString save_data_name = GetPluginSaveDataName(entry_plugin);
    if (m_plugin_save_object.find(save_data_name) != m_plugin_save_object.end() &&
        (m_plugin_save_object.find(save_data_name)->second)->contains(param_name.c_str()))
    {
        return (*m_plugin_save_object.find(save_data_name)->second)[param_name.c_str()];
    }

    return QJsonValue(QJsonValue::Undefined);
}

/**
 *  @brief		プラグインセーブデータのセット.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  param_name パラメータ名.
 * 　@param  in  set_value セットする値.
 */
void SaveLoad::SetSaveData(const IPlugin *entry_plugin, const std::string param_name, const QJsonValue &set_value)
{
    // unsupprted object and array.
    assert(!(set_value.isObject() || set_value.isArray()));

    QString save_data_name = GetPluginSaveDataName(entry_plugin);

    if (m_plugin_save_object.find(save_data_name) == m_plugin_save_object.end())
    {
        m_plugin_save_object[save_data_name] = new QJsonObject();
    }
    (*m_plugin_save_object[save_data_name])[param_name.c_str()] = set_value;
}
}
