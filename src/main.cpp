#include "cell_main.h"
#include "lib/sqlmgr.h"
#include "src/dlg_login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SqlMgr::getInstance()->init();

    Dlg_Login dlg;
    int ret = dlg.exec();

    if(1 == ret)//登录成功
    {
        Cell_Main m;
        m.show();
        return a.exec();
    }

    if(0 == ret)//退出
    {
        exit(0);
        return 0;
    }
    return 0;
}
