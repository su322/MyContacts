#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include "cell_contacts.h"
#include "cell_star.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Cell_Main; }
QT_END_NAMESPACE

class Cell_Main : public QMainWindow
{
    Q_OBJECT

public:
    Cell_Main(QWidget *parent = nullptr);
    ~Cell_Main();

    void initPage();
    void dealMenu();

private:
    Ui::Cell_Main *ui;
    Cell_Contacts *m_ctsPage;
    Cell_Star *m_starPage;
    //设置页面？
};
#endif // CELL_MAIN_H
