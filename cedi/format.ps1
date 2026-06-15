
Get-ChildItem src -Recurse -Include *.c,*.h -File |
    ForEach-Object {
        &clang-format -i $_.FullName --style=WebKit 
    }
