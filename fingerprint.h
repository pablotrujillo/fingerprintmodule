#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#define VERSION "0.6"

#include <QThread>
#include <QDebug>
#include "ftrScanAPI.h"

#define fp_FILENAME "fp_example.bmp"

class FingerPrint: public QObject{
    Q_OBJECT

    FTRSCAN_IMAGE_SIZE ImageSize;
    void *hDevice;
    bool DeviceIsOk;
    unsigned char *raw_data;

    void StrError( ulong nErrCode );

public:

    FingerPrint();    
    ~FingerPrint();
    void GetFrame();
    bool OpenDevice();
    int getImageWidth();
    int getImageHeight();
    int getImageSize();
    unsigned char * getRaw_data(){ return raw_data; }

signals:
    void ShowStrError(QString Message);
    void draw_fp_image();

};

class FPThreadWorker : public QThread{
    Q_OBJECT
private:
    FingerPrint *FingerPrintObj;
    bool Stop;
public:
    explicit FPThreadWorker(FingerPrint *FPObj){ FingerPrintObj = FPObj;}
    void do_stop(){ Stop = true;}
protected:
    void run() Q_DECL_OVERRIDE {
            Stop = false;
            while( !Stop )
            {
                 usleep(1000);                 
                FingerPrintObj->GetFrame();
            }
       }
};


#endif // FINGERPRINT_H
