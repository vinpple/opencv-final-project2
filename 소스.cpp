
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 이미지와 파일 이름을 저장할 변수들을 전역 변수로 선언
Mat img(500, 900, CV_8UC3, Scalar(255, 255, 255)); // 500x700 크기의 흰색 이미지
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255)); // 이미지 사이즈
string fname; // 파일 이름
Point PtOld; // 마우스 이벤트 처리에 사용될 이전 좌표
Mat morph(Mat img);
Mat bounding_img(Mat img);
Mat gray, bin;
Mat draw_img;
Point getCenterPoint(Mat img);

// 마우스 이벤트를 처리하는 함수
void on_mouse(int event, int x, int y, int flags, void*);

//외곽선 개수 세기
int getCounting_contour(Mat img);

// UI 요소를 그리는 함수
void UI(Mat& img);

int main() {
	// UI 초기화
	UI(img);

	// 창 생성 및 마우스 콜백 함수 등록
	namedWindow("img");
	setMouseCallback("img", on_mouse);

	// 키 입력 대기
	waitKey();
}

// UI 요소를 그리는 함수
void UI(Mat& img)
{
	// 수평선 그리기
	line(img, Point(502, 0), Point(502, 500), Scalar(0, 0, 0), 2);
	line(img, Point(700, 0), Point(700, 500), Scalar(0, 0, 0), 2);
	// 수직선 그리기
	for (int i = 1; i < 5; i++)
	{
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
		line(img, Point(700, 500 * i / 5), Point(900, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	// 사각형 그리기
	rectangle(img, Rect(0, 0, 900, 500), Scalar(0, 0, 0), 2);

	// 버튼 텍스트
	vector<vector<string>> text = { {"Save", "Load", "Clear", "Run", "Exit"}, {"contour", "center"} };
	int font = FONT_HERSHEY_DUPLEX;   // 폰트 종류
	double fontscale = 1.0;   // 폰트 크기
	int thick = 2;   // 글씨 두께
	for (int i = 0; i < text.size(); i++) {
		for (int j = 0; j < text[i].size(); j++) {
			Size Textsize = getTextSize(text[i][j], font, fontscale, thick, 0);   // 글씨 크기
			Size imgsize = img_size.size();   // 객체 사이즈
			Point org(500 + i * 200 + (imgsize.width - Textsize.width) / 2,
				500 * j / 5 + (imgsize.height + Textsize.height) / 2);
			putText(img, text[i][j], org, font, fontscale, Scalar(0, 0, 0), thick);
		}
	}
}

// 마우스 이벤트를 처리하는 함수
void on_mouse(int event, int x, int y, int flags, void*)
{
	// 버튼 영역을 정의하는 사각형 배열
	Rect rect_area[] =
	{
		Rect(0, 0, 495, 495),
		Rect(501, 0, 199, 99),
		Rect(501, 500 / 5 + 1, 199, 99),
		Rect(501, 500 * 2 / 5 + 1, 199, 99),
		Rect(501, 500 * 3 / 5 + 1, 199, 99),
		Rect(501, 500 * 4 / 5 + 1, 199, 99),
		Rect(700, 0, 199, 99),   // contour
		Rect(700, 500 / 5 + 1, 199, 99),   // 무게 중심
		Rect(700, 500 * 2 / 5 + 1, 199, 99),
		Rect(700, 500 * 3 / 5 + 1, 199, 99),
		Rect(700, 500 * 4 / 5 + 1, 199, 99)
	};

	switch (event) {
	case EVENT_LBUTTONDOWN:
		// 왼쪽 마우스 버튼이 눌린 경우
		PtOld = Point(x, y);
		if (rect_area[1].contains(PtOld))
		{
			// "Save" 버튼이 클릭된 경우
			cout << " name to save : ";
			getline(cin, fname);
			imwrite(fname + ".jpg", img);
		}
		else if (rect_area[2].contains(PtOld))
		{
			// "Load" 버튼이 클릭된 경우
			while (true) {
				cout << "load file name(.jpg) : ";
				getline(cin, fname);
				img = imread(fname);
				if (!img.data) {
					// 이미지를 찾을 수 없거나 이름을 잘못 입력한 경우
					cout << "Could not find the image. Make sure you write .jpg" << endl;
				}
				else {
					// 올바른 이미지를 로드한 경우
					imshow("img", img);
					break;
				}
			}
		}
		else if (rect_area[3].contains(PtOld))
		{
			// "Clear" 버튼이 클릭된 경우
			rectangle(img, Rect(2, 2, 497, 496), Scalar(255, 255, 255), -1);
			imshow("img", img);
		}
		else if (rect_area[4].contains(PtOld))
		{
			// "Run" 버튼이 클릭된 경우 (구현되지 않음)
		}
		else if (rect_area[5].contains(PtOld))
		{
			// "Exit" 버튼이 클릭된 경우
			cout << "exit" << endl;
			exit(0);
		}
		else if (rect_area[6].contains(PtOld))
		{
			cout << "contour" << endl;

			int count_contour = getCounting_contour(img);

			cout << "외곽선 개수 : " << count_contour << endl;
			if (count_contour == 1)
			{
				cout << "외곽선 개수: 1 (1, 2, 3, 5, 7)" << endl;
			}
			else if (count_contour == 2) {
				cout << "외곽선 개수: 2 (0, 4, 6, 9)" << endl;
			}
			else if (count_contour == 3) {
				cout << "외곽선 개수 3 (8)" << endl;
			}
			else if (rect_area[7].contains(Point(x, y))) {	//무게중심 비
				cout << "center press" << endl;

				Point center_pt = getCenterPoint(img);

				cout << "X : " << center_pt.x << "%" << endl;
				cout << "Y : " << center_pt.y << "%" << endl;
			}
		}
		break;

	case EVENT_MOUSEMOVE:
		if (rect_area[0].contains(Point(x, y)))
		{
			if (flags & EVENT_FLAG_LBUTTON)
			{
				line(img, PtOld, Point(x, y), Scalar(0, 0, 0), 10);
				imshow("img", img);
				PtOld = Point(x, y);
			}
		}
		break;
	}
	imshow("img", img);
}

int getCounting_contour(Mat img)
{
	bin = morph(img);
	bin = bounding_img(bin);

	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);
	imshow("boundingbox", bin);

	return contours.size();
}

Point getCenterPoint(Mat img) {	//무게중심 좌표
	vector<int> center_res;
	bin = morph(img);
	bin = bounding_img(bin);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	int width = stats.at<int>(1, 2);  // width
	int height = stats.at<int>(1, 3); // height
	int center_x = centroids.at<double>(1, 0); // x
	int center_y = centroids.at<double>(1, 1); // y
	//비율 계산
	int per_x = (double)center_x / width * 100;
	center_res.push_back(per_x);
	int per_y = (double)center_y / height * 100;
	center_res.push_back(per_y);

	cvtColor(bin, bin, COLOR_GRAY2BGR);
	circle(bin, Point(center_x, center_y), 2, Scalar(0, 0, 255), 2, -1);
	imshow("boundingbox", bin);
	return Point(per_x, per_y);
}

Mat bounding_img(Mat img)
{
	Mat labels, stats, centroids;

	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	if (cnt < 2)
	{
		cerr << "Bounding box not found. too small." << endl;
		return Mat();
	}
	int* p = stats.ptr<int>(1);
	bin = bin(Rect(p[0], p[1], p[2], p[3]));

	return bin;
}


Mat morph(Mat img) {	//모폴로지 연산
	draw_img = img(Rect(1, 1, 498, 498));
	cvtColor(draw_img, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	int* p = stats.ptr<int>(1);

	int morph_size = 5;
	if (cnt > 2) {
		while (true) {
			morphologyEx(bin, bin, MORPH_CLOSE, Mat(morph_size, morph_size, CV_8UC1));
			cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
			if (cnt <= 2) break;
			morph_size += 3;
		}
	}
	return bin;
}







