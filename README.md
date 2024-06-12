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
