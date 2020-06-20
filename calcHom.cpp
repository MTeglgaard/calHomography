#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

const float calibrationSqaureDim =0.107f; //  meters  0.015;//
const Size chessboardDim  =  Size(6,8); //Size(7,10);//
bool showImg = true;
std::vector<cv::String> fn;

void getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>& allCorners, bool ShowResults = false);
std::vector<Mat> loadImagesFromFolder(std::string imFolder);

int main(int argc, char const *argv[]) {
  std::string Image_Path = "~/Documents/div_Programming/calcHom/calImg";

  if (argc != 2 )
  {
    printf("usages: ./calcHom <Image_Path>\n");
    std::cout << "try use defalt Path: " << Image_Path << '\n';
    return -1;
  } else {Image_Path = argv[1];
  std::cout << "path: "<< Image_Path << '\n';}

//std::string imageFolder = argv[1];
std::vector<Mat> images = loadImagesFromFolder(Image_Path);
//  std::vector<Mat> images = loadImagesFromFolder("~/Documents/div_Programming/calcHom/calImg");
//std::cout << "images vector elemet 1" << images[1] <<'\n';

  Mat image;
  images[0].copyTo(image);
  image = imread("/home/michael/Documents/div_Programming/calcHom/left008855.png", 1);
  if (!image.data )
  {
    printf("No Image data\n" );
    return -1;
  }
  //namedWindow("Display Image", WINDOW_AUTOSIZE );
  //imshow("Display Image", image);
  //waitKey(0);
  //destroyWindow("Display Image");
/**/
vector<vector<Point2f>> chessboardImgSpacePoint;

getChessboardCorners(images, chessboardImgSpacePoint, true);

for (int i = 0; i < chessboardImgSpacePoint.size(); i++) {
        std::cout << "chessboardImgSpacePoint: "<< i << "\n";
        for (int j = 0; j < chessboardImgSpacePoint[i].size(); j++)
            cout  << chessboardImgSpacePoint[i][j] << " \n";
        cout << endl;
    }

// for (size_t i = 0; i < chessboardImgSpacePoint.size; i++) {
//   std::cout << "chessboardImgSpacePoint: \n" << chessboardImgSpacePoint[i] << '\n';
// }

// for (vector<vector<Point2f>>::iterator iter = chessboardImgSpacePoint.begin(); iter != chessboardImgSpacePoint.end(); iter++)
// {
// std::cout << "chessboardImgSpacePoint: \n" << chessboardImgSpacePoint[iter] << '\n';
// }
  return 0;
}


// get chess board Corners
void getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>& allCorners, bool ShowResults)
{
int errorImg = 0;
int cornorImg =0;
  //ofstream myfile;
  //myfile.open ("cornorImg.txt");
  int i=0;
  for (vector<Mat>::iterator iter = images.begin(); iter != images.end(); iter++)
  {

		vector<Point2f> pointBuf;
		bool found = cv::findChessboardCorners(*iter, chessboardDim, pointBuf);


		if(found)
		{
			allCorners.push_back(pointBuf);
      cornorImg++;
      std::cout << "cornors in: " << fn[i] <<'\n';
      //myfile << "img "<< i << "\n";
		}else
    {
      errorImg++;
      std::cout << "no cornors in " << errorImg <<'\n';
    }

		if(ShowResults)
		{
			cv::drawChessboardCorners(*iter, chessboardDim , pointBuf, found);
      string CornorFile = "Cornor" + i;
      std::cout << CornorFile << '\n';
      //imwrite(CornorFile, *iter);
			imshow("Looking for Corners", *iter);
			waitKey(0);
		}
    i++;
	}
  std::cout << "cornors in " << cornorImg <<'\n';
  std::cout << "no cornors in " << errorImg <<'\n';
  //myfile.close();

}


std::vector<Mat> loadImagesFromFolder(std::string imFolder)
{
  // load all images in folder
    // std::vector<cv::String> fn;
    std::string fileNames = imFolder + "/*.png";

    char resolved_path[PATH_MAX];
    realpath("*.png", resolved_path);

    glob(fileNames, fn, false);//glob(resolved_path, fn, false);
    std::vector<Mat> images;
    size_t count = fn.size(); //number of png files in images folder
    for (size_t i=0; i<count; i++)
    {
      images.push_back(imread(fn[i]));
    //  std::cout << i <<" path: " << fn[i] << '\n';
    }
    return images;
}
