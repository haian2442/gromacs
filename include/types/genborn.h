/*
 * 
 *                This source code is part of
 * 
 *                 G   R   O   M   A   C   S
 * 
 *          GROningen MAchine for Chemical Simulations
 * 
 * Written by David van der Spoel, Erik Lindahl, Berk Hess, and others.
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2008, The GROMACS development team,
 * check out http://www.gromacs.org for more information.
 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * If you want to redistribute modifications, please consider that
 * scientific software is very special. Version control is crucial -
 * bugs must be traceable. We will be happy to consider code for
 * inclusion in the official distribution, but derived work must not
 * be called official GROMACS. Details are found in the README & COPYING
 * files - if they are missing, get the official version at www.gromacs.org.
 * 
 * To help us fund GROMACS development, we humbly ask that you cite
 * the papers on the package - you can find them in the top README file.
 * 
 * For more info, check our website at http://www.gromacs.org
 * 
 * And Hey:
 * Gallium Rubidium Oxygen Manganese Argon Carbon Silicon
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


typedef struct
{
	int nbonds;
	int bond[10];
	real length[10];
} genborn_bonds_t;


/* Struct to hold all the information for GB */
typedef struct
{
	int nr;                   /* number of atoms, length of arrays below */
	int n12;                  /* number of 1-2 (bond) interactions       */
	int n13;                  /* number of 1-3 (angle) terms             */
	int n14;                  /* number of 1-4 (torsion) terms           */
	int nlocal;               /* Length of local arrays (with DD)        */
	
	/* Arrays below that end with _globalindex are used for setting up initial values of
	 * all gb parameters and values. They all have length natoms, which for DD is the 
	 * global atom number. 
	 * Values are then taken from these arrays to local copies, that have names without
	 * _globalindex, in the routine make_local_gb(), which is called once for single
	 * node runs, and for DD at every call to dd_partition_system
	 */

	real  *gpol;              /* Atomic polarisation energies */
	real  *gpol_globalindex;  /*  */
	real  *gpol_still_work;   /* Work array for Still model */
	real  *gpol_hct_work;     /* Work array for HCT/OBC models */
	real  *bRad;              /* Atomic Born radii */
	real  *vsolv;             /* Atomic solvation volumes */
	real  *vsolv_globalindex; /*  */
	
	int *vs;                  /* Array for vsites-exclusions */   
	int *vs_globalindex;      /*  */
		
	real es;                  /* Solvation energy and derivatives */
	real *asurf;              /* Atomic surface area */
	rvec *dasurf;             /* Surface area derivatives */
	real as;                  /* Total surface area */

	real *drobc;              /* Parameters for OBC chain rule calculation */
	real *param;              /* Precomputed factor rai*atype->S_hct for HCT/OBC */
	real *param_globalindex;  /*  */
	
	real *log_table;          /* Table for logarithm lookup */
	
	real obc_alpha;           /* OBC parameters */
	real obc_beta;            /* OBC parameters */
	real obc_gamma;           /* OBC parameters */
	real gb_doffset;          /* Dielectric offset for Still/HCT/OBC */
	
	real *work;               /* Used for parallel summation and in the chain rule, length natoms         */
	real *dd_work;            /* Used for domain decomposition parallel runs, length natoms              */
	int  *count;              /* Used for setting up the special gb nblist, length natoms                 */
	int  **nblist_work;       /* Used for setting up the special gb nblist, dim natoms*nblist_work_nalloc */
	int  nblist_work_nalloc;  /* Length of second dimension of nblist_work                                */
} 
gmx_genborn_t;
