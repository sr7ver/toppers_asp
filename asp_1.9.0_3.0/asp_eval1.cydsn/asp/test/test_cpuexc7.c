/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_cpuexc7.c 2534 2013-10-13 12:27:37Z ertl-hiro $
 */

/* 
 *		CPU��O�����̃e�X�g(7)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  �����ݗD��x�}�X�N��TIPM_ENAALL�C�f�B�X�p�b�`�֎~��ԁC�^�X�N��O��
 *  ��ԂŔ�������CPU��O�ɂ�����V�X�e����Ԃ̃e�X�g�D�^�X�N��O�ɂ�
 *  �胊�J�o���[�ł��邱�Ƃ��e�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *  ��������C�����ݗD��x�}�X�N��TIPM_ENAALL�C�f�B�X�p�b�`�֎~��ԁC�^
 *  �X�N��O����ԂŔ�������CPU��O�ɂ����āC
 *
 *	(A) CPU��O�n���h�����s�J�n����CPU���b�N�t���O���ω����Ȃ�����
 *	(B) CPU��O�n���h�����s�J�n���Ɋ����ݗD��x�}�X�N���ω����Ȃ�����
 *		�ICPU��O�n���h�����Ŋ����ݗD��x�}�X�N��ǂ߂Ȃ����߁C�e�X�g��
 *		���Ȃ��D
 *	(C) CPU��O�n���h�����s�J�n���Ƀf�B�X�p�b�`�֎~�t���O���ω����Ȃ�����
 *	(D) CPU��O�n���h�����s�J�n���Ƀ^�X�N��O�����֎~�t���O���ω����Ȃ�����
 *	(E) CPU��O�n���h�����^�[������CPU���b�N�t���O�����ɖ߂邱��
 *	(F) CPU��O�n���h�����^�[�����Ɋ����ݗD��x�}�X�N�����ɖ߂邱��
 *	(G) CPU��O�n���h�����^�[�����Ƀf�B�X�p�b�`�֎~�t���O���ω����Ȃ�����
 *	(H) CPU��O�n���h�����^�[�����Ƀ^�X�N��O�����֎~�t���O���ω����Ȃ�����
 *	(I) xsns_xpn��false��Ԃ�����
 *	(J) xsns_dpn��true��Ԃ�����
 *	(L) �^�X�N��O�ɂ�郊�J�o���[���ł��邱��
 *
 * �y�g�p���\�[�X�z
 *
 *	TASK1: TA_ACT�C���D��x�C�^�X�N��O�������[�`���o�^
 *	CPUEXC1: TA_NULL
 *
 * �y�e�X�g�V�[�P���X�z
 *
 *	== TASK1�i���D��x�C1��ځj==
 *	1:	��Ԃ̃`�F�b�N
 *		dis_dsp()
 *		ena_tex()
 *	2:	��Ԃ̃`�F�b�N
 *		RAISE_CPU_EXCEPTION
 *	== CPUEXC1 ==
 *	3:	��Ԃ̃`�F�b�N				... (A),(C),(D)
 *		xsns_xpn() == false			... (I)
 *		xsns_dpn() == true			... (J)
 *	4:	iras_tex(TASK1, 1U)
 *		iloc_cpu()
 *		���^�[��
 *	== TASK1�̃^�X�N��O�������[�`�� ==
 *	5:	��Ԃ̃`�F�b�N				... (E),(F),(G),(H)
 *	6:	act_tsk(TASK1)				... (L)
 *	7:	ext_tsk()					... (L)
 *	== TASK1�i���D��x�C2��ځj==
 *	8:	��Ԃ̃`�F�b�N				... (L)
 *	9:	�e�X�g�I��
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_cpuexc.h"

int_t	task1_count = 0;

void
task1(intptr_t exinf)
{
	ER		ercd;

	switch (++task1_count) {
	case 1:
		test_start(__FILE__);

		check_point(1);
		check_state(false, false, TIPM_ENAALL, false, false, true);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);
		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_point(2);
		check_state(false, false, TIPM_ENAALL, true, true, false);
		RAISE_CPU_EXCEPTION;

		check_point(0);
		break;

	case 2:
		check_point(8);
		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_finish(9);
		break;

	default:
		check_point(0);
		break;
	}
}

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER		ercd;

	check_point(5);
	check_state(false, false, TIPM_ENAALL, true, true, true);

	check_point(6);
	ercd = act_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	check_point(0);
}

void
alarm1_handler(intptr_t exinf)
{
	check_point(0);
}

void
cpuexc_handler(void *p_excinf)
{
	ER		ercd;

	check_point(3);
	check_state_i(true, false, true, true, false);
	check_assert(xsns_xpn(p_excinf) == false);
	check_assert(xsns_dpn(p_excinf) == true);

	check_point(4);
	ercd = iras_tex(TASK1, 1U);
	check_ercd(ercd, E_OK);
	ercd = iloc_cpu();
	check_ercd(ercd, E_OK);
}