/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: check.h 2412 2012-09-01 04:05:55Z ertl-hiro $
 */

/*
 *		�G���[�`�F�b�N�p�}�N��
 */

#ifndef TOPPERS_CHECK_H
#define TOPPERS_CHECK_H

/*
 *  �\�񑮐��G���[�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_RSATR(atr, valid_atr) do {					\
	if (((atr) & ~(valid_atr)) != 0U) {						\
		ercd = E_RSATR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �D��x�͈̔͂̔���
 */
#define VALID_TPRI(tpri)	(TMIN_TPRI <= (tpri) && (tpri) <= TMAX_TPRI)

#define VALID_DPRI(dpri)	(TMIN_DPRI <= (dpri) && (dpri) <= TMAX_DPRI)

#define VALID_MPRI(mpri)	(TMIN_MPRI <= (mpri) && (mpri) <= TMAX_MPRI)

#define VALID_ISRPRI(isrpri) \
				(TMIN_ISRPRI <= (isrpri) && (isrpri) <= TMAX_ISRPRI)

#ifndef VALID_INTPRI_CHGIPM
#define VALID_INTPRI_CHGIPM(intpri) \
				(TMIN_INTPRI <= (intpri) && (intpri) <= TIPM_ENAALL)
#endif /* VALID_INTPRI_CHGIPM */

/*
 *  �^�X�N�D��x�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_TPRI(tpri) do {								\
	if (!VALID_TPRI(tpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_TPRI_INI(tpri) do {							\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_INI)) {		\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_TPRI_SELF(tpri) do {							\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_SELF)) {		\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �f�[�^�D��x�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_DPRI(dpri) do {								\
	if (!VALID_DPRI(dpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���b�Z�[�W�D��x�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_MPRI(mpri) do {								\
	if (!VALID_MPRI(mpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �����݃T�[�r�X���[�`���D��x�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ISRPRI(isrpri) do {							\
	if (!VALID_ISRPRI(isrpri)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �^�C���A�E�g�w��l�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_TMOUT(tmout) do {								\
	if (!(TMO_FEVR <= (tmout))) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �����ݗD��x�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_INTPRI_CHGIPM(intpri) do {					\
	if (!VALID_INTPRI_CHGIPM(intpri)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �����ݔԍ��̃`�F�b�N�iE_PAR�j
 */
#define CHECK_INTNO_CREISR(intno) do {						\
	if (!VALID_INTNO_CREISR(intno)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_INTNO_DISINT(intno) do {						\
	if (!VALID_INTNO_DISINT(intno)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �A���C�����Ă��邩�̔���
 */
#define ALIGNED(val, align)		((((uintptr_t)(val)) & ((align) - 1U)) == 0U)

#ifdef CHECK_FUNC_ALIGN
#define FUNC_ALIGNED(func)		ALIGNED(func, CHECK_FUNC_ALIGN)
#else /* CHECK_FUNC_ALIGN */
#define FUNC_ALIGNED(func)		true
#endif /* CHECK_FUNC_ALIGN */

#ifdef CHECK_STKSZ_ALIGN
#define STKSZ_ALIGNED(stksz)	ALIGNED(stksz, CHECK_STKSZ_ALIGN)
#else /* CHECK_STKSZ_ALIGN */
#define STKSZ_ALIGNED(stksz)	true
#endif /* CHECK_STKSZ_ALIGN */

#ifdef CHECK_STACK_ALIGN
#define STACK_ALIGNED(stack)	ALIGNED(stack, CHECK_STACK_ALIGN)
#else /* CHECK_STACK_ALIGN */
#define STACK_ALIGNED(stack)	true
#endif /* CHECK_STACK_ALIGN */

#ifdef CHECK_MPF_ALIGN
#define MPF_ALIGNED(mpf)		ALIGNED(mpf, CHECK_MPF_ALIGN)
#else /* CHECK_MPF_ALIGN */
#define MPF_ALIGNED(mpf)		true
#endif /* CHECK_MPF_ALIGN */

#ifdef CHECK_MB_ALIGN
#define MB_ALIGNED(mb)			ALIGNED(mb, CHECK_MB_ALIGN)
#else /* CHECK_MB_ALIGN */
#define MB_ALIGNED(mb)			true
#endif /* CHECK_MB_ALIGN */

/*
 *  NULL�łȂ����Ƃ̃`�F�b�N
 */
#ifdef CHECK_FUNC_NONNULL
#define FUNC_NONNULL(func)		((func) != NULL)
#else /* CHECK_FUNC_NONNULL */
#define FUNC_NONNULL(func)		true
#endif /* CHECK_FUNC_NONNULL */

#ifdef CHECK_STACK_NONNULL
#define STACK_NONNULL(stack)	((stack) != NULL)
#else /* CHECK_STACK_NONNULL */
#define STACK_NONNULL(stack)	true
#endif /* CHECK_STACK_NONNULL */

#ifdef CHECK_MPF_NONNULL
#define MPF_NONNULL(mpf)		((mpf) != NULL)
#else /* CHECK_MPF_NONNULL */
#define MPF_NONNULL(mpf)		true
#endif /* CHECK_MPF_NONNULL */

/*
 *  �֐��̐擪�Ԓn�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ALIGN_FUNC(func) do {							\
	if (!FUNC_ALIGNED(func)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_NONNULL_FUNC(func) do {						\
	if (!FUNC_NONNULL(func)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �X�^�b�N�T�C�Y�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ALIGN_STKSZ(stksz) do {						\
	if (!STKSZ_ALIGNED(stksz)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#ifndef TARGET_MIN_STKSZ
#define TARGET_MIN_STKSZ	1U		/* ����`�̏ꍇ��0�łȂ����Ƃ��`�F�b�N */
#endif /* TARGET_MIN_STKSZ */

#define CHECK_STKSZ_MIN(stksz) do {							\
	if ((stksz) < TARGET_MIN_STKSZ) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �X�^�b�N�̐擪�Ԓn�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ALIGN_STACK(stack) do {						\
	if (!STACK_ALIGNED(stack)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_NONNULL_STACK(stack) do {						\
	if (!STACK_NONNULL(stack)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �Œ蒷�������v�[���̈�̐擪�Ԓn�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ALIGN_MPF(mpf) do {							\
	if (!MPF_ALIGNED(mpf)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_NONNULL_MPF(mpf) do {							\
	if (!MPF_NONNULL(mpf)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �Ǘ��̈�̐擪�Ԓn�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_ALIGN_MB(mb) do {								\
	if (!MB_ALIGNED(mb)) {									\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���̑��̃p�����[�^�G���[�̃`�F�b�N�iE_PAR�j
 */
#define CHECK_PAR(exp) do {									\
	if (!(exp)) {											\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �I�u�W�F�N�gID�͈̔͂̔���
 */
#define VALID_TSKID(tskid)	(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)
#define VALID_SEMID(semid)	(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)
#define VALID_FLGID(flgid)	(TMIN_FLGID <= (flgid) && (flgid) <= tmax_flgid)
#define VALID_DTQID(dtqid)	(TMIN_DTQID <= (dtqid) && (dtqid) <= tmax_dtqid)
#define VALID_PDQID(pdqid)	(TMIN_PDQID <= (pdqid) && (pdqid) <= tmax_pdqid)
#define VALID_MBXID(mbxid)	(TMIN_MBXID <= (mbxid) && (mbxid) <= tmax_mbxid)
#define VALID_MPFID(mpfid)	(TMIN_MPFID <= (mpfid) && (mpfid) <= tmax_mpfid)
#define VALID_CYCID(cycid)	(TMIN_CYCID <= (cycid) && (cycid) <= tmax_cycid)
#define VALID_ALMID(almid)	(TMIN_ALMID <= (almid) && (almid) <= tmax_almid)
#define VALID_ISRID(isrid)	(TMIN_ISRID <= (isrid) && (isrid) <= tmax_isrid)

/*
 *  �I�u�W�F�N�gID�̃`�F�b�N�iE_ID�j
 */
#define CHECK_TSKID(tskid) do {								\
	if (!VALID_TSKID(tskid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_TSKID_SELF(tskid) do {						\
	if (!(VALID_TSKID(tskid) || (tskid) == TSK_SELF)) {		\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_SEMID(semid) do {								\
	if (!VALID_SEMID(semid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_FLGID(flgid) do {								\
	if (!VALID_FLGID(flgid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_DTQID(dtqid) do {								\
	if (!VALID_DTQID(dtqid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_PDQID(pdqid) do {								\
	if (!VALID_PDQID(pdqid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_MBXID(mbxid) do {								\
	if (!VALID_MBXID(mbxid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_MPFID(mpfid) do {								\
	if (!VALID_MPFID(mpfid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_CYCID(cycid) do {								\
	if (!VALID_CYCID(cycid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_ALMID(almid) do {								\
	if (!VALID_ALMID(almid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_ISRID(isrid) do {								\
	if (!VALID_ISRID(isrid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �ďo���R���e�L�X�g�̃`�F�b�N�iE_CTX�j
 */
#define CHECK_TSKCTX() do {									\
	if (sense_context()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_INTCTX() do {									\
	if (!sense_context()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �ďo���R���e�L�X�g��CPU���b�N��Ԃ̃`�F�b�N�iE_CTX�j
 */
#define CHECK_TSKCTX_UNL() do {								\
	if (sense_context() || t_sense_lock()) {				\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

#define CHECK_INTCTX_UNL() do {								\
	if (!sense_context() || i_sense_lock()) {				\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �f�B�X�p�b�`�ۗ���ԂłȂ����̃`�F�b�N�iE_CTX�j
 */
#define CHECK_DISPATCH() do {								\
	if (sense_context() || t_sense_lock() || !dspflg) {		\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���̑��̃R���e�L�X�g�G���[�̃`�F�b�N�iE_CTX�j
 */
#define CHECK_CTX(exp) do {									\
	if (!(exp)) {											\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���^�X�N���w�肵�Ă��Ȃ����̃`�F�b�N�iE_ILUSE�j
 */
#define CHECK_NONSELF(p_tcb) do {							\
	if ((p_tcb) == p_runtsk) {								\
		ercd = E_ILUSE;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���̑��̕s���g�p�G���[�̃`�F�b�N�iE_ILUSE�j
 */
#define CHECK_ILUSE(exp) do {								\
	if (!(exp)) {											\
		ercd = E_ILUSE;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ���T�|�[�g�@�\�G���[�̃`�F�b�N�iE_NOSPT�j
 */
#define CHECK_NOSPT(exp) do {								\
	if (!(exp)) {											\
		ercd = E_NOSPT;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  �ÓI�ȃI�u�W�F�N�g��ԃG���[�̃`�F�b�N�iE_OBJ�j
 */
#define CHECK_OBJ(exp) do {									\
	if (!(exp)) {											\
		ercd = E_OBJ;										\
		goto error_exit;									\
	}														\
} while (false)

#endif /* TOPPERS_CHECK_H */