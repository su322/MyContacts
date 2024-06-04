#include "dlg_ctsau.h"
#include "ui_dlg_ctsau.h"

#include <QSqlQuery>

#include <lib/sqlmgr.h>

Dlg_CtsAU::Dlg_CtsAU(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_CtsAU)
{
    ui->setupUi(this);
}

Dlg_CtsAU::~Dlg_CtsAU()
{
    delete ui;
}

void Dlg_CtsAU::setType(int id)
{
    m_id = id;

    // 执行SQL语句获取联系人信息
    QString sql = "SELECT name, tel, email, qq, home, relation FROM contacts WHERE id = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    if (query.exec())
    {
        if (query.next())
        {
            // 从查询结果中获取图书信息
            QString name = query.value(0).toString();
            QString tel = query.value(1).toString();
            QString email = query.value(2).toString();
            QString qq = query.value(3).toString();
            QString home = query.value(4).toString();
            QString relation = query.value(5).toString();

            // 将图书信息显示到对应的控件上
            ui->le_name->setText(name);
            ui->le_tel->setText(tel);
            ui->le_email->setText(email);
            ui->le_qq->setText(qq);
            ui->le_address->setText(home);
            ui->le_relation->setText(relation);

        }
    }
}

void Dlg_CtsAU::on_btn_ok_clicked()
{
    QStringList l;
    l<<QString::number(m_id);
    l<<ui->le_name->text();
    l<<ui->le_tel->text();
    l<<ui->le_email->text();
    l<<ui->le_qq->text();
    l<<ui->le_address->text();
    l<<ui->le_relation->text();

    if(-1 != m_id)
    {
        //update
        SqlMgr::getInstance()->UpdateCts(l);
    }
    else
    {
        //add
        QVector<QStringList> vec;
        vec.push_back(l);
        SqlMgr::getInstance()->AddCts(vec);
    }
    this->hide();
}


void Dlg_CtsAU::on_btn_cancel_clicked()
{
    this->hide();
}

