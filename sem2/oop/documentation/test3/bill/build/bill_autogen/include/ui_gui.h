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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QListWidget *billsListWidget;
    QPushButton *calculateButton;
    QCheckBox *unpaidCheckBox;
    QLineEdit *companyLineEdit;
    QLabel *resultLabel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(400, 300);
        widget = new QWidget(Form);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 371, 281));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        billsListWidget = new QListWidget(widget);
        billsListWidget->setObjectName("billsListWidget");

        verticalLayout_3->addWidget(billsListWidget);

        calculateButton = new QPushButton(widget);
        calculateButton->setObjectName("calculateButton");

        verticalLayout_3->addWidget(calculateButton);

        unpaidCheckBox = new QCheckBox(widget);
        unpaidCheckBox->setObjectName("unpaidCheckBox");

        verticalLayout_3->addWidget(unpaidCheckBox);

        companyLineEdit = new QLineEdit(widget);
        companyLineEdit->setObjectName("companyLineEdit");

        verticalLayout_3->addWidget(companyLineEdit);

        resultLabel = new QLabel(widget);
        resultLabel->setObjectName("resultLabel");

        verticalLayout_3->addWidget(resultLabel);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        calculateButton->setText(QCoreApplication::translate("Form", "Calulate total", nullptr));
        unpaidCheckBox->setText(QCoreApplication::translate("Form", "show only unpaid", nullptr));
        companyLineEdit->setText(QCoreApplication::translate("Form", "Company name input", nullptr));
        resultLabel->setText(QCoreApplication::translate("Form", "Total/error result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
