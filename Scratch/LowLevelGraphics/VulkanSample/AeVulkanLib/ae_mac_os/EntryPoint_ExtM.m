// 文字コード：UTF-8

#include <assert.h>
#include <string.h>
#include <Cocoa/Cocoa.h>

//------------------------------------------------------------------------------
// EntryPointC.cppに定義してある関数。
extern int mainC(int aArgCount, const char* aArgValues[], const char* aExeFileName ,const char* aExeDirPath);

//------------------------------------------------------------------------------
#define tExeFileNameLength (256)  // Unix のファイル名の最大長
#define tExeDirPathLength (1024) // Unix のパスの最大長
static char tExeFileName[tExeFileNameLength];
static char tExeDirPath[tExeDirPathLength];

static int tLastIndexOf(const char* aStr, const char aCh) {
    int result = -1;
    int i = 0;
    for ( i = 0; aStr[i] != '\0'; ++i )
    {
        if ( aStr[i] == aCh )
        {
            result = i;
        }
    }
    return result;
}

//------------------------------------------------------------------------------
int main( const int aArgCount , const char* aArgValues[]) {
    // メモリリーク対策で autorelease を有効化
    @autoreleasepool {
        {// Exeのパスを解析
            // Exeのパスを取得
            NSBundle* mainBundle = [NSBundle mainBundle];
            if (mainBundle == 0) {
                printf("CrossFramework is not working as command line tool.\n");
                printf("Please build as cocoa application.\n");
                return -1;
            }
            NSString* exePathString = [mainBundle executablePath];
            assert(exePathString != 0);
            const char* exePath = [exePathString UTF8String];
            assert(exePath != 0);

            // 解析をして値を代入
            const int dirLength = tLastIndexOf(exePath, '/');
            assert(0 <= dirLength && dirLength < tExeDirPathLength);
            strncpy(tExeDirPath, exePath, tExeDirPathLength);
            tExeDirPath[dirLength] = '\0';
            strncpy(tExeFileName, &exePath[dirLength + 1], tExeFileNameLength);
        }

        // CPPに処理を委譲
        const int result = mainC(aArgCount, aArgValues, tExeFileName, tExeDirPath);

        // 終了
        return result;
    }
}

//EOF
