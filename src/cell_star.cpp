#include "cell_star.h"
#include "ui_cell_star.h"

#include <lib/sqlmgr.h>

#include <QMessageBox>

Cell_Star::Cell_Star(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cell_Star)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

Cell_Star::~Cell_Star()
{
    delete ui;
}

void Cell_Star::initPage(QString strCondition)
{
    //获取所有联系人
    auto l = SqlMgr::getInstance()->getStars(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"联系人ID","姓名","电话","邮箱","QQ","住址","关系"});
    for(int i=0;i<l.size();i++)
    {
        QList<QStandardItem*> items;
        for(int j=0;j<l[i].size();j++)
        {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}

void Cell_Star::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where name like '%%1%' or tel like '%%1%'").arg(arg1);
    initPage(strCond);
}

void Cell_Star::on_btn_delete_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"信息","无选中联系人");
    }
    else
    {
        auto id = m_model.item(r,0)->text();
        auto str = SqlMgr::getInstance()->delStar(id);
        QMessageBox::information(nullptr,"信息",str.isEmpty()?"删除成功":str);
        initPage();
    }
}

