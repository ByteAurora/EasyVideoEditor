#pragma once

#include <string>
#include <list>
#include "Command.h"
#include "Resource.h"
#include "Image.h"
#include "Video.h"
#include "Frame.h"

/*
* @version  v1.0.0
* @author   Sohn Young Jin
* @since    v1.0.0
* 
* The EveProject class is a class of the singleton pattern that is created when the program is executed.
* All frame objects currently being modified in the program and resource(videos, images) being used are managed in a list.
*/
class EveProject
{
private:
    // Instance of EveProject.
    static EveProject* instance;

    // List of all videos resources in use.
    std::list<Video*> videoList;

    // List of all images resources in use.
    std::list<Image*> imageList;

    // List of all frames being editing.
    std::list<Frame*> frameList;

    // Frame number currently being displayed.
    int currentFrameNumber;
private:
    // Default constructor.
    EveProject();
    // Default destructor.
    ~EveProject();
public:
    // Get instance of EveProject class.
    static EveProject* getInstance();

    // Add video resource into video list.
    void addVideo(Video* video);
    // Get video resource from video list.
    Video* getVideo(int index);

    // Add image resource into image list.
    void addImage(Image* image);
    // Get image resource from image list.
    Image* getImage(int index);

    // Add frame into frame list.
    void addFrame(Frame* frame);
    // Get frame from frame list.
    Frame* getFrame(int index);

    // Remove frame from frame list.
    void removeFrame(int index);
    // Remove frames from frame list.
    void removeFrames(int index, int count);

    // Get current frame pointer.
    Frame* getCurrentFrame();
    // Get current frame pointer and change current frame number to the next frame.
    Frame* getCurrentFrameAndUpdate();

    // Get fps from first resource in video list.
    int getBaseFps();
    // Get delay from first resource in video list.
    int getBaseDelay();
    // Get frame count from first resource in video list.
    int getBaseFrameCount();
    // Get width from first resource in video list.
    int getBaseWidth();
    // Get height from first resource in video list.
    int getBaseHeight();

    // Points to the next frame.
    bool forward1Frame();
    // Points to the previous frame.
    bool backward1Frame();
    // Points the frames 5 seconds later.
    bool forward5Seconds();
    // Points the frames 5 seconds ago.
    bool backward5Seconds();
public:
    // Frame list setter.
    void setFrameList(std::list<Frame*> frameList);
    // Frame list getter.
    std::list<Frame*>* getFrameList();

    // Current frame number setter.
    void setCurrentFrameNumber(int frameNumber);
    // Current frame number getter.
    int getCurrentFrameNumber();
};

