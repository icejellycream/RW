set "projectpath=%cd%"
cd ../
set "preProjectpath=%cd%"
cd %projectpath%
set "SignFullPath=%preProjectpath%/X64/DEBUG/DriverLoader.sys.vmp"

set "SignPath=%preProjectpath%\X64\DEBUG\DriverLoader.vmp.sys"

"D:\VMProtect Ultimate\VMProtect_Con.exe" %SignFullPath%

set "d=%date:~0,10%"
date 2013/8/15
"D:\DSignTool\CSignTool.exe" sign /r landong /f %SignPath% /ac
date %d%


copy %SignPath% "F:\nginx-1.13.12\html\1.sys"
