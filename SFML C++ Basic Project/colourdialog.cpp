//#include <windows.h>
//
//int main() {
//    CHOOSECOLOR cc;                 // common dialog box structure 
//    static COLORREF acrCustClr[16]; // array of custom colors 
//    HWND hwnd;                      // owner window
//    HBRUSH hbrush;                  // brush handle
//    static DWORD rgbCurrent;        // initial color selection
//
//    // Initialize CHOOSECOLOR 
//    ZeroMemory(&cc, sizeof(cc));
//    cc.lStructSize = sizeof(cc);
//    cc.hwndOwner = hwnd;
//    cc.lpCustColors = (LPDWORD)acrCustClr;
//    cc.rgbResult = rgbCurrent;
//    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
//
//    if (ChooseColor(&cc) == TRUE)
//    {
//        hbrush = CreateSolidBrush(cc.rgbResult);
//        rgbCurrent = cc.rgbResult;
//    }
//}