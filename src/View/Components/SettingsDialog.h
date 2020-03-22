#pragma once

#include "ui_SettingsDialog.h"

#include <QDialog>
#include <QWidget>

namespace View
{
	class SettingsDialog : public QDialog
	{
		Q_OBJECT

	public:
		SettingsDialog( QWidget* pParent_ = Q_NULLPTR );
		~SettingsDialog() = default;

	private:
		Ui::SettingsDialog m_ui;
	};

} // namespace View
