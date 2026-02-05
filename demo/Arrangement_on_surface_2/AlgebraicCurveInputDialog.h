// Copyright (c) 2020 Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/v6.1/Arrangement_on_surface_2/demo/Arrangement_on_surface_2/AlgebraicCurveInputDialog.h $
// $Id: demo/Arrangement_on_surface_2/AlgebraicCurveInputDialog.h b26b07a1242 $
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial

#ifndef ALGEBRAICCURVEINPUTDIALOG_H
#define ALGEBRAICCURVEINPUTDIALOG_H

#include <QDialog>

namespace Ui
{
class AlgebraicCurveInputDialog;
}

class AlgebraicCurveInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgebraicCurveInputDialog(QWidget *parent = nullptr);
    ~AlgebraicCurveInputDialog();
    std::string getLineEditText();
    Ui::AlgebraicCurveInputDialog* getUi(){return this->ui;}

private:
    Ui::AlgebraicCurveInputDialog *ui;
};

#endif // ALGEBRAICCURVEINPUTDIALOG_H
