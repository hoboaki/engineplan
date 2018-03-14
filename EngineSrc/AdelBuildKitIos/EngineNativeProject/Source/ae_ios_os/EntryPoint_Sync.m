// 文字コード：UTF-8
#include "EntryPoint_Sync.h"

#import <QuartzCore/QuartzCore.h>

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_CATransactionFlush()
{
    [CATransaction flush];
}

// EOF
