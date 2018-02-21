#pragma once

//#define PI_VERSION

#include "ofMain.h"
#include "ofxMaxim.h"
#ifdef PI_VERSION
#include "ofxGPIO.h"
#endif

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void processSoundVec();
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    void exit();
    void setupRecording();
    
    int		bufferSize;
    int		initialBufferSize; /* buffer size */
    int		sampleRate;

    ofSoundStream soundstream;
    
    double outputs[2];
    
    //processing sound
    maxiSample normSamp;
    maxiSample playbackSound;
    
    //sound recording
    bool recordingOn;
    bool recButton;
    bool playBack;
    vector<float> recorder;
    double bufferCount;
    int recCount;
    
    //loop stuff
    double loopLength;
    double loopBuffers;
    double loopCount;
    
    //PI STUFF
#ifdef      PI_VERSION
    GPIO gpio18;
    GPIO gpio17;
#endif
};


