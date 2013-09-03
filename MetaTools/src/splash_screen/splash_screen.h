#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit SplashScreen(QWidget *parent = 0);
    ~SplashScreen();
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void repaint();

private slots:
    void Animation();
private:
    enum AnimateStatus
    {
        STATE_SHOW,
        STATE_MAIN,
        STATE_HIDE,
        STATE_END
    };
    AnimateStatus m_animate_status;
private:
    Ui::SplashScreen *ui;
    QImage m_splash_screen_image;
    QTimer m_animate_timer;

public:
    void FinishMainWindowShow()
    {
        m_finish_main_window_show = true;
    }
private:
    bool m_finish_main_window_show;
};

#endif // SPLASH_SCREEN_H
