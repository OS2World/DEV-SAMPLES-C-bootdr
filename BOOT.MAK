# IBM Developer's Workframe/2 Make File Creation run at 19:08:31 on 08/23/91


.SUFFIXES:

.SUFFIXES: .c

BOOT.EXE:  \
  BOOT.OBJ
   @REM @<<BOOT.@0
     /CO /PM:VIO +
     BOOT.OBJ
     BOOT.EXE
     
     
     ;
<<
   LINK386.EXE @BOOT.@0

{.}.c.obj:
   cc.exe /Ss /Kboap /Ti /Gm /C .\$*.c

!include BOOT.DEP
