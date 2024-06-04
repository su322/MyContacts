#ifndef DLG_CTSAU_H
#define DLG_CTSAU_H

#include <QDialog>

namespace Ui {
class Dlg_CtsAU;
}

class Dlg_CtsAU : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_CtsAU(QWidget *parent = nullptr);
    ~Dlg_CtsAU();

    void setType(int l);

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Dlg_CtsAU *ui;
    int m_id = -1;

};

#endif // DLG_CTSAU_H
