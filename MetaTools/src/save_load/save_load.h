#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <map>
#include <QJsonObject.h>
#include <QJsonValue.h>

namespace meta_tools
{
class IPlugin;
class SaveLoad
{
public:
    explicit SaveLoad();
    ~SaveLoad();

    // シングルトン.
public:
    static SaveLoad* Order()
    {
        return sm_this;
    }
private:
    static SaveLoad *sm_this;

private:
    void Load();
    void Save();

public:
    const QJsonValue GetAppSaveData(const std::string param_name);
    void SetAppSaveData(const std::string param_name, const QJsonValue &set_value);
    bool IsLastExecute(const IPlugin *entry_plugin);
    void SetLastExecute(const IPlugin *entry_plugin, bool last_execute);
    const QJsonValue GetSaveData(const IPlugin *entry_plugin, const std::string param_name);
    void SetSaveData(const IPlugin *entry_plugin, const std::string param_name, const QJsonValue &set_value);
private:
    QJsonObject m_save_object;
    QJsonObject m_app_save_object;
    std::map<QString, QJsonObject*> m_plugin_save_object;
};

}      // namespace meta_tools.
#endif // SPLASH_SCREEN_H
