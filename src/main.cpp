#include "CameraPerspective.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"

Mat RenderFrame(ICamera& camera)
//THE CODE WAS DONE IN COOPERATION WITH IVAN KABADZHOV

{
	// consider a color for every primitive following the instructions

	CPrimSphere s1(RGB(1, 0, 0), Vec3f(-2, 1.7f, 0), 2);
	CPrimSphere s2(RGB(0, 1, 0) , Vec3f(1, -1, 1), 2.2f);
	CPrimSphere s3(RGB(0, 0, 1), Vec3f(3, 0.8f, -2), 2);

	CPrimPlane p1(RGB(1, 1, 0), Vec3f(0, -1, 0), Vec3f(0, 1, 0));

	CPrimTriangle t1(RGB(0, 1, 1), Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2));
	CPrimTriangle t2(RGB(1, 1, 1), Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3));

	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray

	CPrim* primitives[6] =  {&s1, &s2, &s3, &p1, &t1, &t2}; // array to store the primitives

	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			// initialize array for every pixel
			if(!camera.InitRay(x, y, ray))
				continue;
			Vec3f col = RGB(0, 0, 0); // background color
			// find closest intersection by checking every pixel
			for(auto ind: primitives)
				if(ind->Intersect(ray))
					col = ind->m_color;

			img.at<Vec3f>(y, x) = col; // store pixel color
		}

	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[]) // remain unchanged
{
	const Size resolution(800, 600);
	// render three images with different camera settings

	CCameraPerspective c1(Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	Mat img1 = RenderFrame(c1);
	imwrite("perspective1.jpg", img1);

	CCameraPerspective c2(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution);
	Mat img2 = RenderFrame(c2);
	imwrite("perspective2.jpg", img2);

	CCameraPerspective c3(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45, resolution);
	Mat img3 = RenderFrame(c3);
	imwrite("perspective3.jpg", img3);
	return 0;
}
