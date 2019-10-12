/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: sys_manage.c 2018 2010-12-31 13:43:05Z ertl-hiro $
 */

/*
 *		�V�X�e����ԊǗ��@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_ROT_RDQ_ENTER
#define LOG_ROT_RDQ_ENTER(tskpri)
#endif /* LOG_ROT_RDQ_ENTER */

#ifndef LOG_ROT_RDQ_LEAVE
#define LOG_ROT_RDQ_LEAVE(ercd)
#endif /* LOG_ROT_RDQ_LEAVE */

#ifndef LOG_IROT_RDQ_ENTER
#define LOG_IROT_RDQ_ENTER(tskpri)
#endif /* LOG_IROT_RDQ_ENTER */

#ifndef LOG_IROT_RDQ_LEAVE
#define LOG_IROT_RDQ_LEAVE(ercd)
#endif /* LOG_IROT_RDQ_LEAVE */

#ifndef LOG_GET_TID_ENTER
#define LOG_GET_TID_ENTER(p_tskid)
#endif /* LOG_GET_TID_ENTER */

#ifndef LOG_GET_TID_LEAVE
#define LOG_GET_TID_LEAVE(ercd, tskid)
#endif /* LOG_GET_TID_LEAVE */

#ifndef LOG_IGET_TID_ENTER
#define LOG_IGET_TID_ENTER(p_tskid)
#endif /* LOG_IGET_TID_ENTER */

#ifndef LOG_IGET_TID_LEAVE
#define LOG_IGET_TID_LEAVE(ercd, tskid)
#endif /* LOG_IGET_TID_LEAVE */

#ifndef LOG_LOC_CPU_ENTER
#define LOG_LOC_CPU_ENTER()
#endif /* LOG_LOC_CPU_ENTER */

#ifndef LOG_LOC_CPU_LEAVE
#define LOG_LOC_CPU_LEAVE(ercd)
#endif /* LOG_LOC_CPU_LEAVE */

#ifndef LOG_ILOC_CPU_ENTER
#define LOG_ILOC_CPU_ENTER()
#endif /* LOG_ILOC_CPU_ENTER */

#ifndef LOG_ILOC_CPU_LEAVE
#define LOG_ILOC_CPU_LEAVE(ercd)
#endif /* LOG_ILOC_CPU_LEAVE */

#ifndef LOG_UNL_CPU_ENTER
#define LOG_UNL_CPU_ENTER()
#endif /* LOG_UNL_CPU_ENTER */

#ifndef LOG_UNL_CPU_LEAVE
#define LOG_UNL_CPU_LEAVE(ercd)
#endif /* LOG_UNL_CPU_LEAVE */

#ifndef LOG_IUNL_CPU_ENTER
#define LOG_IUNL_CPU_ENTER()
#endif /* LOG_IUNL_CPU_ENTER */

#ifndef LOG_IUNL_CPU_LEAVE
#define LOG_IUNL_CPU_LEAVE(ercd)
#endif /* LOG_IUNL_CPU_LEAVE */

#ifndef LOG_DIS_DSP_ENTER
#define LOG_DIS_DSP_ENTER()
#endif /* LOG_DIS_DSP_ENTER */

#ifndef LOG_DIS_DSP_LEAVE
#define LOG_DIS_DSP_LEAVE(ercd)
#endif /* LOG_DIS_DSP_LEAVE */

#ifndef LOG_ENA_DSP_ENTER
#define LOG_ENA_DSP_ENTER()
#endif /* LOG_ENA_DSP_ENTER */

#ifndef LOG_ENA_DSP_LEAVE
#define LOG_ENA_DSP_LEAVE(ercd)
#endif /* LOG_ENA_DSP_LEAVE */

#ifndef LOG_SNS_CTX_ENTER
#define LOG_SNS_CTX_ENTER()
#endif /* LOG_SNS_CTX_ENTER */

#ifndef LOG_SNS_CTX_LEAVE
#define LOG_SNS_CTX_LEAVE(state)
#endif /* LOG_SNS_CTX_LEAVE */

#ifndef LOG_SNS_LOC_ENTER
#define LOG_SNS_LOC_ENTER()
#endif /* LOG_SNS_LOC_ENTER */

#ifndef LOG_SNS_LOC_LEAVE
#define LOG_SNS_LOC_LEAVE(state)
#endif /* LOG_SNS_LOC_LEAVE */

#ifndef LOG_SNS_DSP_ENTER
#define LOG_SNS_DSP_ENTER()
#endif /* LOG_SNS_DSP_ENTER */

#ifndef LOG_SNS_DSP_LEAVE
#define LOG_SNS_DSP_LEAVE(state)
#endif /* LOG_SNS_DSP_LEAVE */

#ifndef LOG_SNS_DPN_ENTER
#define LOG_SNS_DPN_ENTER()
#endif /* LOG_SNS_DPN_ENTER */

#ifndef LOG_SNS_DPN_LEAVE
#define LOG_SNS_DPN_LEAVE(state)
#endif /* LOG_SNS_DPN_LEAVE */

#ifndef LOG_SNS_KER_ENTER
#define LOG_SNS_KER_ENTER()
#endif /* LOG_SNS_KER_ENTER */

#ifndef LOG_SNS_KER_LEAVE
#define LOG_SNS_KER_LEAVE(state)
#endif /* LOG_SNS_KER_LEAVE */

/*
 *  �^�X�N�̗D�揇�ʂ̉�]
 */
#ifdef TOPPERS_rot_rdq

ER
rot_rdq(PRI tskpri)
{
	uint_t	pri;
	QUEUE	*p_queue;
	ER		ercd;

	LOG_ROT_RDQ_ENTER(tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TPRI_SELF(tskpri);

	t_lock_cpu();
	pri = (tskpri == TPRI_SELF) ? p_runtsk->priority : INT_PRIORITY(tskpri);
	p_queue = &(ready_queue[pri]);
	if (queue_empty(p_queue)) {
		ercd = E_OK;
	}
	else if ((((TCB *)(p_queue->p_next))->p_tinib->tskatr & TA_RSTR) != 0U) {
		ercd = E_NOSPT;
	}
	else {
		if (rotate_ready_queue(p_queue)) {
			dispatch();
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_ROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rot_rdq */

/*
 *  �^�X�N�̗D�揇�ʂ̉�]�i��^�X�N�R���e�L�X�g�p�j
 */
#ifdef TOPPERS_irot_rdq

ER
irot_rdq(PRI tskpri)
{
	QUEUE	*p_queue;
	ER		ercd;

	LOG_IROT_RDQ_ENTER(tskpri);
	CHECK_INTCTX_UNL();
	CHECK_TPRI(tskpri);

	i_lock_cpu();
	p_queue = &(ready_queue[INT_PRIORITY(tskpri)]);
	if (queue_empty(p_queue)) {
		ercd = E_OK;
	}
	else if ((((TCB *)(p_queue->p_next))->p_tinib->tskatr & TA_RSTR) != 0U) {
		ercd = E_NOSPT;
	}
	else {
		if (rotate_ready_queue(p_queue)) {
			reqflg = true;
		}
		ercd = E_OK;
	}
	i_unlock_cpu();

  error_exit:
	LOG_IROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_irot_rdq */

/*
 *  ���s��Ԃ̃^�X�NID�̎Q��
 */
#ifdef TOPPERS_get_tid

ER
get_tid(ID *p_tskid)
{
	ER		ercd;

	LOG_GET_TID_ENTER(p_tskid);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*p_tskid = TSKID(p_runtsk);
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_GET_TID_LEAVE(ercd, *p_tskid);
	return(ercd);
}

#endif /* TOPPERS_get_tid */

/*
 *  ���s��Ԃ̃^�X�NID�̎Q�Ɓi��^�X�N�R���e�L�X�g�p�j
 */
#ifdef TOPPERS_iget_tid

ER
iget_tid(ID *p_tskid)
{
	ER		ercd;

	LOG_IGET_TID_ENTER(p_tskid);
	CHECK_INTCTX_UNL();

	i_lock_cpu();
	*p_tskid = (p_runtsk == NULL) ? TSK_NONE : TSKID(p_runtsk);
	ercd = E_OK;
	i_unlock_cpu();

  error_exit:
	LOG_IGET_TID_LEAVE(ercd, *p_tskid);
	return(ercd);
}

#endif /* TOPPERS_iget_tid */

/*
 *  CPU���b�N��Ԃւ̈ڍs
 */
#ifdef TOPPERS_loc_cpu

ER
loc_cpu(void)
{
	ER		ercd;

	LOG_LOC_CPU_ENTER();
	CHECK_TSKCTX();

	if (!t_sense_lock()) {
		t_lock_cpu();
	}
	ercd = E_OK;

  error_exit:
	LOG_LOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_loc_cpu */

/*
 *  CPU���b�N��Ԃւ̈ڍs�i��^�X�N�R���e�L�X�g�p�j
 */
#ifdef TOPPERS_iloc_cpu

ER
iloc_cpu(void)
{
	ER		ercd;

	LOG_ILOC_CPU_ENTER();
	CHECK_INTCTX();

	if (!i_sense_lock()) {
		i_lock_cpu();
	}
	ercd = E_OK;

  error_exit:
	LOG_ILOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iloc_cpu */

/*
 *  CPU���b�N��Ԃ̉���
 *
 *  CPU���b�N���́C�f�B�X�p�b�`���K�v�ƂȂ�T�[�r�X�R�[�����Ăяo����
 *  �Ƃ͂ł��Ȃ����߁CCPU���b�N��Ԃ̉������Ƀf�B�X�p�b�`�����N������
 *  �K�v�͂Ȃ��D
 */
#ifdef TOPPERS_unl_cpu

ER
unl_cpu(void)
{
	ER		ercd;

	LOG_UNL_CPU_ENTER();
	CHECK_TSKCTX();

	if (t_sense_lock()) {
		t_unlock_cpu();
	}
	ercd = E_OK;

  error_exit:
	LOG_UNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_unl_cpu */

/*
 *  CPU���b�N��Ԃ̉����i��^�X�N�R���e�L�X�g�p�j
 *
 *  CPU���b�N���́C�f�B�X�p�b�`���K�v�ƂȂ�T�[�r�X�R�[�����Ăяo����
 *  �Ƃ͂ł��Ȃ����߁CCPU���b�N��Ԃ̉������Ƀf�B�X�p�b�`���̋N����v
 *  ������K�v�͂Ȃ��D
 */
#ifdef TOPPERS_iunl_cpu

ER
iunl_cpu(void)
{
	ER		ercd;

	LOG_IUNL_CPU_ENTER();
	CHECK_INTCTX();

	if (i_sense_lock()) {
		i_unlock_cpu();
	}
	ercd = E_OK;

  error_exit:
	LOG_IUNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iunl_cpu */

/*
 *  �f�B�X�p�b�`�̋֎~
 */
#ifdef TOPPERS_dis_dsp

ER
dis_dsp(void)
{
	ER		ercd;

	LOG_DIS_DSP_ENTER();
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	disdsp = true;
	dspflg = false;
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_DIS_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_dis_dsp */

/*
 *  �f�B�X�p�b�`�̋���
 */
#ifdef TOPPERS_ena_dsp

ER
ena_dsp(void)
{
	ER		ercd;

	LOG_ENA_DSP_ENTER();
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	disdsp = false;
	if (ipmflg) {
		dspflg = true;
		if (p_runtsk != p_schedtsk) {
			dispatch();
		}
	}
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_ENA_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ena_dsp */

/*
 *  �R���e�L�X�g�̎Q��
 */
#ifdef TOPPERS_sns_ctx

bool_t
sns_ctx(void)
{
	bool_t	state;

	LOG_SNS_CTX_ENTER();
	state = sense_context() ? true : false;
	LOG_SNS_CTX_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_ctx */

/*
 *  CPU���b�N��Ԃ̎Q��
 */
#ifdef TOPPERS_sns_loc

bool_t
sns_loc(void)
{
	bool_t	state;

	LOG_SNS_LOC_ENTER();
	state = x_sense_lock() ? true : false;
	LOG_SNS_LOC_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_loc */

/*
 *  �f�B�X�p�b�`�֎~��Ԃ̎Q��
 */
#ifdef TOPPERS_sns_dsp

bool_t
sns_dsp(void)
{
	bool_t	state;

	LOG_SNS_DSP_ENTER();
	state = disdsp;
	LOG_SNS_DSP_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_dsp */

/*
 *  �f�B�X�p�b�`�ۗ���Ԃ̎Q��
 */
#ifdef TOPPERS_sns_dpn

bool_t
sns_dpn(void)
{
	bool_t	state;

	LOG_SNS_DPN_ENTER();
	state = (sense_context() || t_sense_lock() || !dspflg) ? true : false;
	LOG_SNS_DPN_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_dpn */

/*
 *  �J�[�l���񓮍��Ԃ̎Q��
 */
#ifdef TOPPERS_sns_ker

bool_t
sns_ker(void)
{
	bool_t	state;

	LOG_SNS_KER_ENTER();
	state = kerflg ? false : true;
	LOG_SNS_KER_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_ker */