
#include "NppFilterTest.h"

using namespace std;

int test_nppiFilter(void)
{
	cv::Mat oHostSrc = cv::imread("E:/resource/History/lenna.png", cv::IMREAD_GRAYSCALE);
	imwrite("original.png", oHostSrc);
	Npp8u *oDeviceSrc;
	cudaMalloc((void**)&oDeviceSrc, sizeof(Npp8u)*oHostSrc.cols*oHostSrc.rows);

	NppiSize kernelSize = { 3, 1 }; // dimensions of convolution kernel (filter)
	NppiSize oSizeROI = { oHostSrc.cols - kernelSize.width + 1, oHostSrc.rows - kernelSize.height + 1 };
	Npp8u *oDeviceDst;
	//cudaMalloc((void**)&oDeviceDst, sizeof(Npp8u)*oSizeROI.width*oSizeROI.height);// allocate device image of appropriately reduced size
	cudaMalloc((void**)&oDeviceDst, sizeof(Npp8u)*oHostSrc.cols*oHostSrc.rows);// allocate device image of appropriately reduced size
	cv::Mat oHostDst(oHostSrc.rows, oHostSrc.cols, CV_8UC1);
	NppiPoint oAnchor = { 2, 1 }; // found that oAnchor = {2,1} or {3,1} works for kernel [-1 0 1] 
	NppStatus eStatusNPP;
	Npp32s hostKernel[3] = { -1, 0, 1 }; // convolving with this should do edge detection
	Npp32s* deviceKernel;
	size_t deviceKernelPitch;
	cudaMallocPitch((void**)&deviceKernel, &deviceKernelPitch, kernelSize.width * sizeof(Npp32s), kernelSize.height * sizeof(Npp32s));
	cudaMemcpy2D(deviceKernel, deviceKernelPitch, hostKernel,
		sizeof(Npp32s)*kernelSize.width, // sPitch
		sizeof(Npp32s)*kernelSize.width, // width
		kernelSize.height, // height
		cudaMemcpyHostToDevice);
	cudaMemcpy(oDeviceSrc, oHostSrc.data, sizeof(Npp8u)*oHostSrc.cols*oHostSrc.rows, cudaMemcpyHostToDevice);
	Npp32s divisor = 1; // no scaling
	Npp32s nSrcStep = 1;
	Npp32s nDstStep = 1;
	/*
	nppiFilter_8u_C1R (const Npp8u *pSrc,
							Npp32s nSrcStep, 
							Npp8u *pDst, 
							Npp32s nDstStep, 
							NppiSize oSizeROI, 
							const Npp32s *pKernel, 
							NppiSize oKernelSize, 
							NppiPoint oAnchor, 
							Npp32s nDivisor)
	*/
	eStatusNPP = nppiFilter_8u_C1R(oDeviceSrc, oHostSrc.cols,
		oDeviceDst, oHostSrc.cols,
		oSizeROI, deviceKernel, kernelSize, oAnchor, divisor);

	cout << "NppiFilter error status " << eStatusNPP << endl; // prints 0 (no errors)
	cudaMemcpy(oHostDst.data, oDeviceDst, sizeof(Npp8u)*oHostSrc.cols*oHostSrc.rows, cudaMemcpyDeviceToHost);

	cudaFree(deviceKernel);
	cudaFree(oDeviceSrc);
	cudaFree(oDeviceDst);
	cv::imwrite("Lena_filter_1d.png", oHostDst);
	return 0;
}