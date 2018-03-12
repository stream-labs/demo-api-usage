#ifndef STREAMLABSCONNECTIONMANAGER_H
#define STREAMLABSCONNECTIONMANAGER_H
#include <qtcpsocket.h>
#include "json.h"
using json = nlohmann::json;
class QLocalSocket;

class StreamlabsConnectionManager : public QObject
{
    Q_OBJECT

public:
    const QString RPC_ID_startStreaming = "1";
    const QString RPC_ID_stopStreaming = "2";
    const QString RPC_ID_startRecording = "3";
    const QString RPC_ID_stopRecording = "4";
    const QString RPC_ID_getCollections = "5";
    const QString RPC_ID_makeCollectionActive = "6";
    const QString RPC_ID_fetchSceneCollectionsSchema = "8";
    const QString RPC_ID_getScenes = "9";
    const QString RPC_ID_getSources = "10";
    const QString RPC_ID_makeSceneActive = "11";
    const QString RPC_ID_getActiveSceneId = "12";
    const QString RPC_ID_muteMixerAudioSource = "13";
    const QString RPC_ID_unmuteMixerAudioSource = "14";
    const QString RPC_ID_hideScene = "15";
    const QString RPC_ID_showScene = "16";
    const QString RPC_ID_subscribeToSceneSwitched = "17";
    const QString RPC_ID_subscribeToSceneAdded = "18";
    const QString RPC_ID_subscribeToSceneRemoved = "19";
    const QString RPC_ID_subscribeToSouceAdded = "20";
    const QString RPC_ID_subscribeToSourceRemoved = "21";
    const QString RPC_ID_subscribeToSourceUpdated = "22";
    const QString RPC_ID_subscribeToItemAdded = "23";
    const QString RPC_ID_subscribeToItemRemoved = "24";
    const QString RPC_ID_subscribeToItemUpdated = "25";
    const QString RPC_ID_subscribeToStreamingStateChanged = "26";
    const QString RPC_ID_getActiveCollection = "27";
    const QString RPC_ID_subscribeToCollectionAdded = "28";
    const QString RPC_ID_subscribeToCollectionRemoved = "29";
    const QString RPC_ID_subscribeToCollectionSwitched = "30";
    const QString RPC_ID_subscribeToCollectionUpdated = "31";
    QString fetchSceneCollectionsSchemaResourceId = "";
    static StreamlabsConnectionManager* getInstance()
    {
        static StreamlabsConnectionManager* sStreamlabsConnectionManager = nullptr;
        if (sStreamlabsConnectionManager == nullptr)
        {
            sStreamlabsConnectionManager = new StreamlabsConnectionManager();
            sStreamlabsConnectionManager->init();
        }
        return sStreamlabsConnectionManager;
    }
    void startStreaming();
    void stopStreaming();
    void startRecording();
    void stopRecording();

    void getCollections();
    void getActiveCollection();
    void makeCollectionActive(const QString & collectionId);
    
    void fetchSceneCollectionsSchema();
    json formatSceneCollectionsSchema(const json & j);

    void getScenes();
    void getSources();
    void makeSceneActive(const QString & sceneId);
    void getActiveSceneId();

    //audio
    void muteMixerAudioSource(const QString & sourceId);
    void unmuteMixerAudioSource(const QString & sourceId);
    void getAudioSources();

    //scene
    void hideScene(const QString& sceneId, const QString& sceneItemId, const QString& sourceId);
    void showScene(const QString& sceneId, const QString& sceneItemId, const QString& sourceId);

    //events
    void subscribeToSceneSwitched();
    void subscribeToSceneAdded();
    void subscribeToSceneRemoved();
    void subscribeToSouceAdded();
    void subscribeToSourceRemoved();
    void subscribeToSourceUpdated();
    void subscribeToItemAdded();
    void subscribeToItemRemoved();
    void subscribeToItemUpdated();
    void subscribeToStreamingStateChanged();
    void subscribeToCollectionAdded();
    void subscribeToCollectionRemoved();
    void subscribeToCollectionSwitched();
    void subscribeToCollectionUpdated();
public slots:

signals:
    void sceneCollectionsSchemaReceived(json& j);
    void streamingStarted();
    void streamingStopped();
    void recordingStarted();
    void recordingStopped();
    void collectionActivated();
    void sceneActivated();
    void scenedHidden();
    void sceneShown();
    void mixerAudioSourceMuted();
    void mixerAudioSourceUnmuted();

    void collectionAdded(json& j);
    void collectionRemoved(json& j);
    void collectionSwitched(json& j);
    void collectionUpdated(json& j);
    void sceneSwitched(json& j);
    void sceneAdded(json& j);
    void sceneRemoved(json& j);
    void sourceAdded(json& j);
    void sourceRemoved(json& j);
    void sourceUpdated(json& j);
    void itemAdded(json& j);
    void itemRemoved(json& j);
    void itemUpdated(json& j);

    void collectionsGot(json& j);
    void activeCollectionGot(json& j);
    void scenesGot(json& j);
    void sourcesGot(json& j);
    void activeSceneIdGot(json& j);
    void streamingStateChanged(json& j);

private:
    QTcpSocket *socket;
    void init();
    StreamlabsConnectionManager(){}
    StreamlabsConnectionManager(StreamlabsConnectionManager const&);
    void operator=(StreamlabsConnectionManager const&);
};

#endif // STREAMLABSCONNECTIONMANAGER_H
