#pragma once

#include "Model/Config/Config.h"
#include "ui_SettingsDialog.h"

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>
#include <QWidget>
namespace View
{
	class SettingsDialog : public QDialog
	{
		Q_OBJECT

	public:
		SettingsDialog( QSharedPointer<Model::Config> pConfig_, QWidget* pParent_ = Q_NULLPTR );
		~SettingsDialog() = default;

	private:
		Ui::SettingsDialog m_ui;
		QSharedPointer<Model::Config> m_pConfig;

	private slots:
		void onLogonChanged( const QCheckBox& checkbox_ );
		void onLogoffChanged( const QCheckBox& checkbox_ );
		void onLockedChanged( const QCheckBox& checkbox_ );
		void onUnlockedChanged( const QCheckBox& checkbox_ );
	};

} // namespace View
