#include <math.h>

namespace WgtStatErr{

	//double computeWeightedBinomialError(double sw_ps, 	/* Sum of weights */
	//									double ssqw_ps,	/* Sum of squared weights */
	//									double sw_fl,
	//									double ssqw_fl)
	//{
	//	double sw_tot		=0.0,
	//		   sw_ps_sq		=0.0,
	//		   sw_fl_sq		=0.0,
	//		   nume			=0.0,
	//		   deno			=0.0,
	//		   tmp			=0.0;
	//
	//	sw_tot		=sw_ps + sw_fl;
	//	deno		=sw_tot*sw_tot;
	//
	//	tmp			=ssqw_ps*sw_fl*sw_fl;
	//	nume		+=tmp;
	//	tmp			=ssqw_fl*sw_ps*sw_ps;
	//	nume		+=tmp;
	//	nume		=sqrt( nume );
	//
	//	return nume/deno;
	//};

	double computeWeightedBinomialError(double sw_1, 	
										double ssqw_1,
										double sw_2,
										double ssqw_2,
										bool isPassFalse=true)
	{
		double err	=0.0;
		double deno	=0.0;
		double nume	=0.0;

		// _1 for events which passed condition
		// _2 for events which did not pass condition
		if( isPassFalse )
		{
			double sw_tot		=0.0,
				   sw_ps_sq		=0.0,
				   sw_fl_sq		=0.0;
			double sw_ps		=sw_1;
			double sw_fl		=sw_2
			double ssqw_ps		=ssqw_1;
			double ssqw_fl		=ssqw_2;
	
			sw_tot		=sw_ps + sw_fl;
			deno		=sw_tot*sw_tot;
	
			tmp			=ssqw_ps*sw_fl*sw_fl;
			nume		+=tmp;
			tmp			=ssqw_fl*sw_ps*sw_ps;
			nume		+=tmp;
			nume		=sqrt( nume );
			err=nume/deno;
		}	
		else
		{
		// _1 for events which passed condition
		// _2 for total events

			double sw_ps		=sw_1;
			double sw_tot		=sw_2;
			double sw_fl		=sw_2 - sw_1;
			double ssqw_ps		=ssqw_1;
			double ssqw_fl		=ssqw_2 - ssqw_1;
			double sw_ps_sq		=0.0,
			double sw_fl_sq		=0.0;
			double tmp			=0.0;
			
			deno		=sw_tot*sw_tot;
			tmp			=ssqw_ps*sw_fl*sw_fl;
			nume		+=tmp;
			tmp			=ssqw_fl*sw_ps*sw_ps;
			nume		+=tmp;
			nume		=sqrt( nume );
			err=nume/deno;
		}
		
		return err;
	};
}
