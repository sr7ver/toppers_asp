/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_utm1.c 2305 2012-01-29 11:51:08Z ertl-hiro $
 */

/*
 *		get_utm�Ɋւ���e�X�g(1)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  ���\�]���p�V�X�e���������t�s���邱�Ƃ��Ȃ����Ƃ��e�X�g����D
 *
 * �y�e�X�g�̓��e�z
 *
 *  ���C���^�X�N�ł́C���\�]���p�V�X�e���������J��Ԃ��擾���C��������
 *  �����Ȃ�Ȃ������`�F�b�N����D����ƕ��s���āC�����n���h����1�~���b
 *  �����Ŏ��s���C���̒��ł����\�]���p�V�X�e���������擾���āC��������
 *  �����Ȃ�Ȃ������`�F�b�N����D
 *
 *  �Ȃ��C���\�]���p�V�X�e���������ő�l�𒴂���0�ɖ߂�󋵂͍l�����Ă�
 *  �Ȃ��D
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_utm1.h"

#define	NO_LOOP		ULONG_C(100000)

SYSUTM	recent_sysutm;
char	*recent_sysutm_pos;
uint_t	cyclic_count;

void
cyclic_handler(intptr_t exinf)
{
	SYSUTM		sysutm, prev_sysutm;
	char		*prev_sysutm_pos;

	iloc_cpu();
	get_utm(&sysutm);
	prev_sysutm = recent_sysutm;
	prev_sysutm_pos = recent_sysutm_pos;
	recent_sysutm = sysutm;
	recent_sysutm_pos = "CYC";
	iunl_cpu();

	if (prev_sysutm > sysutm) {
		syslog(LOG_NOTICE,
				"system performance time goes back: %ld(%s) %ld(CYC)",
				((long_t) prev_sysutm), prev_sysutm_pos, ((ulong_t) sysutm));
	}
	cyclic_count += 1;
}

void
main_task(intptr_t exinf)
{
	SYSUTM		sysutm, prev_sysutm;
	char		*prev_sysutm_pos;
	ulong_t		i;

	cyclic_count = 0U;
	get_utm(&recent_sysutm);
	syslog(LOG_NOTICE, "system performance time test starts.");

	for (i = 0; i < NO_LOOP; i++) {
		loc_cpu();
		get_utm(&sysutm);
		prev_sysutm = recent_sysutm;
		prev_sysutm_pos = recent_sysutm_pos;
		recent_sysutm = sysutm;
		recent_sysutm_pos = "TSK";
		unl_cpu();

		if (prev_sysutm > sysutm) {
			syslog(LOG_NOTICE,
				"system performance time goes back: %ld(%s) %ld(TSK)",
				((long_t) prev_sysutm), prev_sysutm_pos, ((ulong_t) sysutm));
		}
	}

	syslog(LOG_NOTICE, "system performance time test finishes.");
	syslog(LOG_NOTICE, "number of cyclic handler execution: %d", cyclic_count);
	test_finish();
}