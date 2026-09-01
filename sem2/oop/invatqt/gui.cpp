#include "gui.h"
#include "ui_gui.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

GUI::GUI(Services &csv_service, Services &html_service, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form), csv_service(csv_service),
      html_service(html_service) {
  ui->setupUi(this);
  this->service = nullptr;
  this->current_index = 0;
  this->connect_signals();
}

GUI::~GUI() { delete ui; }

QString GUI::tutorial_to_qstring(Tutorial tutorial) {
  Duration d = tutorial.get_duration();
  std::string text =
      tutorial.get_title() + " | " + tutorial.get_presenter() + " | " +
      std::to_string(d.get_min()) + ":" + std::to_string(d.get_sec()) + " | " +
      std::to_string(tutorial.get_likes()) + " | " + tutorial.get_link();
  return QString::fromStdString(text);
}

void GUI::populate_admin_list() {
  ui->listWidget->clear();
  for (auto tutorial : this->service->get_all())
    ui->listWidget->addItem(this->tutorial_to_qstring(tutorial));
}

void GUI::populate_watch_list() {
  ui->listWidget_2->clear();
  for (auto tutorial : this->service->get_watchlist())
    ui->listWidget_2->addItem(this->tutorial_to_qstring(tutorial));
}

void GUI::show_current_tutorial() {
  if (this->filtered.empty()) {
    ui->label_3->setText("No tutorials found.");
    return;
  }

  Tutorial tutorial = this->filtered[this->current_index];
  ui->label_3->setText(this->tutorial_to_qstring(tutorial));
}

void GUI::connect_signals() {
  connect(ui->csvButton, &QPushButton::clicked, this, [this]() {
    this->service = &this->csv_service;
    ui->stackedWidget->setCurrentIndex(1);
  });

  connect(ui->htmlButton, &QPushButton::clicked, this, [this]() {
    this->service = &this->html_service;
    ui->stackedWidget->setCurrentIndex(1);
  });

  connect(ui->adminButton, &QPushButton::clicked, this, [this]() {
    this->populate_admin_list();
    ui->stackedWidget->setCurrentIndex(2);
  });

  connect(ui->userButton, &QPushButton::clicked, this, [this]() {
    this->populate_watch_list();
    ui->stackedWidget->setCurrentIndex(3);
  });

  connect(ui->backButton, &QPushButton::clicked, this,
          [this]() { ui->stackedWidget->setCurrentIndex(1); });

  connect(ui->backButton_2, &QPushButton::clicked, this,
          [this]() { ui->stackedWidget->setCurrentIndex(1); });

  connect(ui->backButton_3, &QPushButton::clicked, this, [this]() {
    this->populate_watch_list();
    ui->stackedWidget->setCurrentIndex(3);
  });

  connect(ui->addButton, &QPushButton::clicked, this, [this]() {
    try {
      this->service->add_tutorial(ui->titleLineEdit->text().toStdString(),
                                  ui->presenterLineEdit->text().toStdString(),
                                  ui->minutesLineEdit->text().toInt(),
                                  ui->secondsLineEdit_2->text().toInt(),
                                  ui->likesLineEdit_2->text().toInt(),
                                  ui->linkLineEdit_2->text().toStdString());
      this->populate_admin_list();
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  });

  connect(ui->updateButton, &QPushButton::clicked, this, [this]() {
    try {
      this->service->update_tutorial(
          ui->titleLineEdit->text().toStdString(),
          ui->presenterLineEdit->text().toStdString(),
          ui->minutesLineEdit->text().toInt(),
          ui->secondsLineEdit_2->text().toInt(),
          ui->likesLineEdit_2->text().toInt(),
          ui->linkLineEdit_2->text().toStdString());
      this->populate_admin_list();
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  });

  connect(ui->removeButton, &QPushButton::clicked, this, [this]() {
    try {
      this->service->delete_tutorial(
          ui->titleLineEdit->text().toStdString(),
          ui->presenterLineEdit->text().toStdString());
      this->populate_admin_list();
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  });

  connect(ui->listWidget, &QListWidget::itemClicked, this, [this]() {
    int index = ui->listWidget->currentRow();
    auto tutorials = this->service->get_all();
    if (index < 0 || index >= (int)tutorials.size())
      return;

    Tutorial tutorial = tutorials[index];
    Duration d = tutorial.get_duration();

    ui->titleLineEdit->setText(QString::fromStdString(tutorial.get_title()));
    ui->presenterLineEdit->setText(
        QString::fromStdString(tutorial.get_presenter()));
    ui->minutesLineEdit->setText(QString::number(d.get_min()));
    ui->secondsLineEdit_2->setText(QString::number(d.get_sec()));
    ui->likesLineEdit_2->setText(QString::number(tutorial.get_likes()));
    ui->linkLineEdit_2->setText(QString::fromStdString(tutorial.get_link()));
  });

  connect(ui->browseButton, &QPushButton::clicked, this, [this]() {
    this->filtered = this->service->get_tutorial_by_presenter(
        ui->presenterLineEdit_2->text().toStdString());
    this->current_index = 0;
    this->show_current_tutorial();
    ui->stackedWidget->setCurrentIndex(4);
  });

  connect(ui->removeWatchlist, &QPushButton::clicked, this, [this]() {
    try {
      this->service->delete_from_watch_list(
          ui->titleLineEdit_2->text().toStdString(),
          ui->presenterLineEdit_2->text().toStdString(),
          ui->like01LineEdit->text().toInt() == 1);
      this->populate_watch_list();
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  });

  connect(ui->openWatchlist, &QPushButton::clicked, this,
          [this]() { this->service->display_watchlist(); });

  connect(ui->listWidget_2, &QListWidget::itemClicked, this, [this]() {
    int index = ui->listWidget_2->currentRow();
    auto tutorials = this->service->get_watchlist();
    if (index < 0 || index >= (int)tutorials.size())
      return;

    Tutorial tutorial = tutorials[index];
    ui->titleLineEdit_2->setText(QString::fromStdString(tutorial.get_title()));
    ui->presenterLineEdit_2->setText(
        QString::fromStdString(tutorial.get_presenter()));
  });

  connect(ui->nextButton, &QPushButton::clicked, this, [this]() {
    if (this->filtered.empty())
      return;
    this->current_index++;
    if (this->current_index == (int)this->filtered.size())
      this->current_index = 0;
    this->show_current_tutorial();
  });

  connect(ui->openLink, &QPushButton::clicked, this, [this]() {
    if (this->filtered.empty())
      return;
    Tutorial tutorial = this->filtered[this->current_index];
    QDesktopServices::openUrl(
        QUrl(QString::fromStdString(tutorial.get_link())));
  });

  connect(ui->addWatchlist, &QPushButton::clicked, this, [this]() {
    try {
      if (this->filtered.empty())
        return;
      this->service->add_to_watchlist(this->filtered[this->current_index]);
      QMessageBox::information(this, "Success", "Tutorial added.");
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  });
}
