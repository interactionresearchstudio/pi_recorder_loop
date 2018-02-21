

#include "ofApp.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup(){

#ifdef      PI_VERSION
    gpio18.setup("18");
    gpio18.export_gpio();
    gpio18.setdir_gpio("out");
    gpio17.setup("17");
    gpio17.export_gpio();
    gpio17.setdir_gpio("in");
#endif
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofBackground(0,0,0);
    
    //set sound threshold
    
    loopLength = sampleRate * 4.0;
    loopBuffers = loopLength / bufferSize;
    loopCount = 0;
    
    soundstream.printDeviceList();
    #ifdef PI_VERSION
    soundstream.setDeviceID(2);
    soundstream.setup(this, 2, 1, sampleRate, bufferSize, 4);
    #else
    soundstream.setDeviceID(1);
    soundstream.setup(this, 2, 2, sampleRate, bufferSize, 4);
    #endif
    
    setupRecording();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
#ifdef      PI_VERSION
    playBack = true;
    string state_but;
    gpio17.getval_gpio(state_but);
    
    if(state_but == "1"){
        gpio18.setval_gpio("1");
        recordingOn = true;
    } else {
        gpio18.setval_gpio("0");
        recordingOn = false;
    }

    
#endif
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
}


void ofApp::processSoundVec(){
    
    maxiRecorder rec;
    double frequencyValues = 44100/bufferSize;
    float buffer1[(int)frequencyValues];
    double lengthSamp = recorder.size();
    double sampChunks = lengthSamp/frequencyValues;
    string name = "recording";
    name = name+ofToString(recCount);
    name = name+".wav";
    rec.setup(ofToDataPath(name));
    recCount++;
    rec.startRecording();
    for(double i = 0 ; i < sampChunks; i++){
        double pos = i*frequencyValues;
        for(double playing = 0; playing<frequencyValues; playing++){
            buffer1[(int)playing]=recorder[playing+pos]*10.0;
        }
        rec.passData(buffer1,frequencyValues);
    }
    
    rec.stopRecording();
    rec.saveToWav();
    
}


//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
   
        for (int i = 0; i < bufferSize; i++){
             if(playBack){
                 double wave = recorder[i+(loopCount*bufferSize)];
                 output[i*nChannels] = wave;
                 output[i*nChannels+1] = wave;
        }
    }
  
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    
    
    for(int i = 0; i < bufferSize; i++){
        if(recordingOn){
        recorder[i+(loopCount*bufferSize)] = (recorder[i+(loopCount*bufferSize)]+input[i*nChannels])/2.0;
          //  recorder[i+(loopCount*bufferSize)] = 0;
        }
    }
    loopCount++;
    if(loopCount > loopBuffers){
        loopCount = 0;
    }

    
}

void ofApp::setupRecording(){
        recorder.resize(loopLength);
    loopCount = 0;
   }


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='a'){
        recordingOn = true;
        }
    if(key =='p'){
        playBack =! playBack;
        }
   }

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key =='a'){
        recordingOn = false;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}


void ofApp::exit(){
    cout << "BYE" << endl;
     processSoundVec();
        cout << "CIAO" << endl;
#ifdef PI_VERSION
    gpio17.unexport_gpio();
    gpio18.unexport_gpio();
#endif
}



//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
