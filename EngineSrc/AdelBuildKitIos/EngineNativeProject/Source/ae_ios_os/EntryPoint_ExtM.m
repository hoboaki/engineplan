// 文字コード：UTF-8

//------------------------------------------------------------------------------
#include <assert.h>
#include <string.h>
#include <UIKit/UIKit.h>
#include "EntryPoint_Ext.h"
#include "AeBaseUIApplicationDelegate.h"

//------------------------------------------------------------------------------
// EntryPointC.cppに定義してある関数。
//------------------------------------------------------------------------------
#define tExeFileNameLength (256)  // Unix のファイル名の最大長
#define tExeDirPathLength  (1024) // Unix のパスの最大長
static char tExeFileName[ tExeFileNameLength ];
static char tExeDirPath[ tExeDirPathLength ];

static int tLastIndexOf( const char* aStr , const char aCh )
{
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
int main( const int aArgCount , char* aArgValues[] )
{
    {// Exeのパスを解析
        // メモリリーク対策
        NSAutoreleasePool* pool=[[NSAutoreleasePool alloc] init];
        
        // Exeのパスを取得
        NSBundle* mainBundle = [NSBundle mainBundle];
        if ( mainBundle == 0 )
        {
            printf( "CrossFramework is not working as command line tool.\n" );
            printf( "Please build as cocoa application.\n" );
            return -1;
        }
        NSString* exePathString = [mainBundle executablePath];
        assert( exePathString != 0 );
        const char* exePath = [exePathString UTF8String];
        assert( exePath != 0 );
        
        // 解析をして値を代入
        const int dirLength = tLastIndexOf(exePath, '/');
        assert( 0 <= dirLength && dirLength < tExeDirPathLength );
        strncpy( tExeDirPath , exePath , tExeDirPathLength ); 
        tExeDirPath[ dirLength ] = '\0';
        strncpy( tExeFileName , &exePath[ dirLength + 1 ] , tExeFileNameLength );
        
        // リリース
        [pool release];
    }
    
    // CPPに処理を委譲
    return mainC( aArgCount , aArgValues , tExeFileName , tExeDirPath );
}

//------------------------------------------------------------------------------
int mainUI( int aArgCount , char* aArgValues[] )
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(aArgCount, aArgValues, nil, @"AeBaseUIApplicationDelegate");
    [pool release];
    return retVal;    
}

//------------------------------------------------------------------------------
void* xmainThreadEntryPoint( void* aArg )
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    xmainThreadEntryPointC( aArg );
    [pool release];
    return 0;    
}

//------------------------------------------------------------------------------
//EOF
