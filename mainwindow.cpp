#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>

#include<QtDebug>
#include "fingerprint.h"

FingerPrint *FPDevice = NULL;
FPThreadWorker *worker = NULL;

QImage FPImage;
QGraphicsPixmapItem *gFPitem = NULL;

QString title = "FtrScanAPI Demo - Smtt ";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    title.append(VERSION);
    setWindowTitle(title);

    ui->ScanButton->setDisabled(true);
    ui->SaveButton->setDisabled(true);
    ui->StopButton->setDisabled(true);
    ui->graphicsView->setHidden(true);

    FPDevice = new FingerPrint();
    connect(FPDevice,&FingerPrint::ShowStrError,this,&MainWindow::ShowMessage);
    if(FPDevice->OpenDevice())
    {        
        ui->graphicsView->setGeometry(200,10,FPDevice->getImageWidth()+2,FPDevice->getImageHeight()+2);
        scene = new QGraphicsScene(this);
        QBrush black(Qt::black);
        //QBrush white(Qt::white);
        scene->setBackgroundBrush(black);
        //scene->setForegroundBrush(white);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setHidden(false);
        ui->ScanButton->setDisabled(false);
        worker = new FPThreadWorker(FPDevice);
        FPImage = QImage(FPDevice->getRaw_data(),FPDevice->getImageWidth(),FPDevice->getImageHeight(),QImage::Format_Indexed8);
        gFPitem =scene->addPixmap(QPixmap::fromImage(FPImage));
        connect(FPDevice,&FingerPrint::draw_fp_image,this,&MainWindow::draw_image,Qt::UniqueConnection);
        //gFPitem->setVisible(false);

    }


}

MainWindow::~MainWindow()
{
    //*************************
        if(worker != NULL){
            if(worker->isRunning())
            {
                worker->do_stop();
            }

        if(worker->wait(1002))
            delete worker;
        }
    //************************
    if(gFPitem != NULL)
        delete gFPitem;
    if(FPDevice != NULL)
        delete FPDevice;
    delete ui;
}

void MainWindow::ShowStrMessage(const char * Message)
{
    QString Msg = Message;
    ShowMessage(Msg);
}


void MainWindow::ShowMessage(QString Message)
{   ui->statusBar->clearMessage();
    ui->statusBar->showMessage(Message,0);
}


void MainWindow::draw_image()
{
    //FPImage.invertPixels(QImage::InvertRgb);
    gFPitem->setPixmap(QPixmap::fromImage(FPImage.scaled(FPImage.width()/3,FPImage.height()/3,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
}


void MainWindow::on_ScanButton_clicked()
{
    if(!worker->isRunning()){        
        ui->SaveButton->setDisabled(true);
        worker->start();
        ui->StopButton->setDisabled(false);

    }
}

void MainWindow::on_StopButton_clicked()
{
    if(worker != NULL)
        {
            if(worker->isRunning())
            {
                worker->do_stop();
                ui->SaveButton->setDisabled(false);
                on_SaveButton_clicked();
            }
        }
}

void MainWindow::on_SaveButton_clicked()
{

    ui->StopButton->setDisabled(true);
    if(gFPitem->pixmap().save(fp_FILENAME)){
        ShowMessage(QString("Image Save"));}
    else
         ShowMessage(QString("Error Saving Image"));
}

/*void MainWindow::on_SaveButton_clicked()
{

    on_StopButton_clicked();
    //ui->StopButton->setDisabled(true);
    if(gFPitem->pixmap().save(fp_FILENAME)){
        ShowMessage(QString("Image Save"));}
    else
         ShowMessage(QString("Error Saving Image"));
gFPitem->setVisible(true);
}*/
