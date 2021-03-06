#include "df.h"

void df_igpt ( const int *num, int *iret )
/************************************************************************
 * df_igpt								*
 *									*
 * This subroutine returns the i reference grid index values for each	*
 * point on the internal grid.						*
 *									*
 * This computation has no operand.					*
 *									*
 * df_igpt ( num, iret )						*
 *									*
 * Input parameters:							*
 * 	*num		const int	Grid number			*
 * Output parameters:							*
 *	*iret		int		Return code			*
 **									*
 * Log:									*
 * T. Lee/SAIC		10/05	Created					*
 * R. Tian/SAIC		11/05	Recoded from Fortran			*
 ************************************************************************/
{
    int nrx, nry, nryy, kxyd, kxd, kyd, ksub1, ksub2, i, j, indx, zero,
        ier;
    float *gnrx, *gnry, *gnryy, *gnum;
/*----------------------------------------------------------------------*/
    *iret = 0;
    zero = 0;

    dg_ssub ( iret );

    /*
     * Get new scratch grids.
     */
    dg_nxts ( &nrx, iret );
    if ( *iret != 0 ) return;
    dg_getg ( &nrx, &gnrx, &kxd, &kyd, &ksub1, &ksub2, iret );
    dg_nxts ( &nry, iret );
    if ( *iret != 0 ) return;
    dg_getg ( &nry, &gnry, &kxd, &kyd, &ksub1, &ksub2, iret );
    dg_nxts ( &nryy, iret );
    if ( *iret != 0 ) return;
    dg_getg ( &nryy, &gnryy, &kxd, &kyd, &ksub1, &ksub2, iret );

    indx = 0;
    for ( j = 1; j <= kyd; j++ ) {
	for ( i = 1; i <= kxd; i++ ) {
	    gnrx[indx] = (float)i;
	    gnry[indx] = (float)j;
	    indx++;
	}
    }

    /*
     * Transform internal I,J values to I,J on the reference grid.
     */
    dg_getg ( num, &gnum, &kxd, &kyd, &ksub1, &ksub2, iret );
    kxyd = kxd * kyd;
    dg_igrg ( &kxyd, gnrx, gnry, gnum, gnryy, iret );

    dg_esub ( num, &zero, &zero, &zero, &ier );
    if ( ier != 0 ) *iret = ier;

    return;
}
