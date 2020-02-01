#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
class TimesheetAssistant;
}

class TimesheetAssistant : public QMainWindow {
  Q_OBJECT

 public:
  TimesheetAssistant(QWidget* parent = Q_NULLPTR);

 private:
  std::shared_ptr<Ui::TimesheetAssistant> m_ui;
};
