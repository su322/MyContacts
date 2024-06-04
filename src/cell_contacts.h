#ifndef CELL_CONTACTS_H
#define CELL_CONTACTS_H

#include "src/dlg_ctsau.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Cell_Contacts;
}

class Cell_Contacts : public QDialog
{
    Q_OBJECT

public:
    explicit Cell_Contacts(QWidget *parent = nullptr);
    ~Cell_Contacts();

    void initPage(QString strCondition = "");

private slots:
    void on_le_search_textChanged(const QString &arg1);

    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_delete_clicked();

    void on_btn_star_clicked();

private:
    Ui::Cell_Contacts *ui;
    QStandardItemModel m_model;
    Dlg_CtsAU au;
};

#endif // CELL_CONTACTS_H
