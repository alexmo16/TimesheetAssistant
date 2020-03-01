#pragma once

#include "ui_MainWindow.h"

#include "Components/HelpDialog.h"

#include <QtWidgets/QMainWindow>

namespace Model
{
	class ModelThread;

} // namespace Model

namespace View
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ = Q_NULLPTR );

		void MainWindow::closeEvent( QCloseEvent* pEvent_ ) override;

	private slots:
		void OnHelpAction( const bool checked_ );

	private:
		void setCurrentWeekLabel();

		Ui::MainWindowClass m_ui;
		HelpDialog m_helpDialog;

		std::shared_ptr<Model::ModelThread> m_pModelThread;
	};

} // namespace View
