#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->cap.open("D:\\video\\image19.mp4");
	this->cap_size = cv::Size(320, 180);

	this->number_of_frames = this->cap.get(CV_CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < number_of_frames; i++) {

		cv::Mat src, mini_src;
		this->cap >> src;
		cv::resize(src, mini_src, this->cap_size);
		cv::cvtColor(mini_src, mini_src, CV_BGR2RGB);

		ofImage* image = new ofImage();
		image->allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
		this->images.push_back(image);

		cv::Mat frame = cv::Mat(cv::Size(image->getWidth(), image->getHeight()), CV_MAKETYPE(CV_8UC3, image->getPixels().getNumChannels()), image->getPixels().getData(), 0);
		this->frames.push_back(frame);

		mini_src.copyTo(frame);
		image->update();
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	int radius = 930;
	int deg_span = 20;

	for (int z = -200; z <= 200; z += 200) {

		int noise_deg = ofMap(ofNoise(z * 0.005, ofGetFrameNum() * 0.003), 0, 1, -360, 360);
		for (int deg = 0; deg < 360; deg += deg_span) {

			ofPoint point(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z);

			ofPushMatrix();
			ofTranslate(point);
			ofRotateX(90);
			ofRotateY(deg + 90);

			int images_index = ofMap(ofNoise(point.x * 0.0005, point.y * 0.0005, point.z * 0.0005, ofGetFrameNum() * 0.005), 0, 1, 0, this->number_of_frames);
			this->images[images_index]->draw(0, 0);

			ofPopMatrix();
		}
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}