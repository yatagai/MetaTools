/**
 * �v���O�C���̃C���^�[�t�F�[�X�̎���.
 * @file plugin.cpp.
 * @author yatagai.
 */

#include "plugin.h"

namespace meta_tools
{
extern bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
extern void AppLogWrite(const IPlugin *writer, const std::string &message);
extern void AppDebugLogWrite(const IPlugin *writer, const std::string &message);
extern void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &add_tab_name);
extern void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget);

/**
 * �R���X�g���N�^.
 */
IPlugin::IPlugin()
    : m_is_execute(false)
{
}

/**
 * �f�X�g���N�^.
 */
IPlugin::~IPlugin()
{
}

/**
 *  �v���O�C���̊J�n.
 *  @return true�Ő��� false�Ŏ��s.
 */
bool IPlugin::Start()
{
    if (OnStart())
    {
        m_is_execute = true;
    }
    return m_is_execute;
}

/**
 *  �v���O�C���̏I�����Ă��悢��.
 *  @return true�ŏI�����Ă��悢 false�ŏI��������_��.
 */
bool IPlugin::Closing()
{
    return OnClosing();
}

/**
 *  �v���O�C���̏I��.
 *  @return true�Ő��� false�Ŏ��s.
 */
bool IPlugin::Close()
{
    if (OnClose())
    {
        m_is_execute = false;
    }

    return !m_is_execute;
}

/**
 *  �v���O�C���Ƀ��b�Z�[�W���M.
 *  @param in target_plugin_name ���M��̃v���O�C����.
 *  @param in message_type ���b�Z�[�W�^�C�v.
 *  @param in param �p�����[�^.
 */
bool IPlugin::SendMessage(const std::string &target_plugin_name, const std::string &message_type, void *param) const
{
    return AppSendMessage(this, target_plugin_name, message_type, param);
}

/**
 *  ���O�ɏo��.
 *  @param in message �o�͂��郁�b�Z�[�W.
 */
void IPlugin::LogWrite(const std::string &message) const
{
    AppLogWrite(this, message);
}

/**
 *  ���O��1�s�o��.
 *  @param message �o�͂��郁�b�Z�[�W.
 */
void IPlugin::LogWriteLine(const std::string &message) const
{
    AppLogWrite(this, message + "\n");
}

/**
 *  �f�o�b�O�p���O�ɏo��.
 *  @param in message �o�͂��郁�b�Z�[�W.
 */
void IPlugin::DebugLogWrite(const std::string &message) const
{
    AppDebugLogWrite(this, message);
}

/**
 *  �f�o�b�O�p���O��1�s�o��.
 *  @param in message �o�͂��郁�b�Z�[�W.
 */
void IPlugin::DebugLogWriteLine(const std::string &message) const
{
    AppDebugLogWrite(this, message + "\n");
}

/**
 *  ���j���[�pWidget�ǉ�.
 *  @param in add_widget �ǉ�����Widget.
 *  @param in add_tab_name �ǉ�����^�u.
 */
void IPlugin::AddMenuWidget(QWidget *add_widget, const std::string &add_tab_name)
{
    AppAddMenuWidget(this, add_widget, add_tab_name);
}

/**
 *  �c�[���pWidget�ǉ�.
 *  @param in add_widget �ǉ�����Widget.
 */
void IPlugin::AddToolWidget(QWidget *add_widget)
{
    AppAddToolWidget(this, add_widget);
}

}   // end namesapce meta_tools
