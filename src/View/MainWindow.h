#pragma once

#include "ui_MainWindow.h"

#include "Components/HelpDialog.h"
#include "Model/Events/Event.h"

#include <QDate>
#include <QElapsedTimer>
#include <QLineEdit>
#include <QString>
#include <QTime>
#include <QVector>
#include <QtWidgets/QMainWindow>

namespace Model
{
	class ModelThread;
	class Timesheet;
	class QByteArray;

} // namespace Model

namespace View
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ = Q_NULLPTR );
		~MainWindow() = default;

	protected:
		void closeEvent( QCloseEvent* pEvent_ ) override;
		void paintEvent( QPaintEvent* pEvent_ ) override;

	private slots:
		void OnHelpAction( const bool checked_ );
		void OnTimesheetUpdated( const Model::Timesheet& timesheet_ );
		void OnRefreshClicked();

	private:
		void SetCurrentWeekLabel();

		Ui::MainWindowClass m_ui;
		HelpDialog m_helpDialog;
		std::shared_ptr<Model::ModelThread> m_pModelThread;
		QVector<QLineEdit*> m_workDays;
		QVector<QString> m_workDaysStrings;
		QDate m_mondayDate;
		QDate m_fridayDate;
		QTime m_currentDayTotalTime;
		QElapsedTimer m_currentDayTimer;
	};

} // namespace View
