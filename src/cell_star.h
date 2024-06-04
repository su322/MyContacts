#ifndef CELL_STAR_H
#define CELL_STAR_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Cell_Star;
}

class Cell_Star : public QDialog
{
    Q_OBJECT

public:
    explicit Cell_Star(QWidget *parent = nullptr);
    ~Cell_Star();

    void initPage(QString strCondition = "");

private slots:
    void on_le_search_textChanged(const QString &arg1);

    void on_btn_delete_clicked();

private:
    Ui::Cell_Star *ui;
    QStandardItemModel m_model;
};

#endif // CELL_STAR_H
