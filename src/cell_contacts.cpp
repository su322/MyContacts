#include "cell_contacts.h"
#include "dlg_ctsau.h"
#include "ui_cell_contacts.h"

#include <lib/sqlmgr.h>

#include <QMessageBox>

Cell_Contacts::Cell_Contacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cell_Contacts)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

Cell_Contacts::~Cell_Contacts()
{
    delete ui;
}

void Cell_Contacts::initPage(QString strCondition)
{
    //获取所有联系人
    auto l = SqlMgr::getInstance()->getCts(strCondition);
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

void Cell_Contacts::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where name like '%%1%' or tel like '%%1%'").arg(arg1);
    initPage(strCond);
}


void Cell_Contacts::on_btn_add_clicked()
{
    Dlg_CtsAU dlg;
    dlg.exec();
    initPage();
}


void Cell_Contacts::on_btn_update_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"信息","无选中联系人");
    }
    else
    {
        auto id = m_model.item(r,0)->text();
        Dlg_CtsAU dlg;
        dlg.setType(id.toInt());
        int ret = dlg.exec();
        //qDebug()<<ret;              ret=0?
        //QMessageBox::information(nullptr,"信息",!ret?"修改成功":"修改失败");
        if(!ret)
        {
            initPage();
        }
    }
}


void Cell_Contacts::on_btn_delete_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"信息","无选中联系人");
    }
    else
    {
        auto id = m_model.item(r,0)->text();
        auto str = SqlMgr::getInstance()->delCts(id);
        QMessageBox::information(nullptr,"信息",str.isEmpty()?"删除成功":str);
        initPage();
    }
}


void Cell_Contacts::on_btn_star_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"信息","无选中联系人");
    }
    else
    {
        auto id = m_model.item(r,0)->text();
        SqlMgr::getInstance()->addStar(id);
        //QMessageBox::information(nullptr,"信息",str.isEmpty()?"收藏成功":str);
        initPage();
    }
}

