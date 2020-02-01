#pragma once

#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>

namespace View {
	class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = Q_NULLPTR);

	private:
		Ui::MainWindowClass ui;
	};
}
