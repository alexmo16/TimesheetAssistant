#include "TimesheetAssistant.h"

#include <ui_TimesheetAssistant.h>

TimesheetAssistant::TimesheetAssistant(QWidget *parent)
    : QMainWindow(parent), m_ui(std::make_shared<Ui::TimesheetAssistant>()) {
  m_ui->setupUi(this);
}
