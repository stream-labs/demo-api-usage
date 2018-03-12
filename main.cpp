#include <QCoreApplication>
#include <QIODevice>
#include <QLocalSocket>
#include <QObject>
#include "streamlabsconnectionmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    StreamlabsConnectionManager* sl = StreamlabsConnectionManager::getInstance();
//    sl->fetchSceneCollectionsSchema();

//    sl->startStreaming();
//    sl->stopStreaming();
//    sl->startRecording();
//    sl->stopRecording();


//    sl->makeCollectionActive("ba1df9fd-0b1a-42a1-b2a3-829b3894b01e");
//    sl->makeSceneActive("scene_d59836d3-f2ac-491e-848d-a732c5a07d97");

//    sl->hideScene("scene_d59836d3-f2ac-491e-848d-a732c5a07d97", "770d64dc-ffd8-467c-b9e4-ebbfaa5b6027",  "browser_source_633a58ac-2da8-415c-9820-b0793fd23714");
//    sl->showScene("scene_d59836d3-f2ac-491e-848d-a732c5a07d97", "770d64dc-ffd8-467c-b9e4-ebbfaa5b6027",  "browser_source_633a58ac-2da8-415c-9820-b0793fd23714");

//    sl->muteMixerAudioSource("wasapi_output_capture_cd14c7c9-c1e7-472f-96ee-3233348a59dd");
//    sl->unmuteMixerAudioSource("wasapi_output_capture_cd14c7c9-c1e7-472f-96ee-3233348a59dd");

//    sl->subscribeToSceneSwitched();
//    sl->subscribeToSceneAdded();
//    sl->subscribeToSceneRemoved();


    sl->subscribeToSouceAdded();
    sl->subscribeToSourceRemoved();
    sl->subscribeToSourceUpdated();

//    sl->subscribeToItemAdded();
//    sl->subscribeToItemRemoved();
//    sl->subscribeToItemUpdated();
//    sl->subscribeToStreamingStateChanged();
//    sl->getCollections();
//      sl->getActiveCollection();
      sl->subscribeToCollectionAdded();
      sl->subscribeToCollectionRemoved();
      sl->subscribeToCollectionSwitched();
      sl->subscribeToCollectionUpdated();
//    sl->getScenes();
//    sl->getSources();
//    sl->getActiveSceneId();

    return a.exec();
}
