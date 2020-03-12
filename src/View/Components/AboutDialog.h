#pragma once

#include "ui_AboutDialog.h"

#include <QDialog>
#include <QWidget>

namespace View
{
	class AboutDialog : public QDialog
	{
		Q_OBJECT

	public:
		AboutDialog( QWidget* pParent_ = Q_NULLPTR );
		~AboutDialog() = default;

	private:
		Ui::AboutDialog m_ui;
	};
} // namespace View
