#include "dlg_login.h"

#include "ui_dlg_login.h"

#include <QMessageBox>

#include <lib/sqlmgr.h>

Dlg_Login::Dlg_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Login)
{
    ui->setupUi(this);
    QWidget::setTabOrder(ui->le_username, ui->le_userpass);
    QWidget::setTabOrder(ui->le_userpass, ui->btn_login);
    QWidget::setTabOrder(ui->btn_login, ui->btn_exit);

}

Dlg_Login::~Dlg_Login()
{
    delete ui;
}

void Dlg_Login::on_btn_exit_clicked()
{
    setResult(0);
    hide();
}


//void Dlg_Login::on_btn_reg_clicked()//以前的注册按钮
//{
//    Dlg_Reg * dlg_reg = new Dlg_Reg(this);
//    dlg_reg->setWindowModality(Qt::ApplicationModal);//模态窗口，上一窗口不可操作
//    dlg_reg->show();
//}


void Dlg_Login::on_btn_login_clicked()
{
    auto ret = SqlMgr::getInstance()->login(ui->le_username->text(),ui->le_userpass->text());
    if(ret)
    {
        setResult(1);
        hide();
    }else
    {
        QMessageBox::information(nullptr,"信息","用户名或密码错误");
    }
}


void Dlg_Login::on_le_userpass_textChanged(const QString &arg1)
{
    ui->le_userpass->setEchoMode(QLineEdit::Password);
}

