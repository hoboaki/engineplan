// 文字コード：UTF-8

// 環境に関する情報を提供するクラス。
// 名前衝突を避けるために Environment ではなく Env にした。
static class Env
{
    /// MacOS 環境か。
    internal static bool IsMacOs 
    {
        get
        {
            switch (Environment.OSVersion.Platform)
            {
                case PlatformID.MacOSX:
                case PlatformID.Unix: // mono 環境だと UNIX と返す。
                    return true;
                default:
                    return false;
            }
        }
    }
}

// EOF
