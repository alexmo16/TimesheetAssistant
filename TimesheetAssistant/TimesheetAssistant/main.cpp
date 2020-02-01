#include <QtWidgets/QApplication>

#include "TimesheetAssistant.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TimesheetAssistant w;
  w.show();
  return a.exec();
}
