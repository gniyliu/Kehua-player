copy "c:\program files (x86)\Windows Media Player\wmplayer.exe" ..\POWERCUBE500_Client_Source\ /y
copy mscomm*.* %windir%\system32\ /y
Regsvr32 %windir%\system32\mscomm32.ocx /s
reg add "HKCR\Licenses\4250E830-6AC2-11cf-8ADB-00AA00C00905" /v "" /d "kjljvjjjoquqmjjjvpqqkqmqykypoqjquoun" /f
 (x86)