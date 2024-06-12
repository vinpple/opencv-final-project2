
/*
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img(500, 900, CV_8U, Scalar(255, 255, 255));
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255));
string fname;
Point PtOld;
void on_mouse(int event, int x, int y, int flags, void*);
void UI(Mat& img);
int main()
{
	UI(img);
	namedWindow("img");
	setMouseCallback("img", on_mouse);
	waitKey();
}

void UI(Mat&img)
{
	line(img, Point(500, 0), Point(500, 500), Scalar(0, 0, 0), 2);
	for (int i = 1; i < 5; i++)
	{
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	rectangle(img, Rect(0, 0, 700, 500), Scalar(0, 0, 0), 2);

	string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontface = FONT_HERSHEY_SCRIPT_COMPLEX;
	double fontscale = 1;
	int thick = 2;

	for (int i = 0; i < 5; i++) {
		Size sizetext = getTextSize(text[i], fontface, fontscale, thick, 0);
		Size sizeimg = img_size.size();
		Point org(500 + (sizeimg.width - sizetext.width) / 2,
			500 * i / 5 + (sizeimg.height + sizetext.height) / 2);
		putText(img, text[i], org, fontface, fontscale, Scalar(0, 0, 0), thick);
	}
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	Rect rect_area[] =
	{
		Rect(0, 0, 495, 495),
		Rect(501, 0, 199, 99),
		Rect(501, 500 / 5 + 1, 199, 99),
		Rect(501, 500 * 2 / 5 + 1, 199, 99),
		Rect(501, 500 * 3 / 5 + 1, 199, 99),
		Rect(501, 500 * 4 / 5 + 1, 199, 99)
		Rect(700, 0, 199, 99),	//6
		Rect(700, 500 / 5 + 1, 199, 99),	//7.
		Rect(700, 500 * 2 / 5 + 1, 199, 99),	//8.
		Rect(700, 500 * 3 / 5 + 1, 199, 99),	//9.

	};
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		PtOld = Point(x, y);
			if (rect_area[1].contains(PtOld))
			{
				cout << " name to save : ";
				getline(cin, fname);
				imwrite(fname+".jpg", img);
			}
			else if (rect_area[2].contains(PtOld))
			{
				while (true) {
					cout << "load file name(.jpg) : ";
					getline(cin, fname);
					img = imread(fname);
					if (!img.data) {
						cout << "Could not find the image. Make sure you write .jpg" << endl;
					}
					else {
						imshow("img", img);
						break;
					}
				}
			}
			else if (rect_area[3].contains(PtOld))
			{
				rectangle(img, Rect(2, 2, 497, 496), Scalar(255, 255, 255), -1);
				imshow("img", img);
			}
			else if (rect_area[4].contains(PtOld))
			{

			}
			else if (rect_area[5].contains(PtOld))
			{
				cout << "exit" << endl;
				exit(0);
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
*/





/*
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// �̹����� ���� �̸��� ������ �������� ���� ������ ����
Mat img(500, 900, CV_8U, Scalar(255, 255, 255)); // 500x700 ũ���� ��� �̹���
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255)); // �̹��� ������
string fname; // ���� �̸�
Point PtOld; // ���콺 �̺�Ʈ ó���� ���� ���� ��ǥ
Mat morph(Mat img);
Mat bounding_img(Mat img);
Mat gray, bin;


// ���콺 �̺�Ʈ�� ó���ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*);

//�ܰ��� ���� ����
int getCounting_contour(Mat img);

// UI ��Ҹ� �׸��� �Լ�
void UI(Mat& img);

int main() {
	// UI �ʱ�ȭ
	UI(img);

	// â ���� �� ���콺 �ݹ� �Լ� ���
	namedWindow("img");
	setMouseCallback("img", on_mouse);

	// Ű �Է� ���
	waitKey();
}

// UI ��Ҹ� �׸��� �Լ�
void UI(Mat& img)
{
	// ���� �׸���
	line(img, Point(502, 0), Point(502, 500), Scalar(0, 0, 0), 2);
	line(img, Point(700, 0), Point(700, 500), Scalar(0, 0, 0), 2);
	// ������ �׸���
	for (int i = 1; i < 5; i++)
	{
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
		line(img, Point(700, 500 * i / 5), Point(900, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	// �簢�� �׸���
	rectangle(img, Rect(0, 0, 900, 500), Scalar(0, 0, 0), 2);

	// ��ư �ؽ�Ʈ
	//string text[] = { "Save", "Load", "Clear", "Run", "Exit", "countour", "center"};
	vector<vector<string>> text = { {"Save", "Load", "Clear", "Run", "Exit"}, {"contour", "center"} };
	int font =FONT_HERSHEY_DUPLEX;	//��Ʈ ����
	double fontscale = 1.0;	//��Ʈ ũ��
	int thick = 2;	//�۾� �β�
	for (int i = 0; i < text.size(); i++) {
		for (int j = 0; j < text[i].size(); j++) {
			Size Textsize = getTextSize(text[i][j], font, fontscale, thick, 0);	//�۾� ũ��
			Size imgsize = img_size.size();	//��ü ������
			Point org(500 + i * 200 + (imgsize.width - Textsize.width) / 2,
				500 * j / 5 + (imgsize.height + Textsize.height) / 2);
			putText(img, text[i][j], org, font, fontscale, Scalar(0, 0, 0), thick);
		}
	}
}


// ���콺 �̺�Ʈ�� ó���ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*)
{
	// ��ư ������ �����ϴ� �簢�� �迭
	Rect rect_area[] =
	{
		Rect(0, 0, 495, 495),
		Rect(501, 0, 199, 99),
		Rect(501, 500 / 5 + 1, 199, 99),
		Rect(501, 500 * 2 / 5 + 1, 199, 99),
		Rect(501, 500 * 3 / 5 + 1, 199, 99),
		Rect(501, 500 * 4 / 5 + 1, 199, 99),
		Rect(700, 0, 199, 99),   //contour
		Rect(700, 500 / 5 + 1, 199, 99),   //���� �߽�
		Rect(700, 500 * 2 / 5 + 1, 199, 99),
		Rect(700, 500 * 3 / 5 + 1, 199, 99),
		Rect(700, 500 * 4 / 5 + 1, 199, 99)

	};

	switch (event) {
	case EVENT_LBUTTONDOWN:
		// ���� ���콺 ��ư�� ���� ���
		PtOld = Point(x, y);
		if (rect_area[1].contains(PtOld))
		{
			// "Save" ��ư�� Ŭ���� ���
			cout << " name to save : ";
			getline(cin, fname);
			imwrite(fname + ".jpg", img);
		}
		else if (rect_area[2].contains(PtOld))
		{
			// "Load" ��ư�� Ŭ���� ���
			while (true) {
				cout << "load file name(.jpg) : ";
				getline(cin, fname);
				img = imread(fname);
				if (!img.data) {
					// �̹����� ã�� �� ���ų� �̸��� �߸� �Է��� ���
					cout << "Could not find the image. Make sure you write .jpg" << endl;
				}
				else {
					// �ùٸ� �̹����� �ε��� ���
					imshow("img", img);
					break;
				}
			}
		}
		else if (rect_area[3].contains(PtOld))
		{
			// "Clear" ��ư�� Ŭ���� ���
			rectangle(img, Rect(2, 2, 497, 496), Scalar(255, 255, 255), -1);
			imshow("img", img);
		}
		else if (rect_area[4].contains(PtOld))
		{
			// "Run" ��ư�� Ŭ���� ��� (�������� ����)
		}
		else if (rect_area[5].contains(PtOld))
		{
			// "Exit" ��ư�� Ŭ���� ���
			cout << "exit" << endl;
			exit(0);
		}
		else if (rect_area[6].contains(PtOld))
		{
			cout << "contour" << endl;

			int count_contour = getCounting_contour(img);

			cout << "�ܰ��� ���� : " << count_contour << endl;
			if (count_contour == 1)
			{
				cout << "�ܰ��� ����: 1 (1, 2, 3, 5, 7)" << endl;
			}
			else if (count_contour == 2) {
				cout << "�ܰ��� ����: 2 (0, 4, 6, 9)" << endl;
			}
			else if (count_contour == 3) {
				cout << "�ܰ��� ���� 3 (8)" << endl;
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


Mat morph(Mat img)
{
	cvtColor(img(Rect(0,0,500,500)), gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	int* p = stats.ptr<int>(1);

	int rows = (p[0] + p[2]) / 8;	//10�� ������ ��
	int cols = (p[1] + p[3]) / 8;

	int morph_size = 2;
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

Mat bounding_img(Mat img)
{
	bin = morph(img);
	Mat labels, stats, centroids;

	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	if (cnt < 2)
	{
		cerr << "Bounding box not found. Possibly too small." << endl;
		return Mat();
	}
	int* p = stats.ptr<int>(1);
	bin= bin(Rect(p[0], p[1], p[2], p[3]));
	imshow("bin", bin);

	return bin;
}
*/

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// �̹����� ���� �̸��� ������ �������� ���� ������ ����
Mat img(500, 900, CV_8UC3, Scalar(255, 255, 255)); // 500x700 ũ���� ��� �̹���
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255)); // �̹��� ������
string fname; // ���� �̸�
Point PtOld; // ���콺 �̺�Ʈ ó���� ���� ���� ��ǥ
Mat morph(Mat img);
Mat bounding_img(Mat img);
Mat gray, bin;
Mat draw_img;
Point getCenterPoint(Mat img);

// ���콺 �̺�Ʈ�� ó���ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*);

//�ܰ��� ���� ����
int getCounting_contour(Mat img);

// UI ��Ҹ� �׸��� �Լ�
void UI(Mat& img);

int main() {
	// UI �ʱ�ȭ
	UI(img);

	// â ���� �� ���콺 �ݹ� �Լ� ���
	namedWindow("img");
	setMouseCallback("img", on_mouse);

	// Ű �Է� ���
	waitKey();
}

// UI ��Ҹ� �׸��� �Լ�
void UI(Mat& img)
{
	// ���� �׸���
	line(img, Point(502, 0), Point(502, 500), Scalar(0, 0, 0), 2);
	line(img, Point(700, 0), Point(700, 500), Scalar(0, 0, 0), 2);
	// ������ �׸���
	for (int i = 1; i < 5; i++)
	{
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
		line(img, Point(700, 500 * i / 5), Point(900, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	// �簢�� �׸���
	rectangle(img, Rect(0, 0, 900, 500), Scalar(0, 0, 0), 2);

	// ��ư �ؽ�Ʈ
	vector<vector<string>> text = { {"Save", "Load", "Clear", "Run", "Exit"}, {"contour", "center"} };
	int font = FONT_HERSHEY_DUPLEX;   // ��Ʈ ����
	double fontscale = 1.0;   // ��Ʈ ũ��
	int thick = 2;   // �۾� �β�
	for (int i = 0; i < text.size(); i++) {
		for (int j = 0; j < text[i].size(); j++) {
			Size Textsize = getTextSize(text[i][j], font, fontscale, thick, 0);   // �۾� ũ��
			Size imgsize = img_size.size();   // ��ü ������
			Point org(500 + i * 200 + (imgsize.width - Textsize.width) / 2,
				500 * j / 5 + (imgsize.height + Textsize.height) / 2);
			putText(img, text[i][j], org, font, fontscale, Scalar(0, 0, 0), thick);
		}
	}
}

// ���콺 �̺�Ʈ�� ó���ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*)
{
	// ��ư ������ �����ϴ� �簢�� �迭
	Rect rect_area[] =
	{
		Rect(0, 0, 495, 495),
		Rect(501, 0, 199, 99),
		Rect(501, 500 / 5 + 1, 199, 99),
		Rect(501, 500 * 2 / 5 + 1, 199, 99),
		Rect(501, 500 * 3 / 5 + 1, 199, 99),
		Rect(501, 500 * 4 / 5 + 1, 199, 99),
		Rect(700, 0, 199, 99),   // contour
		Rect(700, 500 / 5 + 1, 199, 99),   // ���� �߽�
		Rect(700, 500 * 2 / 5 + 1, 199, 99),
		Rect(700, 500 * 3 / 5 + 1, 199, 99),
		Rect(700, 500 * 4 / 5 + 1, 199, 99)
	};

	switch (event) {
	case EVENT_LBUTTONDOWN:
		// ���� ���콺 ��ư�� ���� ���
		PtOld = Point(x, y);
		if (rect_area[1].contains(PtOld))
		{
			// "Save" ��ư�� Ŭ���� ���
			cout << " name to save : ";
			getline(cin, fname);
			imwrite(fname + ".jpg", img);
		}
		else if (rect_area[2].contains(PtOld))
		{
			// "Load" ��ư�� Ŭ���� ���
			while (true) {
				cout << "load file name(.jpg) : ";
				getline(cin, fname);
				img = imread(fname);
				if (!img.data) {
					// �̹����� ã�� �� ���ų� �̸��� �߸� �Է��� ���
					cout << "Could not find the image. Make sure you write .jpg" << endl;
				}
				else {
					// �ùٸ� �̹����� �ε��� ���
					imshow("img", img);
					break;
				}
			}
		}
		else if (rect_area[3].contains(PtOld))
		{
			// "Clear" ��ư�� Ŭ���� ���
			rectangle(img, Rect(2, 2, 497, 496), Scalar(255, 255, 255), -1);
			imshow("img", img);
		}
		else if (rect_area[4].contains(PtOld))
		{
			// "Run" ��ư�� Ŭ���� ��� (�������� ����)
		}
		else if (rect_area[5].contains(PtOld))
		{
			// "Exit" ��ư�� Ŭ���� ���
			cout << "exit" << endl;
			exit(0);
		}
		else if (rect_area[6].contains(PtOld))
		{
			cout << "contour" << endl;

			int count_contour = getCounting_contour(img);

			cout << "�ܰ��� ���� : " << count_contour << endl;
			if (count_contour == 1)
			{
				cout << "�ܰ��� ����: 1 (1, 2, 3, 5, 7)" << endl;
			}
			else if (count_contour == 2) {
				cout << "�ܰ��� ����: 2 (0, 4, 6, 9)" << endl;
			}
			else if (count_contour == 3) {
				cout << "�ܰ��� ���� 3 (8)" << endl;
			}
			else if (rect_area[7].contains(Point(x, y))) {	//�����߽� ��
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

Point getCenterPoint(Mat img) {	//�����߽� ��ǥ ��
	vector<int> center_res;
	bin = morph(img);
	bin = bounding_img(bin);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	int width = stats.at<int>(1, 2);  // width
	int height = stats.at<int>(1, 3); // height
	int center_x = centroids.at<double>(1, 0); // �����߽� x��ǥ
	int center_y = centroids.at<double>(1, 1); // �����߽� y��ǥ
	//���� ���
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


Mat morph(Mat img) {	//�������� ����
	draw_img = img(Rect(0, 0, 500, 500));
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







