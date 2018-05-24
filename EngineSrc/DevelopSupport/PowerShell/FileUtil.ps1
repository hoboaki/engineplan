# 文字コード：UTF-8

# ファイルに関する便利関数群。
class FileUtil
{
    # aFrom 以下にあるファイル＆ディレクトリを aTo 以下にコピーする。
    # コピー先にファイルやディレクトリがあれば消してからコピーする。
    static [void] CopyDir([string]$aFrom, [string]$aTo)
    {
        if (Test-Path $aTo) {
            Remove-Item $aTo -Recurse
        }
        Copy-Item $aFrom -destination $aTo -recurse
    }
}

# EOF
