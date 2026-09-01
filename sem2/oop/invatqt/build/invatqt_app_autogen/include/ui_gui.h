/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *csvButton;
    QPushButton *htmlButton;
    QWidget *page_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *adminButton;
    QPushButton *userButton;
    QWidget *page_3;
    QListWidget *listWidget;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *removeButton;
    QPushButton *backButton;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *secondsLabel_2;
    QLineEdit *secondsLineEdit_2;
    QLabel *likesLabel_2;
    QLineEdit *likesLineEdit_2;
    QLabel *linkLabel_2;
    QLineEdit *linkLineEdit_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *titleLabel;
    QLineEdit *titleLineEdit;
    QLabel *presenterLabel;
    QLineEdit *presenterLineEdit;
    QLabel *minutesLabel;
    QLineEdit *minutesLineEdit;
    QWidget *page_4;
    QListWidget *listWidget_2;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *titleLabel_2;
    QLineEdit *titleLineEdit_2;
    QLabel *presenterLabel_2;
    QLineEdit *presenterLineEdit_2;
    QLabel *like01Label;
    QLineEdit *like01LineEdit;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *browseButton;
    QPushButton *removeWatchlist;
    QPushButton *openWatchlist;
    QPushButton *backButton_2;
    QWidget *page_5;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *nextButton;
    QPushButton *openLink;
    QPushButton *addWatchlist;
    QPushButton *backButton_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(400, 284);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(Form);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 371, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 210, 371, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        csvButton = new QPushButton(horizontalLayoutWidget);
        csvButton->setObjectName("csvButton");

        horizontalLayout->addWidget(csvButton);

        htmlButton = new QPushButton(horizontalLayoutWidget);
        htmlButton->setObjectName("htmlButton");

        horizontalLayout->addWidget(htmlButton);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayoutWidget_2 = new QWidget(page_2);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 371, 201));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        horizontalLayoutWidget_2 = new QWidget(page_2);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(0, 200, 371, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        adminButton = new QPushButton(horizontalLayoutWidget_2);
        adminButton->setObjectName("adminButton");

        horizontalLayout_3->addWidget(adminButton);

        userButton = new QPushButton(horizontalLayoutWidget_2);
        userButton->setObjectName("userButton");

        horizontalLayout_3->addWidget(userButton);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        listWidget = new QListWidget(page_3);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 381, 131));
        horizontalLayoutWidget_3 = new QWidget(page_3);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(0, 210, 381, 51));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        addButton = new QPushButton(horizontalLayoutWidget_3);
        addButton->setObjectName("addButton");

        horizontalLayout_4->addWidget(addButton);

        updateButton = new QPushButton(horizontalLayoutWidget_3);
        updateButton->setObjectName("updateButton");

        horizontalLayout_4->addWidget(updateButton);

        removeButton = new QPushButton(horizontalLayoutWidget_3);
        removeButton->setObjectName("removeButton");

        horizontalLayout_4->addWidget(removeButton);

        backButton = new QPushButton(horizontalLayoutWidget_3);
        backButton->setObjectName("backButton");

        horizontalLayout_4->addWidget(backButton);

        formLayoutWidget_2 = new QWidget(page_3);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(190, 130, 191, 81));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        secondsLabel_2 = new QLabel(formLayoutWidget_2);
        secondsLabel_2->setObjectName("secondsLabel_2");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, secondsLabel_2);

        secondsLineEdit_2 = new QLineEdit(formLayoutWidget_2);
        secondsLineEdit_2->setObjectName("secondsLineEdit_2");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, secondsLineEdit_2);

        likesLabel_2 = new QLabel(formLayoutWidget_2);
        likesLabel_2->setObjectName("likesLabel_2");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, likesLabel_2);

        likesLineEdit_2 = new QLineEdit(formLayoutWidget_2);
        likesLineEdit_2->setObjectName("likesLineEdit_2");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, likesLineEdit_2);

        linkLabel_2 = new QLabel(formLayoutWidget_2);
        linkLabel_2->setObjectName("linkLabel_2");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, linkLabel_2);

        linkLineEdit_2 = new QLineEdit(formLayoutWidget_2);
        linkLineEdit_2->setObjectName("linkLineEdit_2");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, linkLineEdit_2);

        formLayoutWidget = new QWidget(page_3);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(0, 130, 191, 81));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(formLayoutWidget);
        titleLabel->setObjectName("titleLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, titleLabel);

        titleLineEdit = new QLineEdit(formLayoutWidget);
        titleLineEdit->setObjectName("titleLineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, titleLineEdit);

        presenterLabel = new QLabel(formLayoutWidget);
        presenterLabel->setObjectName("presenterLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, presenterLabel);

        presenterLineEdit = new QLineEdit(formLayoutWidget);
        presenterLineEdit->setObjectName("presenterLineEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, presenterLineEdit);

        minutesLabel = new QLabel(formLayoutWidget);
        minutesLabel->setObjectName("minutesLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, minutesLabel);

        minutesLineEdit = new QLineEdit(formLayoutWidget);
        minutesLineEdit->setObjectName("minutesLineEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, minutesLineEdit);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        listWidget_2 = new QListWidget(page_4);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(0, 0, 381, 121));
        formLayoutWidget_3 = new QWidget(page_4);
        formLayoutWidget_3->setObjectName("formLayoutWidget_3");
        formLayoutWidget_3->setGeometry(QRect(110, 120, 160, 81));
        formLayout_3 = new QFormLayout(formLayoutWidget_3);
        formLayout_3->setObjectName("formLayout_3");
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        titleLabel_2 = new QLabel(formLayoutWidget_3);
        titleLabel_2->setObjectName("titleLabel_2");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, titleLabel_2);

        titleLineEdit_2 = new QLineEdit(formLayoutWidget_3);
        titleLineEdit_2->setObjectName("titleLineEdit_2");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, titleLineEdit_2);

        presenterLabel_2 = new QLabel(formLayoutWidget_3);
        presenterLabel_2->setObjectName("presenterLabel_2");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::LabelRole, presenterLabel_2);

        presenterLineEdit_2 = new QLineEdit(formLayoutWidget_3);
        presenterLineEdit_2->setObjectName("presenterLineEdit_2");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::FieldRole, presenterLineEdit_2);

        like01Label = new QLabel(formLayoutWidget_3);
        like01Label->setObjectName("like01Label");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::LabelRole, like01Label);

        like01LineEdit = new QLineEdit(formLayoutWidget_3);
        like01LineEdit->setObjectName("like01LineEdit");

        formLayout_3->setWidget(2, QFormLayout::ItemRole::FieldRole, like01LineEdit);

        horizontalLayoutWidget_4 = new QWidget(page_4);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(0, 200, 381, 61));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        browseButton = new QPushButton(horizontalLayoutWidget_4);
        browseButton->setObjectName("browseButton");

        horizontalLayout_5->addWidget(browseButton);

        removeWatchlist = new QPushButton(horizontalLayoutWidget_4);
        removeWatchlist->setObjectName("removeWatchlist");

        horizontalLayout_5->addWidget(removeWatchlist);

        openWatchlist = new QPushButton(horizontalLayoutWidget_4);
        openWatchlist->setObjectName("openWatchlist");

        horizontalLayout_5->addWidget(openWatchlist);

        backButton_2 = new QPushButton(horizontalLayoutWidget_4);
        backButton_2->setObjectName("backButton_2");

        horizontalLayout_5->addWidget(backButton_2);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        horizontalLayoutWidget_5 = new QWidget(page_5);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(0, 0, 381, 191));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_5);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_3);

        horizontalLayoutWidget_6 = new QWidget(page_5);
        horizontalLayoutWidget_6->setObjectName("horizontalLayoutWidget_6");
        horizontalLayoutWidget_6->setGeometry(QRect(0, 190, 381, 71));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        nextButton = new QPushButton(horizontalLayoutWidget_6);
        nextButton->setObjectName("nextButton");

        horizontalLayout_7->addWidget(nextButton);

        openLink = new QPushButton(horizontalLayoutWidget_6);
        openLink->setObjectName("openLink");

        horizontalLayout_7->addWidget(openLink);

        addWatchlist = new QPushButton(horizontalLayoutWidget_6);
        addWatchlist->setObjectName("addWatchlist");

        horizontalLayout_7->addWidget(addWatchlist);

        backButton_3 = new QPushButton(horizontalLayoutWidget_6);
        backButton_3->setObjectName("backButton_3");

        horizontalLayout_7->addWidget(backButton_3);

        stackedWidget->addWidget(page_5);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);


        retranslateUi(Form);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "Choose watchlist type!", nullptr));
        csvButton->setText(QCoreApplication::translate("Form", "CSV", nullptr));
        htmlButton->setText(QCoreApplication::translate("Form", "HTML", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Choose mode!", nullptr));
        adminButton->setText(QCoreApplication::translate("Form", "ADMIN", nullptr));
        userButton->setText(QCoreApplication::translate("Form", "USER", nullptr));
        addButton->setText(QCoreApplication::translate("Form", "Add", nullptr));
        updateButton->setText(QCoreApplication::translate("Form", "Update", nullptr));
        removeButton->setText(QCoreApplication::translate("Form", "Remove", nullptr));
        backButton->setText(QCoreApplication::translate("Form", "Back", nullptr));
        secondsLabel_2->setText(QCoreApplication::translate("Form", "Seconds:", nullptr));
        likesLabel_2->setText(QCoreApplication::translate("Form", "Likes:", nullptr));
        linkLabel_2->setText(QCoreApplication::translate("Form", "Link:", nullptr));
        titleLabel->setText(QCoreApplication::translate("Form", "Title:", nullptr));
        presenterLabel->setText(QCoreApplication::translate("Form", "Presenter:", nullptr));
        minutesLabel->setText(QCoreApplication::translate("Form", "Minutes:", nullptr));
        titleLabel_2->setText(QCoreApplication::translate("Form", "Title:", nullptr));
        presenterLabel_2->setText(QCoreApplication::translate("Form", "Presenter:", nullptr));
        like01Label->setText(QCoreApplication::translate("Form", "Like(0/1):", nullptr));
        browseButton->setText(QCoreApplication::translate("Form", "Browse", nullptr));
        removeWatchlist->setText(QCoreApplication::translate("Form", "Remove", nullptr));
        openWatchlist->setText(QCoreApplication::translate("Form", "Open", nullptr));
        backButton_2->setText(QCoreApplication::translate("Form", "Back", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "Aici vine tutorialul", nullptr));
        nextButton->setText(QCoreApplication::translate("Form", "Next", nullptr));
        openLink->setText(QCoreApplication::translate("Form", "Open", nullptr));
        addWatchlist->setText(QCoreApplication::translate("Form", "Add", nullptr));
        backButton_3->setText(QCoreApplication::translate("Form", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
