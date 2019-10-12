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
 *  @(#) $Id: target_serial.c 2202 2011-07-26 13:27:11Z ertl-honda $
 */

/*
 *  �V���A��I/O�f�o�C�X�iSIO�j�h���C�o�iCY8C5XLP�p�j
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_serial.h"
#include "core_insn.h"
#include "cyfitter.h"
#include "UART_1.h"
#if (TNUM_SIOP >= 2)
	#include "UART_2.h"
#endif /* TNUM_SIOP >= 2 */
#if(UART_1_INTERNAL_CLOCK_USED)
    #include "UART_1_IntClock.h"
#endif /* End UART_1_INTERNAL_CLOCK_USED */

/*
 *  �V���A��I/O�|�[�g�������u���b�N�̒�`
 */
typedef struct sio_port_initialization_block {
	ID       port;   /* SIO�̃|�[�gID(�_���ԍ�) */
	INTNO    intno;  /* �����ݔԍ� */
} SIOPINIB;

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̒�`
 */
struct sio_port_control_block {
	const SIOPINIB  *p_siopinib;  /* �V���A��I/O�|�[�g�������u���b�N */
	intptr_t        exinf;        /* �g����� */
	bool_t          opnflg;       /* �I�[�v���ς݃t���O */
};

/*
 * �V���A��I/O�|�[�g�������u���b�N
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{(ID)0, (INTNO)INTNO_SIO},
#if (TNUM_SIOP >= 2)
	{(ID)1, (INTNO)INTNO_SIO},
#endif /* TNUM_SIOP >= 2 */
};

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̃G���A
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  �V���A��I/O�|�[�gID����Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_SIOP(siopid)	((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  �^�[�Q�b�g�̃V���A��������
 *
 * PSoC Creator����������UART�h���C�o���Q�l�ɍ쐬
 *
 * �EUART_*_TXCLKGENDP�V���{���̒�`���s���̂��߂��̂܂܈��p
 * �EUART_1_INTERNAL_CLOCK_USED�V���{���̓��[�U�I���\�Ƃ���
 */
void target_usart_init(ID siopid)
{
	switch(siopid) {
	case 0:	/* �V���A���|�[�gID:0 */
		if((UART_1_RXBITCTR_CONTROL_REG && UART_1_CNTR_ENABLE) == 0) {
	        /* Init Count7 period */
	        UART_1_RXBITCTR_PERIOD_REG = UART_1_RXBITCTR_INIT;
	        /* Configure the Initial RX interrupt mask */
	        UART_1_RXSTATUS_MASK_REG  = UART_1_INIT_RX_INTERRUPTS_MASK;
	
	        /* Write Counter Value for TX Bit Clk Generator*/
	        #if(UART_1_TXCLKGEN_DP)
	            UART_1_TXBITCLKGEN_CTR_REG = UART_1_BIT_CENTER;
	            UART_1_TXBITCLKTX_COMPLETE_REG = (UART_1_NUMBER_OF_DATA_BITS +
	                        UART_1_NUMBER_OF_START_BIT) * UART_1_OVER_SAMPLE_COUNT;
	        #else
	            UART_1_TXBITCTR_PERIOD_REG = ((UART_1_NUMBER_OF_DATA_BITS +
	                        UART_1_NUMBER_OF_START_BIT) * UART_1_OVER_SAMPLE_8) - 1u;
	        #endif /* End UART_1_TXCLKGEN_DP */

	        /* Configure the Initial TX interrupt mask */
	        #if(UART_1_TX_INTERRUPT_ENABLED && (UART_1_TXBUFFERSIZE > UART_1_FIFO_LENGTH))
	            UART_1_TXSTATUS_MASK_REG = UART_1_TX_STS_FIFO_EMPTY;
	        #else
	            UART_1_TXSTATUS_MASK_REG = UART_1_INIT_TX_INTERRUPTS_MASK;
	        #endif /*End UART_1_TX_INTERRUPT_ENABLED*/

	        /*RX Counter (Count7) Enable */
	        UART_1_RXBITCTR_CONTROL_REG |= UART_1_CNTR_ENABLE;
	        /* Enable the RX Interrupt. */
/*	        UART_1_RXSTATUS_ACTL_REG  |= UART_1_INT_ENABLE;*/

	        /*TX Counter (DP/Count7) Enable */
	        #if(!UART_1_TXCLKGEN_DP)
	            UART_1_TXBITCTR_CONTROL_REG |= UART_1_CNTR_ENABLE;
	        #endif /* End UART_1_TXCLKGEN_DP */
	        /* Enable the TX Interrupt. */
/*	        UART_1_TXSTATUS_ACTL_REG |= UART_1_INT_ENABLE;*/

		    #if(UART_1_INTERNAL_CLOCK_USED)
	    	   /* Enable the clock. */
		        UART_1_IntClock_Start();
		    #endif /* End UART_1_INTERNAL_CLOCK_USED */
		}
		break;
	default: /* ����`�|�[�g */
		break;
	};
}

/*
 *  SIO�h���C�o�̏�����
 */
void
sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̏�����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->opnflg = false;
	}
}


/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	bool_t  opnflg;
	ER      ercd;

	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  �I�[�v�������|�[�g�����邩��opnflg�ɓǂ�ł����D
	 */
	opnflg = p_siopcb->opnflg;

	p_siopcb->exinf = exinf;

	/*
	 *  �n�[�h�E�F�A�̏�����
	 */
	target_usart_init(siopid);

	/*
	 *  �V���A��I/O�����݂̃}�X�N����������D
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopinib->intno);
		assert(ercd == E_OK);
	}

	return(p_siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  �V���A��I/O�����݂��}�X�N����D
	 */
	if (!(p_siopcb->opnflg)) {
		dis_int(p_siopcb->p_siopinib->intno);
	}
}

/*
 *  SIO�̊����݃T�[�r�X���[�`��
 */
void
sio_isr(intptr_t exinf)
{
	SIOPCB          *p_siopcb;

	p_siopcb = get_siopcb(exinf);

	/*
	 *  �����݂̃N���A
	 */
/* PSoC UART�ł��K�v���v�m�F */

/* �V���A���|�[�g��؂�ւ���ꍇ�́Cp_siopcb->p_siopinib->ID �Ŕ��ʂ���*/

	if ((UART_1_ReadRxStatus() & UART_1_RX_STS_FIFO_NOTEMPTY) != 0u) {
		/*
		 *  ��M�ʒm�R�[���o�b�N���[�`�����Ăяo���D
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	if ((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_FULL) == 0u) {
		/*
		 *  ���M�\�R�[���o�b�N���[�`�����Ăяo���D
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
bool_t
sio_snd_chr(SIOPCB *p_siopcb, char c)
{
/* �V���A���|�[�g��؂�ւ���ꍇ�́Cp_siopcb->p_siopinib->ID �Ŕ��ʂ���*/
	if((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_FULL) == 0u){
        UART_1_TXDATA_REG = (uint8)c;
		return(true);
	}
	return(false);
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
/* �V���A���|�[�g��؂�ւ���ꍇ�́Cp_siopcb->p_siopinib->ID �Ŕ��ʂ���*/
	if((UART_1_ReadRxStatus() & UART_1_RX_STS_FIFO_NOTEMPTY) != 0u){
		return((int_t) UART_1_GetChar());
	}
	return(-1);
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
/* �V���A���|�[�g��؂�ւ���ꍇ�́Cp_siopcb->p_siopinib->ID �Ŕ��ʂ���*/
	switch (cbrtn) {
	  case SIO_RDY_SND:
        /* Enable the TX Interrupt. */
        UART_1_TXSTATUS_ACTL_REG |= UART_1_INT_ENABLE;
		break;
	  case SIO_RDY_RCV:
        /* Enable the RX Interrupt. */
        UART_1_RXSTATUS_ACTL_REG  |= UART_1_INT_ENABLE;
		break;
	}
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
/* �V���A���|�[�g��؂�ւ���ꍇ�́Cp_siopcb->p_siopinib->ID �Ŕ��ʂ���*/
	switch (cbrtn) {
	  case SIO_RDY_SND:
        /* Disable the TX Interrupt. */
        UART_1_TXSTATUS_ACTL_REG &= (uint8)~UART_1_INT_ENABLE;
		break;
	  case SIO_RDY_RCV:
        /* Disable the RX Interrupt. */
        UART_1_RXSTATUS_ACTL_REG  &= (uint8)~UART_1_INT_ENABLE;
		break;
	}
}