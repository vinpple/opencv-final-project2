
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

 3. 바운딩 박스 구하기

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
    
  4. 무게 중심을 기준으로 X축 과 Y축 으로 나누었을 때 각 축별 외곽선의 개수
		Point Counting_xycontour(Mat img) {
			draw_img = img(Rect(0, 0, 500, 500));
			
			
			morphologyEx(bin, bin, MORPH_CLOSE, Mat(5, 20, CV_8UC1));
			bin = bounding_img(~bin);
			bin = ~draw_img;
			int cols_count = 0;
		
			for (int i = 1; i < bin.cols; i++) {
				Mat l_dst = bin(Rect(0, 0, i, bin.rows));	
				vector<vector<Point>> contours1, contours2;
				findContours(l_dst, contours1, RETR_LIST, CHAIN_APPROX_NONE);
				Mat r_dst = bin(Rect(i, 0, bin.cols - i, bin.rows));	

				findContours(r_dst, contours2, RETR_LIST, CHAIN_APPROX_NONE);
				if (cols_count < contours1.size() + contours2.size()) cols_count = contours1.size() + contours2.size();
			}
			int rows_count = 0;
			for (int i = 1; i < bin.rows; i++) {
				Mat u_dst = bin(Rect(0, 0, bin.cols, i));
				vector<vector<Point>> contours1, contours2;
				findContours(u_dst, contours1, RETR_LIST, CHAIN_APPROX_NONE);
				Mat d_dst = bin(Rect(0, i, bin.cols, bin.rows - i));

				findContours(d_dst, contours2, RETR_LIST, CHAIN_APPROX_NONE);
				if (rows_count < contours1.size() + contours2.size()) rows_count = contours1.size() + contours2.size();
			}
			imshow("boundingbox", bin);
			return Point(cols_count, rows_count);
		}

  6. 무게 중심을 기준으로 x축 y축으로 나누고 비교
		tuple<int, int, int, int> PixelCount(Mat img) {
			draw_img = img(Rect(0, 0, 500, 500));
			bin = ~draw_img;
			morphologyEx(bin, bin, MORPH_CLOSE, Mat(5, 20, CV_8UC1));
			bin = bounding_img(~bin);
		
			Mat labels, stats, centroids;
			
			int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
			int center_x = stats.at<int>(0, 2) / 2; // 중심 x좌표
			int center_y = stats.at<int>(0, 3) / 2; // 중심 y좌표
		
			int draw_pixel_count = 0, background_pixel_count = 0;
			int l_pixel_count = 0, r_pixel_count = 0, u_pixel_count = 0, d_pixel_count = 0;
			
			for (int i = 0; i < bin.rows; i++) {
				for (int j = 0; j < bin.cols; j++) {
					if (bin.at<uchar>(i, j) == 255) draw_pixel_count++;	//전체 픽셀 수
		
					if (i >= 0 && i < center_y && bin.at<uchar>(i, j) == 255) u_pixel_count++;	
					else if (i > center_y && i <= bin.rows && bin.at<uchar>(i, j) == 255) d_pixel_count++;	
		
					if (j >= 0 && j < center_x && bin.at<uchar>(i, j) == 255) l_pixel_count++;	
					else if (j > center_x && j <= bin.cols && bin.at<uchar>(i, j) == 255) r_pixel_count++;	
				}
			}
			int u_count, d_count, l_count, r_count;
			u_count = (double)u_pixel_count / (u_pixel_count + d_pixel_count) * 100;
			d_count = (double)d_pixel_count / (u_pixel_count + d_pixel_count) * 100;
			l_count = (double)l_pixel_count / (l_pixel_count + r_pixel_count) * 100;
			r_count = (double)r_pixel_count / (l_pixel_count + r_pixel_count) * 100;
			
			imshow("boundingbox", bin);
		
			return make_tuple(u_count, d_count, l_count, r_count);
		}
