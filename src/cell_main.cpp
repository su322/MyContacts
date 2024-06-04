#include "cell_main.h"
#include "ui_cell_main.h"

Cell_Main::Cell_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_Main)
    , m_ctsPage(nullptr)
    , m_starPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

Cell_Main::~Cell_Main()
{
    delete ui;
}

void Cell_Main::initPage()
{
    m_ctsPage = new Cell_Contacts(this);
    m_starPage = new Cell_Star(this);
    ui->stackedWidget->addWidget(m_ctsPage);
    ui->stackedWidget->addWidget(m_starPage);
    ui->stackedWidget->setCurrentIndex(0);

    auto l = ui->tool->children();
    for(auto it:l)
    {
        if(it->objectName().contains("btn"))
        {
            connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&Cell_Main::dealMenu);
        }
    }
    m_ctsPage->initPage();
}

void Cell_Main::dealMenu()
{
    auto str = sender()->objectName();
    do
    {
        if("btn_cts" == str)
        {
            m_ctsPage->initPage();
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }

        if("btn_star" == str)
        {
            m_starPage->initPage();
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }

    }while(false);
}
