
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"


void ComputeHarrisCorner(const cv::Mat& iImage, cv::Mat& oImage)
{
	cv::Mat Corners;
	cv::cornerHarris(iImage, Corners, 2, 3, 0.04);

	cv::Mat NormalizedCorners;
	normalize(Corners, NormalizedCorners, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	convertScaleAbs(NormalizedCorners, Corners);

	for (int j = 0; j < NormalizedCorners.rows; j++)
	{
		for (int i = 0; i < NormalizedCorners.cols; i++)
		{
			if ((int)NormalizedCorners.at<float>(j, i) > 100)
			{
				circle(oImage, cv::Point(i, j), 5, cv::Scalar(0), 2, 8, 0);
			}
		}
	}
}


void ComputeSift(const cv::SiftFeatureDetector& iDetector, const cv::Mat& iImage, cv::Mat& oImage)
{
	std::vector<cv::KeyPoint> Keypoints;
	iDetector.detect(iImage, Keypoints);

	cv::drawKeypoints(iImage, Keypoints, oImage);
}


int main(int argc, char** argv)
{
	// cv::Mat InputImg = cv::imread("notredame.jpg", 0);

	cv::Mat InputImgScaled;
	cv::resize(InputImg, InputImgScaled, cv::Size(InputImg.cols / 2, InputImg.rows / 2));

	cv::Mat OutputImgHarris;
	cv::Mat OutputImgSift;

	cv::Mat OutputImgHarrisScaled;
	cv::Mat OutputImgSiftScaled;

	InputImg.copyTo(OutputImgHarris);
	ComputeHarrisCorner(InputImg, OutputImgHarris);

	InputImgScaled.copyTo(OutputImgHarrisScaled);
	ComputeHarrisCorner(InputImgScaled, OutputImgHarrisScaled);

	cv::imwrite("harris_output.jpg", OutputImgHarris);
	cv::imwrite("harris_output_scaled.jpg", OutputImgHarrisScaled);

	cv::SiftFeatureDetector Detector;

	ComputeSift(Detector, InputImg, OutputImgSift);

	ComputeSift(Detector, InputImgScaled, OutputImgSiftScaled);

	cv::imwrite("sift_output.jpg", OutputImgSift);
	cv::imwrite("sift_output_scaled.jpg", OutputImgSiftScaled);

	return 0;
}
