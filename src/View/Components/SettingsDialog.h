#pragma once

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
		SettingsDialog( QSharedPointer<QSettings> pSettings_, QWidget* pParent_ = Q_NULLPTR );
		~SettingsDialog() = default;

	private:
		Ui::SettingsDialog m_ui;
		QSharedPointer<QSettings> m_pSettings;
	};

} // namespace View
