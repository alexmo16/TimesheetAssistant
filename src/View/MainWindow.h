#pragma once

#include "ui_MainWindow.h"

#include "Components/AboutDialog.h"
#include "Components/HelpDialog.h"
#include "Components/SettingsDialog.h"
#include "Model/Config/Config.h"
#include "Model/Events/Event.h"

#include <QDate>
#include <QElapsedTimer>
#include <QLineEdit>
#include <QSettings>
#include <QSharedPointer>
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
		MainWindow( std::unique_ptr<Model::ModelThread> pModelThread_, QSharedPointer<Model::Config> pConfig_,
			QWidget* pParent_ = Q_NULLPTR );
		//~MainWindow() = default;

	protected:
		void closeEvent( QCloseEvent* pEvent_ ) override;
		void paintEvent( QPaintEvent* pEvent_ ) override;

	private slots:
		void onHelpAction();
		void onAboutAction();
		void onSettingsAction();
		void onTimesheetUpdated( const Model::Timesheet& timesheet_ );
		void onRefreshClicked();

	private:
		void setCurrentWeekLabel();
		void calculateTotalTime();

		Ui::MainWindowClass m_ui;
		HelpDialog m_helpDialog;
		AboutDialog m_aboutDialog;
		SettingsDialog m_settingsDialog;
		std::unique_ptr<Model::ModelThread> m_pModelThread;
		QVector<QLineEdit*> m_workDays;
		QVector<QString> m_workDaysStrings;
		QDate m_mondayDate;
		QDate m_fridayDate;
		QTime m_currentDayTotalTime;
		QTime m_totalWorkTime;
		QElapsedTimer m_currentDayTimer;
	};

} // namespace View
