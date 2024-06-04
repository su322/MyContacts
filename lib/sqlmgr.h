#ifndef SQLMGR_H
#define SQLMGR_H
#include <QDebug>
#include <QSqlDatabase>
class SqlMgr
{
public:
    SqlMgr();
    ~SqlMgr();

    //单例模式
    static SqlMgr* instance;
    static SqlMgr* getInstance(){
        if(nullptr == instance){
            instance = new SqlMgr();
        }
        return instance;
    }

    //初始化数据库
    void init();

    //抽象相关功能
    //登录
    bool login(QString strUser,QString strPass);

    //注册用户
    //bool userRegister(QString strUser, QString strPass, QString strPass2nd);

    //获取所有联系人
    QVector<QStringList> getCts(QString strCondition = "");

    //获取所有收藏联系人 小组分类？
    QVector<QStringList> getStars(QString strCondition = "");

    //新建联系人
    void AddCts(QVector<QStringList>);

    //修改联系人
    void UpdateCts(QStringList);

    //删除联系人
    QString delCts(QString strId);

    //添加收藏
    void addStar(QString strId);

    //删除收藏
    QString delStar(QString strId);


    QVector<QStringList> executeQuery(QSqlQuery &q, const QString &strSql);
private:
    QSqlDatabase m_db;
};

#endif // SQLMGR_H
