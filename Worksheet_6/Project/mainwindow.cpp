#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,
        &QPushButton::released,
        this,
        &MainWindow::handleButton); 

    connect( this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );

    partList = new ModelPartList("PartsList", this);
    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart* childItem = new ModelPart({ name, visible });


        rootItem->appendChild(childItem);


        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });


            childItem->appendChild(childChildItem);
        }
    }
}

void MainWindow::handleButton() {
    emit statusUpdateMessage ( QString ("Add button was clicked"), 0);
}

MainWindow::~MainWindow()
{
    
    delete ui;
}
