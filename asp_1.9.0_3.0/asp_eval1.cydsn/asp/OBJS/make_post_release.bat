@ECHO OFF
rem 引数
rem 　%1 aspのトップディレクトリ					(..)
rem 　%2 対象となるコンフィギュレーションファイル	(sample1)
rem 　%3 ターゲット名								(cy8ckit050_gcc)
rem   %4 PSoC Creatorプロジェクト名					(asp_eval1)

@ECHO ON
copy ..\..\CortexM3\ARM_GCC_441\Release\%4.elf > NULL
arm-none-eabi-nm -C %4.elf > %4.syms
arm-none-eabi-objcopy -O srec -S %4.elf %4.srec
..\cfg\cfg\cfg --pass 3 --kernel asp -I. -I%1/include -I%1/arch -I.. -I%1/target/%3 -I%1/arch/arm_m_gcc/common --rom-image %4.srec --symbol-table %4.syms -T %1/target/%3/target_check.tf --api-table %1/kernel/kernel_api.csv  --cfg1-def-table %1/kernel/kernel_def.csv  --cfg1-def-table %1/arch/arm_m_gcc/common/core_def.csv %2.cfg
