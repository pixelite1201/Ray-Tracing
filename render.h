/* Contains rendering interface details*/


#include "object.h"

class render
{
	public:
		int w,h,pw,ph;
		int objCnt, sphCnt, coneCnt, cylCnt;
		int antiAlias, ambComp;
		vector *img;
		int **lightSrc;
		
		int lightSrcCnt;
		int depth;
		
		render()
		{
			objCnt = sphCnt = coneCnt = cylCnt = lightSrcCnt = 0;
		}
		void initImg();
		void readInput(char *fname, camera &cam);
		vector rayTrace(vector rOrigin, vector rDir, camera cam, int argDepth);
		void renderImage(camera cam);
		double diffuse(vector lightDir,vector ptHit);
};
