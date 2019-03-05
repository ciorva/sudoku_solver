#include "sudoku_solver.h"

void solveSudoku(std::vector< std::vector <int> > &m){
	int i,j,n,nc=1,k;
	int C,rb,cb;
	int ind[10];
	double val[10];
	val[1]=1.0;
	val[2]=1.0;
	val[3]=1.0;
	val[4]=1.0;
	val[5]=1.0;
	val[6]=1.0;
	val[7]=1.0;
	val[8]=1.0;
	val[9]=1.0;
	//creating model
	glp_prob *mip = glp_create_prob();
	glp_set_obj_dir(mip, GLP_MAX);
	glp_term_out(GLP_OFF);
	//Add Variables
	glp_add_cols(mip,729);
	for(i=1;i<=729;i++){
		glp_set_obj_coef(mip,i,1.0);
		glp_set_col_kind(mip,i,GLP_BV);
	}
	//Add Constraints
	glp_add_rows(mip,324);
	for(i=1;i<=9;i++){
		for(j=1;j<9;j++){
			for(n=1;n<=9;n++) ind[n]=(i-1)*81+(j-1)*9+(n-1) + 1;
			glp_set_mat_row(mip,nc,9,ind,val);
			glp_set_row_bnds(mip,nc,GLP_FX,1.0,1.0);
			nc++;
		}
	}
	for(j=1;j<=9;j++){
		for(n=1;n<=9;n++){
			for(i=1;i<=9;i++) ind[i]=(i-1)*81+(j-1)*9+(n-1) + 1;
			glp_set_mat_row(mip,nc,9,ind,val);
			glp_set_row_bnds(mip,nc,GLP_FX,1.0,1.0);
			nc++;
		}
	}
	for(i=1;i<=9;i++){
		for(n=1;n<=9;n++){
			for(j=1;j<=9;j++) ind[j]=(i-1)*81+(j-1)*9+(n-1) + 1;
			glp_set_mat_row(mip,nc,9,ind,val);
			glp_set_row_bnds(mip,nc,GLP_FX,1.0,1.0);
			nc++;
		}
	}
	for(C=1;C<=9;C++){
		for(n=1;n<=9;n++){
			k=1;
			rb=(C-1)/3;
			cb=(C-1)%3;
			for(i=1+rb*3;i<4+rb*3;i++){
				for(j=1+cb*3;j<4+cb*3;j++){
					ind[k]=(i-1)*81+(j-1)*9+(n-1) + 1;
					k++;
				}
			}
			glp_set_mat_row(mip,nc,9,ind,val);
			glp_set_row_bnds(mip,nc,GLP_FX,1.0,1.0);
			nc++;
		}
	}
	// Adding instance constraints
	for(i=1;i<=9;i++){
		for(j=1;j<=9;j++){
			if (m[i-1][j-1]>0){
				ind[1]=(i-1)*81+(j-1)*9+(m[i-1][j-1]-1) + 1;
				nc=glp_add_rows(mip,1);
				glp_set_mat_row(mip,nc,1,ind,val);
				glp_set_row_bnds(mip,nc,GLP_FX,1.0,1.0);
			}
		}
	}
	
	// Solving MIP
	glp_iocp parm;
	glp_init_iocp(&parm);
	parm.presolve = GLP_ON;
	glp_intopt(mip,&parm);
	if (glp_mip_status(mip)==GLP_OPT){
		for(i=1;i<=9;i++){
			for(n=1;n<=9;n++){
				for(j=1;j<=9;j++){
					if (glp_mip_col_val(mip,(i-1)*81+(j-1)*9+(n-1) + 1)>=0.9) m[i-1][j-1]=n;
				}
			}
		}
	}
	glp_delete_prob(mip);
	return;
}