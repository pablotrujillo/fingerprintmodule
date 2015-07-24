#include "fingerprint.h"

FingerPrint::FingerPrint()
{
    DeviceIsOk = false;
    hDevice = NULL;
    raw_data = NULL;
}

FingerPrint::~FingerPrint()
{
    if(hDevice != NULL)
        ftrScanCloseDevice( hDevice );
    if(raw_data != NULL)
        free(raw_data);
}

void FingerPrint::StrError( ulong nErrCode ){
   QString strError;

    switch( nErrCode )
    {
    case 0:
        strError = " ";
        break;
    case FTR_ERROR_EMPTY_FRAME:	// ERROR_EMPTY
        strError = "- Empty frame -";
        break;
    case FTR_ERROR_MOVABLE_FINGER:
       strError = "- Movable finger -";
        break;
    case FTR_ERROR_NO_FRAME:
        strError = "- No frame -";
        break;
    case FTR_ERROR_USER_CANCELED:
        strError = "- User canceled -";
        break;
    case FTR_ERROR_HARDWARE_INCOMPATIBLE:
        strError =  "- Incompatible hardware -";
        break;
    case FTR_ERROR_FIRMWARE_INCOMPATIBLE:
        strError = "- Incompatible firmware -";
        break;
    case FTR_ERROR_INVALID_AUTHORIZATION_CODE:
        strError = "- Invalid authorization code -";
        break;
    default:
        QTextStream(&strError) << "Unknown return code - " << nErrCode;
    }

    emit ShowStrError(strError);
}

bool FingerPrint::OpenDevice()
{
    QString local_error;


    hDevice = ftrScanOpenDevice();
       if( hDevice == NULL )
       {
           DeviceIsOk  = false;
           emit ShowStrError(local_error = "Failed to open device!");
       }
       else
       {
           if( !ftrScanGetImageSize( hDevice, &ImageSize ) )
               {
                   emit ShowStrError( local_error = "Failed to get Image Size!");
                   ftrScanCloseDevice( hDevice );
                   return DeviceIsOk = false;
               }
           else
               {
                   DeviceIsOk = true;
                   StrError(0);
                   raw_data = (unsigned char *)malloc(ImageSize.nImageSize );
                   memset(raw_data, 0, ImageSize.nImageSize );

           }
       }
return DeviceIsOk;
}

void FingerPrint::GetFrame(){

    unsigned long ulErr = 0;

    memset(raw_data, 0, ImageSize.nImageSize );
    if ( !ftrScanGetFrame(hDevice, raw_data, NULL) )
        ulErr = ftrScanGetLastError();
    emit draw_fp_image();
    emit StrError( ulErr );
}

int FingerPrint::getImageHeight(){return ImageSize.nHeight;}

int FingerPrint::getImageWidth(){return ImageSize.nWidth;}

int FingerPrint::getImageSize(){return ImageSize.nImageSize;}


//TODO:
//configure where to save image
//comment code.
//generate:
//deb file
//example using: qdebug, and qt test facilities.
//generate uml + dioxigen document files.
//upload to git---------> DONE
// refactor to get better understable code.
//locale  (set resources : learn the qt way).
