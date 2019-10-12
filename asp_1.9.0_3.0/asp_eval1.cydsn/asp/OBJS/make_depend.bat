@ECHO OFF
rem 引数
rem 　%1 aspのトップディレクトリ					(..)
rem 　%2 対象となるコンフィギュレーションファイル	(sample1)
rem 　%3 ターゲット名								(cy8ckit050_gcc)

@ECHO ON
..\cfg\cfg\cfg --pass 1 --kernel asp -I. -I%1/include -I%1/arch -I..  -I%1/target/%3 -I%1/arch/arm_m_gcc/common -I%1/arch/gcc --api-table %1/kernel/kernel_api.csv  --cfg1-def-table %1/kernel/kernel_def.csv  --cfg1-def-table %1/arch/arm_m_gcc/common/core_def.csv %2.cfg
arm-none-eabi-gcc -c  -mlittle-endian -mcpu=cortex-m3 -mthumb  -g -Wall -O2  -I. -I%1/include -I%1/arch -I.. -I%1/target/%3 -I%1/arch/arm_m_gcc/common -I%1/arch/gcc  -DALLFUNC  -I%1/kernel -I%1/../Generated_Source/PSoC5 cfg1_out.c
arm-none-eabi-gcc -c  -mlittle-endian -mcpu=cortex-m3 -mthumb  -g -Wall -O2  -I. -I%1/include -I%1/arch -I.. -I%1/target/%3 -I%1/arch/arm_m_gcc/common -I%1/arch/gcc -DALLFUNC  -I%1/kernel %1/arch/arm_m_gcc/common/start.S
arm-none-eabi-gcc  -mlittle-endian -mcpu=cortex-m3 -mthumb  -g -Wall -O2  -I. -I%1/include -I%1/arch -I.. -I%1/target/%3 -I%1/arch/arm_m_gcc/common -I%1/arch/gcc -nostdlib -nostdlib  -mlittle-endian  -T %1/target/%3/cy8c5xlp_rom.ld  -o cfg1_out.exe cfg1_out.o 
arm-none-eabi-nm -C cfg1_out.exe > cfg1_out.syms
arm-none-eabi-objcopy -O srec -S cfg1_out.exe cfg1_out.srec
..\cfg\cfg\cfg --pass 2 --kernel asp -I. -I%1/include -I%1/arch -I..  -I%1/target/%3 -I%1/arch/arm_m_gcc/common -T %1/target/%3/target.tf --api-table %1/kernel/kernel_api.csv  --cfg1-def-table %1/kernel/kernel_def.csv  --cfg1-def-table %1/arch/arm_m_gcc/common/core_def.csv %2.cfg

@ECHO OFF
rem バナー表示のタイムスタンプを更新 (UNIXのtouchコマンドに相当)
copy %1\syssvc\banner.c tmp.c > nul
type tmp.c > %1\syssvc\banner.c
del tmp.c

@ECHO ON
..\cfg\cfg\cfg --pass 3 --kernel asp -I. -I%1/include -I%1/arch -I.. -I%1/target/%3 -I%1/arch/arm_m_gcc/common --rom-image cfg1_out.srec --symbol-table cfg1_out.syms -T %1/target/%3/target_offset.tf --api-table %1/kernel/kernel_api.csv  --cfg1-def-table %1/kernel/kernel_def.csv  --cfg1-def-table %1/arch/arm_m_gcc/common/core_def.csv %2.cfg
