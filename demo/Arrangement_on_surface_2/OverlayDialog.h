// Copyright (c) 2012  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/v5.1/Arrangement_on_surface_2/demo/Arrangement_on_surface_2/OverlayDialog.h $
// $Id: OverlayDialog.h 3003fb3 2020-06-18T13:35:40+02:00 Maxime Gimeno
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Alex Tsui <alextsui05@gmail.com>

#ifndef OVERLAY_DIALOG_H
#define OVERLAY_DIALOG_H

#include <QDialog>
#include <vector>
#include <CGAL/Object.h>

class ArrangementDemoWindow;
class QListWidgetItem;
namespace Ui { class OverlayDialog; }

class OverlayDialog : public QDialog
{
  Q_OBJECT

  public:
  typedef enum OverlayDialogRole {
    ARRANGEMENT = 32
  } OverlayDialogRole;

  OverlayDialog( ArrangementDemoWindow* parent, Qt::WindowFlags f = Qt::WindowType(0)  );

  std::vector< CGAL::Object > selectedArrangements( ) const;

public Q_SLOTS:
  void on_pickPushButton_pressed( );
  void on_unpickPushButton_pressed( );

protected:
  void restrictSelection( QListWidgetItem* item );
  void unrestrictSelection( );

  Ui::OverlayDialog* ui;
};

#endif // OVERLAY_DIALOG_H
