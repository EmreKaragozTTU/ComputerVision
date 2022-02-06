

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	const int MaxPyrLevelCount = 6;

	cv::Mat Image0;
	cv::Mat Image1;
	cv::Mat MaskImage;

	cv::Mat GaussianPyr0[MaxPyrLevelCount]; /* Gaussian Pyramid for Image0 */
	cv::Mat GaussianPyr1[MaxPyrLevelCount]; /* Gaussian Pyramid for Image1 */
	cv::Mat GaussianPyr2[MaxPyrLevelCount]; /* Gaussian Pyramid for mask image */

	cv::Mat LaplacianPyr0[MaxPyrLevelCount]; /* Laplacian Pyramid for Image0 */
	cv::Mat LaplacianPyr1[MaxPyrLevelCount]; /* Laplacian Pyramid for Image1 */

	cv::Mat BlendPyr[MaxPyrLevelCount];

	/*
	Image0 = cv::imread("halfapple.png");
	Image1 = cv::imread("halforange.png");
	cv::imread("apple.jpg").convertTo(Image0, CV_32F, 1.0f / 255.0f);
	cv::imread("orange.jpg").convertTo(Image1, CV_32F, 1.0f / 255.0f);
	cv::imread("mask.png").convertTo(MaskImage, CV_32F, 1.0f / 255.0f);

	cv::imread("goz2.png").convertTo(Image0, CV_32F, 1.0f / 255.0f);
	cv::imread("el.png").convertTo(Image1, CV_32F, 1.0f / 255.0f);
	cv::imread("goz2mask.png").convertTo(MaskImage, CV_32F, 1.0f / 255.0f);
	*/

	GaussianPyr0[0] = Image0;
	GaussianPyr1[0] = Image1;
	GaussianPyr2[0] = MaskImage;

	/* Compute Gaussian Pyramids */
	for (size_t LevelIdx = 0; LevelIdx < MaxPyrLevelCount - 1; LevelIdx++)
	{
		cv::pyrDown(GaussianPyr0[LevelIdx], GaussianPyr0[LevelIdx + 1], cv::Size(GaussianPyr0[LevelIdx].cols / 2, GaussianPyr0[LevelIdx].rows / 2));
		cv::pyrDown(GaussianPyr1[LevelIdx], GaussianPyr1[LevelIdx + 1], cv::Size(GaussianPyr1[LevelIdx].cols / 2, GaussianPyr1[LevelIdx].rows / 2));
		cv::pyrDown(GaussianPyr2[LevelIdx], GaussianPyr2[LevelIdx + 1], cv::Size(GaussianPyr2[LevelIdx].cols / 2, GaussianPyr2[LevelIdx].rows / 2));
	}

	/* Compute Laplacian Pyramids and blend each level */
	for (size_t LevelIdx = 0; LevelIdx < MaxPyrLevelCount - 1; LevelIdx++)
	{
		cv::Mat Temp;

		cv::pyrUp(GaussianPyr0[LevelIdx + 1], Temp, GaussianPyr0[LevelIdx].size());
		LaplacianPyr0[LevelIdx] = GaussianPyr0[LevelIdx] - Temp;

		cv::pyrUp(GaussianPyr1[LevelIdx + 1], Temp, GaussianPyr1[LevelIdx].size());
		LaplacianPyr1[LevelIdx] = GaussianPyr1[LevelIdx] - Temp;

		cv::Mat MaskedLevel0 = LaplacianPyr0[LevelIdx].mul(GaussianPyr2[LevelIdx]);
		cv::Mat MaskedLevel1 = LaplacianPyr1[LevelIdx].mul(cv::Scalar(1.0, 1.0, 1.0) - GaussianPyr2[LevelIdx]);

		BlendPyr[LevelIdx] = MaskedLevel0 + MaskedLevel1;
	}

	/* Blend top level Gaussian pyramid images */
	cv::Mat BlendedImage = GaussianPyr0[MaxPyrLevelCount - 1].mul(GaussianPyr2[MaxPyrLevelCount - 1]) +
							GaussianPyr1[MaxPyrLevelCount - 1].mul(cv::Scalar(1.0, 1.0, 1.0) - GaussianPyr2[MaxPyrLevelCount - 1]);

	/* Reconstruct blended image */
	for (int LevelIdx = MaxPyrLevelCount - 2; LevelIdx >= 0; LevelIdx--)
	{
		cv::Mat Temp;

		cv::pyrUp(BlendedImage, Temp, BlendPyr[LevelIdx].size());
		BlendedImage = BlendPyr[LevelIdx] + Temp;
	}

	BlendedImage.convertTo(BlendedImage, CV_8UC3, 255.0f);
	cv::imwrite("blended_image.jpg", BlendedImage);

	return 0;
}
