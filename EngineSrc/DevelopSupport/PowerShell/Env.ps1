# 文字コード：UTF-8

# 環境に関する値を提供するクラス。
class Env
{
    # EngineSrc ルートフォルダの絶対パスを取得。
    # 末尾にスラッシュは無い。
    [string] EngineSrcRoot()
    {
        return "${PSScriptRoot}/../.."
    }
}
$global:Env = New-Object Env

# EOF
