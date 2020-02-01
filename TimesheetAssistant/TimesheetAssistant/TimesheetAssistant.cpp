#include "TimesheetAssistant.h"

#include <ui_TimesheetAssistant.h>

TimesheetAssistant::TimesheetAssistant(QWidget *parent)
    : QMainWindow(parent), m_pUi(std::make_shared<Ui::TimesheetAssistant>()) {
  m_pUi->setupUi(this);
}
