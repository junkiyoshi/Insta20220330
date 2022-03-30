#include "ofApp.h"	


//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font_size = 120;

	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	string word = "WAVING";
	auto word_size = glm::vec2(this->font.stringWidth(word), this->font.stringHeight(word));

	auto char_path_list = this->font.getStringAsPoints(word, true, false);
	int sample_count = 120;

	for (int char_index = 0; char_index < char_path_list.size(); char_index++) {

		vector<ofPolyline> outline = char_path_list[char_index].getOutline();

		ofFill();
		ofSetColor(255);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(word_size.x * 0.5, word_size.y * -0.5, 0);
				auto noise_value = ofNoise(location.x * 0.005 + ofGetFrameNum() * 0.025);
				auto value = ofMap(noise_value, 0, 1, 100, -120);

				if (location.y < value) {

					location.y = value;
				}

				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(word_size.x * 0.5, word_size.y * -0.5, 0);
				ofVertex(location);
			}
		}
		ofEndShape(true);
	}
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}