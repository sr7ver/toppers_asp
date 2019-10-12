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
 *  @(#) $Id: core_timer.h 2183 2011-07-23 10:29:36Z ertl-honda $
 */

/*
 *  �^�C�}�h���C�o�iSYSTIC�p�j
 */

#ifndef TOPPERS_CORE_TIMER_H
#define TOPPERS_CORE_TIMER_H

#include <sil.h>

/*
 *  �^�C�}�����݃n���h���o�^�̂��߂̒萔
 */
#define INHNO_TIMER     IRQNO_SYSTICK /* �����݃n���h���ԍ� */
#define INTNO_TIMER     IRQNO_SYSTICK /* �����ݔԍ� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �^�C�}�l�̓����\���̌^
 */
typedef uint32_t    CLOCK;

/*
 *  �^�C�}�l�̓����\���ƃ~���b�E�ʕb�P�ʂƂ̕ϊ�
 *
 */
#define TO_CLOCK(nume, deno)    ((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define TO_USEC(clock)          (((SYSUTM) clock) * 1000U / TIMER_CLOCK)

/*
 *  �ݒ�ł���ő�̃^�C�}�����i�P�ʂ͓����\���j
 */
#define MAX_CLOCK    ((CLOCK) 0x00ffffffU)

/*
 *  �^�C�}�̋N������
 *
 *  �^�C�}�����������C�����I�ȃ^�C�}�����ݗv���𔭐�������D
 */
extern void target_timer_initialize(intptr_t exinf);

/*
 *  �^�C�}�̒�~����
 *
 *  �^�C�}�̓�����~������D
 */
extern void target_timer_terminate(intptr_t exinf);

/*
 *  �^�C�}�̌��ݒl�̓Ǐo��
 */
Inline CLOCK
target_timer_get_current(void)
{
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - sil_rew_mem((void*)SYSTIC_CURRENT_VALUE));
}

/*
 *  �^�C�}�����ݗv���̃`�F�b�N
 */
Inline bool_t
target_timer_probe_int(void)
{
	return((sil_rew_mem((void*)SYSTIC_CONTROL_STATUS) & SYSTIC_COUNTFLAG) == SYSTIC_COUNTFLAG);
}

/*
 *  �^�C�}�����݃n���h��
 */
extern void target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CORE_TIMER_H */