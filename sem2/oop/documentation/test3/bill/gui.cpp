#include "gui.h"
#include "ui_gui.h"
#include <QErrorMessage>
#include <QMessageBox>

GUI::GUI(Service &service, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form), service(service) {
  ui->setupUi(this);
  this->populateList();
  this->connectSignals();
}

GUI::~GUI() { delete ui; }

void GUI::populateList() {
  ui->billsListWidget->clear();

  for (auto bill : this->service.getAllSorted()) {
    QString text = QString::fromStdString(bill.getCompName() + " | " +
                                          std::to_string(bill.getSum()));

    QListWidgetItem *item = new QListWidgetItem(text);
    if (bill.getPaid() == false)
      item->setBackground(Qt::red);

    ui->billsListWidget->addItem(item);
  }
}

void GUI::connectSignals() {
  QObject::connect(
      ui->unpaidCheckBox, &QCheckBox::checkStateChanged, this, [this]() {
        ui->billsListWidget->clear();

        std::vector<Bill> bills;
        if (ui->unpaidCheckBox->isChecked())
          bills = this->service.getFiltered(false);
        else
          bills = this->service.getAllSorted();

        for (auto bill : bills) {
          QString text = QString::fromStdString(bill.getCompName() + " | " +
                                                std::to_string(bill.getSum()));

          QListWidgetItem *item = new QListWidgetItem(text);
          if (bill.getPaid() == false)
            item->setBackground(Qt::red);

          ui->billsListWidget->addItem(item);
        }
      });

  QObject::connect(ui->calculateButton, &QPushButton::clicked, this, [this]() {
    float total =
        this->service.getTotalUnpaid(ui->companyLineEdit->text().toStdString());

    if (total == 0) {
      QMessageBox::critical(this, "Error", "No such unpaid company.");
      return;
    }

    ui->resultLabel->setText(QString::fromStdString(std::to_string(total)));
  });
}
