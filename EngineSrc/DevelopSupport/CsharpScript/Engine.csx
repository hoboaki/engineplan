// 文字コード：UTF-8
#load "./FileUtil.csx"

// 本プロジェクト環境に関する値を提供するクラス。
static class Engine
{
    // EngineSrc ルートフォルダの絶対パスを取得。
    // 末尾に区切り文字は入っていないパスを返す。
    static internal string SrcRoot()
    {
        return FileUtil.CurrentScriptFile().Directory.Parent.Parent.FullName;
    }
}
// EOF
