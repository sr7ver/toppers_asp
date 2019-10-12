@ECHO OFF
IF "%1" == "" GOTO ERROR
IF %1 == 2.2 path C:\Program Files\Cypress\PSoC Creator\2.2\PSoC Creator\import\gnu_cs\arm\4.4.1\bin;%PATH%
IF %1 == 3.0 path C:\Program Files\Cypress\PSoC Creator\3.0\PSoC Creator\import\gnu_cs\arm\4.7.3\bin;%PATH%
PATH
GOTO FIN

:ERROR
ECHO ***** パラメータがありません *****
ECHO 使用方法：set_path.bat ver
ECHO ver : PSoc Creatorのバージョン番号(2.2 or 3.0)
:FIN
