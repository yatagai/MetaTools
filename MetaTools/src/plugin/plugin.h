/**
 *  プラグインのインターフェースの定義.
 * @file plugin.h.
 * @author yatagai.
 */

#ifndef METATOOLSPLUGIN_H
#define METATOOLSPLUGIN_H

#include <string>
#include <map>
#include <functional>
#include <QtGui>
#include <QIcon>

#undef SendMessage

namespace meta_tools
{

/**
 *  @brief		プラグインのインターフェース.		
 *  @author		yatagaik.
 */ 
class IPlugin
{
    // アプリケーション関数.
public:
    struct AppFunctions
    {
        bool (*AppSendMessage)(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
        void (*AppLogWrite)(const IPlugin *writer, const std::string &message);
        void (*AppDebugLogWrite)(const IPlugin *writer, const std::string &message);
        void (*AppAddMenuWidget)(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name);
        void (*AppAddToolWidget)(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label);
        void (*AppRemoveWidget)(const IPlugin *entry_plugin, QWidget *add_widget);
    };

public:
    /**
     *  @brief		コンストラクタ.
     *  @author		yatagaik.
     */
    IPlugin(const AppFunctions &app_functions) :
        m_widget_icon(new QIcon()),
        m_is_execute(false),
        m_functions(app_functions)
    {
    }

    /**
     *  @brief		デストラクタ.
     *  @author		yatagaik.
     */
    virtual ~IPlugin()
    {
        if (m_widget_icon)
        {
            delete m_widget_icon;
            m_widget_icon = nullptr;
        }
    }

public:
    /**
     *  @brief		プラグインの開始.
     *  @author		yatagaik.
     *  @return		trueで成功 falseで失敗.
     */
    bool Start()
    {
        if (OnStart())
        {
            m_is_execute = true;
        }
        return m_is_execute;
    }

    /**
     *  @brief		プラグインの終了してもよいか.
     *  @author		yatagaik.
     *  @return     trueで終了してもよい falseで終了したらダメ.
     */
    bool Closing()
    {
        return OnClosing();
    }

    /**
     *  @brief		プラグインの終了.
     *  @author		yatagaik.
     *  @return     trueで成功 falseで失敗.
     */
    bool Close()
    {
        if (OnClose())
        {
            m_is_execute = false;
        }

        return !m_is_execute;
    }

    // message関係.
public:
    /**
     *  @brief		プラグインにメッセージ送信.
     *  @author		yatagaik.
     *  @param  in  target_plugin_name 送信先のプラグイン名.
     *  @param  in  message_type メッセージタイプ.
     *  @param  in  param パラメータ.
     */
    bool SendMessage(const std::string &target_plugin_name, const std::string &message_type, void *param) const
    {
        return (*m_functions.AppSendMessage)(this, target_plugin_name, message_type, param);
    }
protected:
    /**
     *  @brief		メッセージ関数の追加.
     *  @author		yatagaik.
     *  @param  in  message_type メッセージタイプ.
     *  @param  in  funcメンバ関数ポインタ.
     */
    template<class F>
    void AddMessageFunc(const std::string &message_type, bool (F::*func)(const IPlugin*, void*))
    {
        F* cast_this = static_cast<F*>(this);
        m_message_functions.insert(std::make_pair(message_type, std::bind(func, cast_this, std::placeholders::_1, std::placeholders::_2)));
    }
private:
    /**
     *  @brief		ログプラグイン.
     *  @author		yatagaik.
     *  @param  in  sender 送り主プラグイン.
     *  @param  in  message_type メッセージタイプ.
     *  @param  in  param パラメータ.
     *  @return     trueで処理した falseで処理していない.
     */
    bool ReceiveMessage(const IPlugin *sender, const std::string &message_type, void *param)
    {
        auto it = m_message_functions.find(message_type);
        if (it != m_message_functions.end())
        {
            return it->second(sender, param);
        }
        return false;
    }
private:
    typedef std::map<const std::string, std::function<bool (const IPlugin * sender, void *param)> > MessageFunctionMap;
    MessageFunctionMap m_message_functions;


public:
    /**
     *  @brief		ログに出力.
     *  @author		yatagaik.
     *  @param  in  message 出力するメッセージ.
     */
    void LogWrite(const std::string &message) const
    {
        (*m_functions.AppLogWrite)(this, message);
    }

    /**
     *  @brief		ログに1行出力.
     *  @author		yatagaik.
     *  @param  in  message 出力するメッセージ.
     */
    void LogWriteLine(const std::string &message) const
    {
        (*m_functions.AppLogWrite)(this, message + "\n");
    }

    /**
     *  @brief		デバッグ用ログに出力.
     *  @author		yatagaik.
     *  @param  in  message 出力するメッセージ.
     */
    void DebugLogWrite(const std::string &message) const
    {
        (*m_functions.AppDebugLogWrite)(this, message);
    }

    /**
     *  @brief		デバッグ用ログに1行出力.
     *  @author		yatagaik.
     *  @param  in  message 出力するメッセージ.
     */
    void DebugLogWriteLine(const std::string &message) const
    {
        (*m_functions.AppDebugLogWrite)(this, message + "\n");
    }


public:
    /**
     *  @brief		メニュー用Widget追加.
     *  @author		yatagaik.
     *  @param  in  add_widget 追加するWidget.
     *  @param  in  label 追加するWidgetのラベル.
     *  @param  in  add_tab_name 追加するタブ.
     */
    void AddMenuWidget(QWidget *add_widget, const std::string &label, const std::string &add_tab_name)
    {
        (*m_functions.AppAddMenuWidget)(this, add_widget, label, add_tab_name);
    }

    /**
     *  @brief		ツール用Widget追加.
     *  @author		yatagaik.
     *  @param  in  add_widget 追加するWidget.
     *  @param  in  label 追加するWigetのラベル.
     */
    void AddToolWidget(QWidget *add_widget, const std::string &label)
    {
        (*m_functions.AppAddToolWidget)(this, add_widget, label);
    }

    /**
     *  @brief		ウィジェットの削除.
     *  @author		yatagaik.
     *  @param  in	remove_widget	削除するウィジェット.
     */
    void RemoveWidget(QWidget *remove_widget)
    {
        (*m_functions.AppRemoveWidget)(this, remove_widget);
    }

public:
    /**
     *  @brief		実行中かどうか.
     *  @author		yatagaik.
     *  @return     trueで実行中 falseで実行中でない.
     */
    bool IsExecute() const
    {
        return m_is_execute;
    }

public:
    /**
     *  @brief		プラグイン名の取得.
     *  @author		yatagaik.
     *  @return     プラグイン名.
     */
    virtual const char* GetName() const = 0;
    /**
     *  @brief		プラグインの説明取得.
     *  @author		yatagaik.
     *  @return     プラグインの説明.
     */
    virtual const char* GetExp() const = 0;
    /**
     *  @brief		Author名の取得.
     *  @author		yatagaik.
     *  @return     Author名の説明.
     */
    virtual const char* GetAuthor() const = 0;
    /**
     *  @brief		バージョンの取得.
     *  @author		yatagaik.
     *  @return     バージョン.
     */
    virtual const char* GetVersion() const = 0;
    /**
     *  @brief		スタートアッププラグインかどうか取得.
     *  @author		yatagaik.
     *  @return     trueでMetaTools起動時に自動で起動する.
     */
    virtual bool IsStartUp() const
    {
        return false;
    }
    /**
     *  @brief		プラグインアイコンの取得(90*90で表示).
     *  @author		yatagaik.
     *  @return     アイコン QIcon.IsNull()がtrueだとデフォルトのアイコンが使用される.
     */
    virtual QIcon* GetWidgetIcon() const
    {
        return m_widget_icon;
    }
protected:
    QIcon *m_widget_icon;

public:
    /**
     *  @brief		メニューウィジェットとツールウィジェットの閉じるボタンが押されたら呼ばれる.
     *  @author		yatagaik.
     *  @param  in	clicked_widget	閉じるボタンが押されたウィジェット.]
     *  @param  in  cancel trueを入れるとcancelされる.
     */
    virtual void OnClickCloseButton(QWidget * /*clicked_widget*/, bool &/*cancel*/)
    {
    }
protected:
    /**
     *  @brief		プラグイン起動時関数.
     *  @author		yatagaik.
     *  @return     trueで起動される.
     */
    virtual bool OnStart() = 0;
    /**
     *  @brief		プラグイン終了前処理.
     *  @author		yatagaik.
     *  @return     trueで終了する.
     */
    virtual bool OnClosing()
    {
        return true;
    }
    /**
     *  @brief		プラグイン終了自処理.
     *  @author		yatagaik.
     *  @return     trueで終了する.
     */
    virtual bool OnClose()
    {
        return true;
    }
private:
    bool m_is_execute;

private:
    const AppFunctions m_functions;


    friend class PluginManager;
};

}  // end namespace meta_tools
#endif // METATOOLSPLUGIN_H
