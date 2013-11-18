/********************************************************************************
** Form generated from reading UI file 'main_form.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_FORM_H
#define UI_MAIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *main_view;
    QVBoxLayout *verticalLayout_2;
    QWidget *sub_menu;
    QHBoxLayout *horizontalLayout_3;
    QSlider *scale_slider;
    QLabel *scale_label;
    QLabel *label;
    QWidget *font_color;
    QLabel *label_4;
    QWidget *outline_color;
    QLabel *label_2;
    QWidget *bg_color;
    QCheckBox *bound;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLineEdit *font_path;
    QLabel *label_6;
    QComboBox *texture_size_list;
    QLabel *label_7;
    QSpinBox *font_size;
    QLabel *label_3;
    QCheckBox *outline_enable;
    QDoubleSpinBox *outline_width;
    QLabel *label_8;
    QPlainTextEdit *create_text;
    QWidget *button_widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *use_all_ascii;
    QPushButton *use_all_kana;
    QPushButton *use_all_kanji;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->resize(1139, 278);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/font_creator_resource/img/font_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainForm->setWindowIcon(icon);
        MainForm->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(MainForm);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        main_view = new QWidget(MainForm);
        main_view->setObjectName(QStringLiteral("main_view"));
        verticalLayout_2 = new QVBoxLayout(main_view);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        sub_menu = new QWidget(main_view);
        sub_menu->setObjectName(QStringLiteral("sub_menu"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sub_menu->sizePolicy().hasHeightForWidth());
        sub_menu->setSizePolicy(sizePolicy1);
        sub_menu->setMinimumSize(QSize(0, 25));
        sub_menu->setMaximumSize(QSize(16777215, 25));
        horizontalLayout_3 = new QHBoxLayout(sub_menu);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        scale_slider = new QSlider(sub_menu);
        scale_slider->setObjectName(QStringLiteral("scale_slider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scale_slider->sizePolicy().hasHeightForWidth());
        scale_slider->setSizePolicy(sizePolicy2);
        scale_slider->setMinimumSize(QSize(200, 0));
        scale_slider->setMinimum(20);
        scale_slider->setMaximum(800);
        scale_slider->setValue(100);
        scale_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(scale_slider);

        scale_label = new QLabel(sub_menu);
        scale_label->setObjectName(QStringLiteral("scale_label"));
        sizePolicy2.setHeightForWidth(scale_label->sizePolicy().hasHeightForWidth());
        scale_label->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(12);
        scale_label->setFont(font);

        horizontalLayout_3->addWidget(scale_label);

        label = new QLabel(sub_menu);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        font_color = new QWidget(sub_menu);
        font_color->setObjectName(QStringLiteral("font_color"));
        sizePolicy2.setHeightForWidth(font_color->sizePolicy().hasHeightForWidth());
        font_color->setSizePolicy(sizePolicy2);
        font_color->setMinimumSize(QSize(30, 15));

        horizontalLayout_3->addWidget(font_color);

        label_4 = new QLabel(sub_menu);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        outline_color = new QWidget(sub_menu);
        outline_color->setObjectName(QStringLiteral("outline_color"));
        sizePolicy2.setHeightForWidth(outline_color->sizePolicy().hasHeightForWidth());
        outline_color->setSizePolicy(sizePolicy2);
        outline_color->setMinimumSize(QSize(30, 15));

        horizontalLayout_3->addWidget(outline_color);

        label_2 = new QLabel(sub_menu);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        bg_color = new QWidget(sub_menu);
        bg_color->setObjectName(QStringLiteral("bg_color"));
        sizePolicy2.setHeightForWidth(bg_color->sizePolicy().hasHeightForWidth());
        bg_color->setSizePolicy(sizePolicy2);
        bg_color->setMinimumSize(QSize(30, 15));

        horizontalLayout_3->addWidget(bg_color);

        bound = new QCheckBox(sub_menu);
        bound->setObjectName(QStringLiteral("bound"));
        bound->setChecked(true);

        horizontalLayout_3->addWidget(bound);


        verticalLayout_2->addWidget(sub_menu);

        graphicsView = new QGraphicsView(main_view);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);
        graphicsView->setMinimumSize(QSize(0, 1));
        graphicsView->setMaximumSize(QSize(10, 16777215));
        graphicsView->setAcceptDrops(false);
        graphicsView->setAutoFillBackground(false);

        verticalLayout_2->addWidget(graphicsView);


        horizontalLayout->addWidget(main_view);

        widget = new QWidget(MainForm);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 2, 5, 2);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);
        label_5->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(label_5);

        font_path = new QLineEdit(widget);
        font_path->setObjectName(QStringLiteral("font_path"));
        font_path->setReadOnly(true);

        verticalLayout->addWidget(font_path);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(label_6);

        texture_size_list = new QComboBox(widget);
        texture_size_list->setObjectName(QStringLiteral("texture_size_list"));
        sizePolicy4.setHeightForWidth(texture_size_list->sizePolicy().hasHeightForWidth());
        texture_size_list->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(texture_size_list);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(label_7);

        font_size = new QSpinBox(widget);
        font_size->setObjectName(QStringLiteral("font_size"));
        font_size->setWrapping(false);
        font_size->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        font_size->setMinimum(9);
        font_size->setMaximum(100);
        font_size->setValue(30);

        verticalLayout->addWidget(font_size);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        outline_enable = new QCheckBox(widget);
        outline_enable->setObjectName(QStringLiteral("outline_enable"));
        outline_enable->setChecked(true);
        outline_enable->setTristate(false);

        verticalLayout->addWidget(outline_enable);

        outline_width = new QDoubleSpinBox(widget);
        outline_width->setObjectName(QStringLiteral("outline_width"));
        outline_width->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        outline_width->setDecimals(1);
        outline_width->setMinimum(0.5);
        outline_width->setMaximum(10);
        outline_width->setSingleStep(0.1);
        outline_width->setValue(1);

        verticalLayout->addWidget(outline_width);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy4.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy4);
        label_8->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(label_8);

        create_text = new QPlainTextEdit(widget);
        create_text->setObjectName(QStringLiteral("create_text"));
        sizePolicy.setHeightForWidth(create_text->sizePolicy().hasHeightForWidth());
        create_text->setSizePolicy(sizePolicy);
        create_text->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(create_text);

        button_widget = new QWidget(widget);
        button_widget->setObjectName(QStringLiteral("button_widget"));
        sizePolicy4.setHeightForWidth(button_widget->sizePolicy().hasHeightForWidth());
        button_widget->setSizePolicy(sizePolicy4);
        button_widget->setMinimumSize(QSize(0, 25));
        horizontalLayout_2 = new QHBoxLayout(button_widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        use_all_ascii = new QPushButton(button_widget);
        use_all_ascii->setObjectName(QStringLiteral("use_all_ascii"));
        sizePolicy2.setHeightForWidth(use_all_ascii->sizePolicy().hasHeightForWidth());
        use_all_ascii->setSizePolicy(sizePolicy2);
        use_all_ascii->setMinimumSize(QSize(30, 25));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        use_all_ascii->setFont(font1);

        horizontalLayout_2->addWidget(use_all_ascii);

        use_all_kana = new QPushButton(button_widget);
        use_all_kana->setObjectName(QStringLiteral("use_all_kana"));
        sizePolicy2.setHeightForWidth(use_all_kana->sizePolicy().hasHeightForWidth());
        use_all_kana->setSizePolicy(sizePolicy2);
        use_all_kana->setMinimumSize(QSize(120, 25));
        QFont font2;
        font2.setFamily(QStringLiteral("MS UI Gothic"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        use_all_kana->setFont(font2);

        horizontalLayout_2->addWidget(use_all_kana);

        use_all_kanji = new QPushButton(button_widget);
        use_all_kanji->setObjectName(QStringLiteral("use_all_kanji"));
        sizePolicy2.setHeightForWidth(use_all_kanji->sizePolicy().hasHeightForWidth());
        use_all_kanji->setSizePolicy(sizePolicy2);
        use_all_kanji->setMinimumSize(QSize(30, 25));
        use_all_kanji->setFont(font1);

        horizontalLayout_2->addWidget(use_all_kanji);


        verticalLayout->addWidget(button_widget);


        horizontalLayout->addWidget(widget);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        scale_label->setText(QApplication::translate("MainForm", "100%", 0));
        label->setText(QApplication::translate("MainForm", "FontColor", 0));
        label_4->setText(QApplication::translate("MainForm", "OutlineColor", 0));
        label_2->setText(QApplication::translate("MainForm", "BGColor", 0));
        bound->setText(QApplication::translate("MainForm", "BOUND", 0));
        label_5->setText(QApplication::translate("MainForm", "\343\203\225\343\202\251\343\203\263\343\203\210", 0));
        label_6->setText(QApplication::translate("MainForm", "\343\203\206\343\202\257\343\202\271\343\203\201\343\203\243\343\202\265\343\202\244\343\202\272", 0));
        label_7->setText(QApplication::translate("MainForm", "\343\203\225\343\202\251\343\203\263\343\203\210\343\202\265\343\202\244\343\202\272", 0));
        label_3->setText(QApplication::translate("MainForm", "\350\274\252\351\203\255\347\267\232", 0));
        outline_enable->setText(QString());
        label_8->setText(QApplication::translate("MainForm", "\347\224\237\346\210\220\343\203\206\343\202\255\343\202\271\343\203\210", 0));
        create_text->setPlainText(QString());
        use_all_ascii->setText(QApplication::translate("MainForm", "ASCII", 0));
        use_all_kana->setText(QApplication::translate("MainForm", "\343\201\213\343\201\252/\345\205\250\350\247\222\350\213\261\346\225\260\345\255\227", 0));
        use_all_kanji->setText(QApplication::translate("MainForm", "\346\274\242\345\255\227", 0));
        Q_UNUSED(MainForm);
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_FORM_H
