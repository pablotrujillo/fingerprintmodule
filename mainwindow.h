#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    

private slots:
    void on_ScanButton_clicked();
    void on_SaveButton_clicked();

    void on_StopButton_clicked();

public slots:
    void ShowMessage(QString Message);
    void ShowStrMessage(const char * Message);
    void draw_image();
private:
    void ShowStrError( ulong nErrCode );
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};


#endif // MAINWINDOW_H
