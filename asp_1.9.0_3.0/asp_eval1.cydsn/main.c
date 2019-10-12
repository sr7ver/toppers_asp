/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <device.h>
extern void sta_ker(void);

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	__disable_fault_irq();	/* cpsid f*/
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	sta_ker();
}

/* [] END OF FILE */
