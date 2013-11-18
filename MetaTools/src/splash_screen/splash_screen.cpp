#include "splash_screen.h"
#include "ui_splash_screen.h"
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent, Qt::SplashScreen),
    m_animate_status(STATE_SHOW),
    ui(new Ui::SplashScreen()),
    m_splash_screen_image(":/metatools_resource/img/meta_tools_splash.png"),
    m_finish_main_window_show(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);

    // connect(&m_animate_timer, SIGNAL(timeout()), SLOT(Animation()));
    m_animate_timer.start(10);

    setWindowOpacity(0.0f);

    QRect geometry(geometry());
    geometry.setWidth(0);
    geometry.setHeight(0);
    QDesktopWidget *desk_top = QApplication::desktop();
    QRect screen_geometry = desk_top->screenGeometry();
    int screen_center_x = screen_geometry.width() / 2;
    int screen_center_y = screen_geometry.height() / 2;
    geometry.setLeft(screen_center_x - 1280 / 2.0f);
    geometry.setTop(screen_center_y - 350 / 2.0f);
    this->setGeometry(geometry);

    repaint();
}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(305, 0, m_splash_screen_image);
    painter.end();
}

void SplashScreen::repaint()
{
    QWidget::repaint();
}

void SplashScreen::Animation()
{
    static const char LOADING_TEXT_U[] = "STARTING META TOOLS";
    static const char LOADING_TEXT_L[] = "starting-meta-tools";
    static const int MAX_PROGRESS_COUNT = sizeof(LOADING_TEXT_U);
    static int progress_counter = 0;
    static bool show_end_ok = false;
    char progress_text[MAX_PROGRESS_COUNT]  = {0};

    switch (m_animate_status)
    {
    case STATE_SHOW:
    {
        setWindowOpacity(windowOpacity() + 0.1f);
        QRect geometry(geometry());
        geometry.setWidth(1280 * windowOpacity());
        geometry.setHeight(350 * windowOpacity());
        this->setGeometry(geometry);
        if (windowOpacity() >= 1.0f)
        {
            m_animate_status = STATE_MAIN;
            m_animate_timer.stop();
            m_animate_timer.start(5);
        }
    }
        break;

    case STATE_MAIN:
        progress_counter = (progress_counter + 1) % (MAX_PROGRESS_COUNT);
        show_end_ok = show_end_ok || progress_counter == 10; // すぐに閉じるとなにかわからないので10回は最低待つ.
        for (int i = 0; i < MAX_PROGRESS_COUNT; ++i)
        {
            if (i == progress_counter)
            {
                progress_text[i] = LOADING_TEXT_U[i];
            }
            else
            {
                progress_text[i] = LOADING_TEXT_L[i];
            }
        }
        ui->NowLoading->setText(progress_text);

        if (m_finish_main_window_show && show_end_ok)
        {
            m_animate_status = STATE_HIDE;
            ui->NowLoading->setText("");
            m_animate_timer.start(5);
        }
        else
        {
            m_animate_timer.stop();
            m_animate_timer.start(150);
        }
        break;

    case STATE_HIDE:
    {
        setWindowOpacity(windowOpacity() - 0.05f);
        QRect geometry(geometry());
        geometry.setY(geometry.y() - (350 * 0.05) / 2);
        geometry.setHeight(350 * windowOpacity());
        this->setGeometry(geometry);
        if (windowOpacity() <= 0.0f)
        {
            m_animate_status = STATE_END;
            m_animate_timer.stop();
            close();
        }
    }
        break;
    }
}
