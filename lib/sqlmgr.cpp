#include "sqlmgr.h"
#include "qmessagebox.h"

#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

SqlMgr* SqlMgr::instance = nullptr;

SqlMgr::SqlMgr()
{

}

SqlMgr::~SqlMgr()
{

}

void SqlMgr::init()//改数据库
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(""); // 设置数据库主机地址，根据实际情况修改
    m_db.setPort(5432); // 设置数据库端口号，根据实际情况修改
    m_db.setDatabaseName("postgres"); // 设置数据库名称，根据实际情况修改
    m_db.setUserName("gaussdb"); // 设置数据库用户名，根据实际情况修改
    m_db.setPassword(""); // 设置数据库密码，根据实际情况修改

    if (!m_db.open()) {
        qDebug() << "Failed to connect to database:";
        qDebug() << m_db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }
}

bool SqlMgr::login(QString strUser, QString strPass)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select id from \"user\" where username='%1' and userpass ='%2'").arg(strUser).arg(strPass);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }else
    {
        ret = q.next();
    }
    return ret;
}

//bool SqlMgr::userRegister(QString strUser, QString strPass, QString strPass2nd)
//{
//    //用户是否已存在？检查是否有相同用户名
//    //用户名长度、密码长度超出限制长度？
//    //确认密码是否成功？
//}

QVector<QStringList> SqlMgr::getCts(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("SELECT * FROM contacts %1").arg(strCondition);
    return executeQuery(q, strSql);
}

QVector<QStringList> SqlMgr::getStars(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("SELECT * FROM stars %1").arg(strCondition);
    return executeQuery(q, strSql);
}

QVector<QStringList> SqlMgr::executeQuery(QSqlQuery& q, const QString& strSql)
{
    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while (q.next())
        {
            l.clear();
            for (int i = 0; i < iCols; i++)
            {
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}


void SqlMgr::AddCts(QVector<QStringList> vec)
{
    if (vec.isEmpty())
    {
        return;
    }

    QStringList ldata = vec[0];
    QSqlQuery q(m_db);
    QString strSql = QString("INSERT INTO contacts (name, tel, email, qq, home, relation) "
                             "VALUES ('%1', '%2', '%3', '%4', '%5', '%6')")
                         .arg(ldata[1])
                         .arg(ldata[2])
                         .arg(ldata[3])
                         .arg(ldata[4])
                         .arg(ldata[5])
                         .arg(ldata[6]);
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
}

void SqlMgr::UpdateCts(QStringList ldata)
{
    QSqlQuery q(m_db);

    // 更新 contacts 表的内容
    QString strSqlContacts = QString("UPDATE contacts "
                                     "SET name = '%1', tel = '%2', email = '%3', qq = '%4', home = '%5', relation = '%6' "
                                     "WHERE id = %7 RETURNING id")
                                 .arg(ldata[1])
                                 .arg(ldata[2])
                                 .arg(ldata[3])
                                 .arg(ldata[4])
                                 .arg(ldata[5])
                                 .arg(ldata[6])
                                 .arg(ldata[0]);
    bool retContacts = q.exec(strSqlContacts);
    if (!retContacts) {
        qDebug() << q.lastError().text();
        return;
    }

    // 如果更新成功，获取更新后的 id
    if (q.next()) {
        int id = q.value(0).toInt();

        // 更新 stars 表的内容
        QString strSqlUpdateStars = QString("UPDATE stars "
                                            "SET name = '%1', tel = '%2', email = '%3', qq = '%4', home = '%5', relation = '%6' "
                                            "WHERE id = %7")
                                        .arg(ldata[1])
                                        .arg(ldata[2])
                                        .arg(ldata[3])
                                        .arg(ldata[4])
                                        .arg(ldata[5])
                                        .arg(ldata[6])
                                        .arg(id);
        bool retUpdateStars = q.exec(strSqlUpdateStars);
        if (!retUpdateStars) {
            qDebug() << q.lastError().text();
        }
    }
}

QString SqlMgr::delCts(QString strId)
{
    QString strRet;
    QSqlQuery q(m_db);

    // 删除联系人
    QString strSql = QString("DELETE FROM contacts WHERE id = %1").arg(strId);
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
        strRet = "删除失败，请检查";
        return strRet;
    }

    // 设置序列的当前值为当前联系人表中最大的 ID 值
    QString strSqlSetval = "SELECT setval('id_seq', (SELECT max(id) FROM contacts))";
    ret = q.exec(strSqlSetval);
    if (!ret)
    {
        qDebug() << q.lastError().text();
        strRet = "设置序列当前值失败，请检查";
        return strRet;
    }

    return strRet;
}

void SqlMgr::addStar(QString strId)
{
    QString sql = "INSERT INTO stars SELECT * FROM contacts WHERE id = :id";
    // 执行SQL语句并将联系人写入stars表
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", strId);
    if (query.exec()) {
        QMessageBox::information(nullptr,"信息","收藏成功");// 写入成功
    } else {
        QMessageBox::information(nullptr,"信息","重复收藏");// 写入失败
    }
}

QString SqlMgr::delStar(QString strId)
{
    QString strRet;
    QSqlQuery q(m_db);

    // 删除 stars 表中的行
    QString strSql = QString("DELETE FROM stars WHERE id = %1").arg(strId);
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
        strRet = "删除失败，请检查";
        return strRet;
    }

    // 设置序列的当前值为当前 stars 表中最大的 ID 值
    QString strSqlSetval = "SELECT setval('id_seq', (SELECT max(id) FROM stars))";
    ret = q.exec(strSqlSetval);
    if (!ret)
    {
        qDebug() << q.lastError().text();
        strRet = "设置序列当前值失败，请检查";
        return strRet;
    }

    return strRet;
}
