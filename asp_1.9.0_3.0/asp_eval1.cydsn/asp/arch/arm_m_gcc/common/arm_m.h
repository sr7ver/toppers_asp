/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: arm_m.h 2202 2011-07-26 13:27:11Z ertl-honda $
 */

/*
 *  ARMVx-M�̃n�[�h�E�F�A�����̒�`
 */

#ifndef ARM_M_H
#define ARM_M_H

/*
 *  EPSR��T�r�b�g
 */
#define EPSR_T   0x01000000

/*
 * IPSR�� ISR NUMBER
 */
#define IPSR_ISR_NUMBER 0x1ff

/*
 *  ��O�E�����ݔ������ɃX�^�b�N��ɐς܂��ۑ��̈�̃T�C�Y
 *  �{�J�[�l���ł͗�O�t���[���ƌĂ�
 */
#define EXC_FRAME_SIZE         (8*4)

/*
 *  ��O�E�����ݔ�������LR�ɐݒ肳���EXC_RETURN�̒l
 */
#define EXC_RETURN_HANDLER      0x0
#define EXC_RETURN_THREAD       0x8
#define EXC_RETURN_MSP          0x0
#define EXC_RETURN_PSP          0x4

/*
 *  CONTROL���W�X�^
 */
#define CONTROL_PSP            0x02
#define CONTROL_MSP            0x00

/*
 *  ��O�ԍ�
 */
#define EXCNO_NMI         2
#define EXCNO_HARD        3
#define EXCNO_MPU         4
#define EXCNO_BUS         5
#define EXCNO_USAGE       6
#define EXCNO_SVCALL     11          
#define EXCNO_DEBUG      12
#define EXCNO_PENDSV     14

/*
 *  ��O�ԍ��̍ŏ��l�ƍő�l
 */
#define TMIN_EXCNO   2
#define TMAX_EXCNO  14

/*
 *  �����ݔԍ�
 */
#define IRQNO_SYSTICK    15

/*
 *  �����ݔԍ��̍ŏ��l
 */
#define TMIN_INTNO       15

/*
 *  ��O�t���[���̃I�t�Z�b�g
 */
#define P_EXCINF_OFFSET_EXC_RETURN  0x00
#define P_EXCINF_OFFSET_BASEPRI     0x01
#define P_EXCINF_OFFSET_XPSR        0x09
#define P_EXCINF_OFFSET_PC          0x08

/*
 *  NVIC�֘A
 */

/*
 *  �R���g���[�����W�X�^
 */
#define NVIC_INT_CTRL       0xe000ed04

#define NVIC_PENDSVSET      0x10000000

/*
 *  �V�X�e���n���h���[�R���g���[�����W�X�^
 */
#define NVIC_SYS_HND_CTRL   0xE000ED24

/*
 *  �e��O�̋��r�b�g
 */
#define NVIC_SYS_HND_CTRL_USAGE 0x00040000
#define NVIC_SYS_HND_CTRL_BUS   0x00020000
#define NVIC_SYS_HND_CTRL_MEM   0x00010000

/*
 *  �D��x�ݒ背�W�X�^
 */
#define NVIC_SYS_PRI1       0xE000ED18  // Sys. Handlers 4 to 7 Priority
#define NVIC_SYS_PRI2       0xE000ED1C  // Sys. Handlers 8 to 11 Priority
#define NVIC_SYS_PRI3       0xE000ED20  // Sys. Handlers 12 to 15 Priority
#define NVIC_PRI0           0xE000E400  // IRQ 0 to 3 Priority Register

/*
 *  �����݋����W�X�^
 */
#define NVIC_SETENA0        0xE000E100  // IRQ 0 to 31 Set Enable Register

/*
 *  �����݋֎~���W�X�^
 */
#define NVIC_CLRENA0        0xE000E180  // IRQ 0 to 31 Set Disable Register

/*
 *  �����݃Z�b�g�y���f�B���O���W�X�^
 */
#define NVIC_ISER0          0xE000E200  // IRQ 0 to 31 Set-Pending Register

/*
 *  �����݃N���A�y���f�B���O���W�X�^
 */
#define NVIC_ICER0          0xE000E280  // IRQ 0 to 31 Clear-Pending Register

/*
 *  �x�N�^�e�[�u���I�t�Z�b�g���W�X�^
 */
#define NVIC_VECTTBL        0xE000ED08


/*
 *  SYSTIC�֘A���W�X�^
 */
#define SYSTIC_CONTROL_STATUS 0xE000E010
#define SYSTIC_RELOAD_VALUE   0xE000E014
#define SYSTIC_CURRENT_VALUE  0xE000E018
#define SYSTIC_CALIBRATION    0xE000E01C

#define SYSTIC_ENABLE    0x01
#define SYSTIC_TICINT    0x02
#define SYSTIC_CLKSOURCE 0x04
#define SYSTIC_COUNTFLAG 0x10000

#define SYSTIC_SKEW      0x40000000
#define SYSTIC_NOREF     0x80000000
#define SYSTIC_TENMS     0x00ffffff

#endif  /* ARM_M_H */