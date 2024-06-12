
https://youtu.be/eZtCvv4RNvE?si=__MCgM1A17ZDdMrV


1. 외곽선 개수 구하기

		int getCounting_contour(Mat img)
		{
			bin = morph(img);
			bin = bounding_img(bin);
		
			vector<vector<Point>> contours;
			findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);
			imshow("boundingbox", bin);
		
			return contours.size();
		}

2. 무게 중심 좌표 비율 구하기

		Point getCenterPoint(Mat img)
		{
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

  3. 바운딩 박스의 중점과 무게 중심의 높이 차이를 비교
     -6, 9, 0 비교


  5. 무게 중심을 기준으로 가로 세로 나누고 비교
