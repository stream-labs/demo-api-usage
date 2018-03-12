#include "json.h"
using json = nlohmann::json;
#include "streamlabsconnectionmanager.h"
#include "jsonhelper.h"
#include <iostream>

void StreamlabsConnectionManager::init(){
    socket = new QTcpSocket(this);

    QObject::connect(socket, &QIODevice::readyRead, [=](){
        qDebug("reading");
        while(socket->canReadLine()){
            auto j = json::parse(socket->readLine());
            std::cout << j <<std::endl;
            auto id = QString::number(GetIntByName(j, "id"));
            if(this->RPC_ID_startStreaming == id){
                qDebug("streaming started");
                emit this->streamingStarted();
            }else if(this->RPC_ID_stopStreaming == id){
                qDebug("streaming stopped");
                emit this->streamingStopped();
            }else if(this->RPC_ID_startRecording == id){
                qDebug("recording started");
                emit this->recordingStarted();
            }else if(this->RPC_ID_stopRecording == id){
                qDebug("recording stopped");
                emit this->recordingStopped();
            }else if(this->RPC_ID_makeCollectionActive == id){
                qDebug("collection activated");
                emit this->collectionActivated();
            }else if(this->RPC_ID_makeSceneActive == id){
                qDebug("scene actived");
                emit this->sceneActivated();
            }else if(this->RPC_ID_hideScene == id){
                qDebug("scene hidden");
                emit this->scenedHidden();
            }else if(this->RPC_ID_showScene == id){
                qDebug("scene shown");
                emit this->sceneShown();
            }else if(this->RPC_ID_muteMixerAudioSource == id){
                qDebug("mixerAudioSource muted");
                emit this->mixerAudioSourceMuted();
            }else if(this->RPC_ID_unmuteMixerAudioSource == id){
                qDebug("mixerAudioSource unmuted");
                emit this->mixerAudioSourceUnmuted();
            }else if(this->RPC_ID_getCollections == id){
                qDebug("collections got");
                emit this->collectionsGot(j);
            }else if(this->RPC_ID_getActiveCollection == id){
                qDebug("active collection got");
                emit this->activeCollectionGot(j);
            }else if(this->RPC_ID_getScenes == id){
                qDebug("scenes got");
                emit this->scenesGot(j);
            }else if(this->RPC_ID_getSources == id){
                qDebug("sources got");
                emit this->sourcesGot(j);
            }else if(this->RPC_ID_getActiveSceneId == id){
                qDebug("activeSceneId got");
                emit this->activeSceneIdGot(j);
            }else if(this->RPC_ID_subscribeToCollectionAdded == id){
                qDebug("collectionAdded subscribed");
            }else if(this->RPC_ID_subscribeToCollectionRemoved == id){
                qDebug("collectionRemoved subscribed");
            }else if(this->RPC_ID_subscribeToCollectionSwitched == id){
                qDebug("collectionSwitched subscribed");
            }else if(this->RPC_ID_subscribeToCollectionUpdated == id){
                qDebug("collectionUpdated subscribed");
            }else if(this->RPC_ID_subscribeToSceneSwitched == id){
                qDebug("sceneSwitched subscribed");
            }else if(this->RPC_ID_subscribeToSceneAdded == id){
                qDebug("sceneAdded subscribed");
            }else if(this->RPC_ID_subscribeToSceneRemoved == id){
                qDebug("sceneRemoved subscribed");
            }else if(this->RPC_ID_subscribeToSouceAdded == id){
                qDebug("sourceAdded subscribed");
            }else if(this->RPC_ID_subscribeToSourceRemoved == id){
                qDebug("sourceRemoved subscribed");
            }else if(this->RPC_ID_subscribeToSourceUpdated == id){
                qDebug("sourceUpdated subscribed");
            }else if(this->RPC_ID_subscribeToItemAdded == id){
                qDebug("itemAdded subscribed");
            }else if(this->RPC_ID_subscribeToItemRemoved == id){
                qDebug("itemRemoved subscribed");
            }else if(this->RPC_ID_subscribeToItemUpdated == id){
                qDebug("itemUpdated subscribed");
            }else if(this->RPC_ID_subscribeToStreamingStateChanged == id){
                qDebug("streaming state subscribed");
            }else if(this->RPC_ID_fetchSceneCollectionsSchema == id){
                qDebug("fetchSceneCollectionsSchema subscribed");
                json resultObject;
                if( GetObjectByName(j, "result", resultObject) ){
                    auto resourceId = GetStringByName(resultObject, "resourceId", "");
                    auto type = GetStringByName(resultObject, "_type", "");
                    this->fetchSceneCollectionsSchemaResourceId = QString::fromStdString(resourceId);
                }
            }

            if(this->fetchSceneCollectionsSchemaResourceId.size() > 0){
                json resultObject;
                if( GetObjectByName(j, "result", resultObject) ){
                    auto resourceId = GetStringByName(resultObject, "resourceId", "");
                    auto type = GetStringByName(resultObject, "_type", "");
                    if(type == "EVENT" && QString::fromStdString(resourceId) == this->fetchSceneCollectionsSchemaResourceId) {
                        qDebug("sceneCollectionsSchema received");
                        this->fetchSceneCollectionsSchemaResourceId = "";
                        //NOTICE!!!! to format result
                        //check this method formatSceneCollectionsSchema
                        j = this->formatSceneCollectionsSchema(j);
                        std::cout<<j<<"\n";
                        emit this->sceneCollectionsSchemaReceived(j);
                    }
                }
            }

            json resultObject;
            if(GetObjectByName(j, "result", resultObject)){
                auto resourceId = GetStringByName(resultObject, "resourceId", "");
                auto type = GetStringByName(resultObject, "_type", "");
                if(type == "EVENT"){
                    if(resourceId == "SceneCollectionsService.collectionAdded"){
                        qDebug("Collection added");
                        emit this->collectionAdded(j);
                    }else if(resourceId == "SceneCollectionsService.collectionRemoved"){
                        qDebug("Collection removed");
                        emit this->collectionRemoved(j);
                    }else if(resourceId == "SceneCollectionsService.collectionSwitched"){
                        qDebug("Collection switched");
                        emit this->collectionSwitched(j);
                    }else if(resourceId == "SceneCollectionsService.collectionSwitched"){
                        qDebug("Collection updated");
                        emit this->collectionUpdated(j);
                    }else if(resourceId == "ScenesService.sceneSwitched"){
                        qDebug("scene Switched");
                        emit this->sceneSwitched(j);
                    }else if(resourceId == "ScenesService.sceneAdded"){
                        qDebug("scene added");
                        emit this->sceneAdded(j);
                    }else if(resourceId == "ScenesService.sceneRemoved"){
                        qDebug("scene removed");
                        emit this->sceneRemoved(j);
                    }else if(resourceId == "SourcesService.sourceAdded"){
                        qDebug("source Added");
                        emit this->sourceAdded(j);
                    }else if(resourceId == "SourcesService.sourceRemoved"){
                        qDebug("source removed");
                        emit this->sourceRemoved(j);
                    }else if(resourceId == "SourcesService.sourceUpdated"){
                        qDebug("source updated");
                        emit this->sourceUpdated(j);
                    }else if(resourceId == "SourcesService.itemAdded"){
                        qDebug("item added");
                        emit this->itemAdded(j);
                    }else if(resourceId == "SourcesService.itemRemoved"){
                        qDebug("item removed");
                        emit this->itemRemoved(j);
                    }else if(resourceId == "SourcesService.itemUpdated"){
                        qDebug("item updated");
                        emit this->itemUpdated(j);
                    }else if (resourceId == "StreamingService.streamingStateChange"){
                        qDebug("streaming state changed");
                        emit this->streamingStateChanged(j);
                    }
                }

            }

        }



    });

    socket->connectToHost("127.0.0.1", 28194);
    if (!socket->waitForConnected(5000))
    {
        qDebug(socket->errorString().toUtf8());
    } else{
        qDebug("connected to slobs!");
    }
}


void StreamlabsConnectionManager::startStreaming()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_startStreaming+", \"method\": \"startStreaming\", \"params\": {   \"resource\": \"StreamingService\"   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::stopStreaming()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_stopStreaming+", \"method\": \"stopStreaming\", \"params\": {   \"resource\": \"StreamingService\"   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::startRecording()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_startRecording+", \"method\": \"startRecording\", \"params\": {   \"resource\": \"StreamingService\"   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::stopRecording()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_stopRecording+", \"method\": \"stopRecording\", \"params\": {   \"resource\": \"StreamingService\"   } }\n";
    socket->write(str.toStdString().c_str());
}

//events
void StreamlabsConnectionManager::subscribeToCollectionAdded()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToCollectionAdded+", \"method\": \"collectionAdded\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToCollectionRemoved()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToCollectionRemoved+", \"method\": \"collectionRemoved\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToCollectionSwitched()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToCollectionSwitched+", \"method\": \"collectionSwitched\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToCollectionUpdated()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToCollectionSwitched+", \"method\": \"collectionUpdated\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSceneSwitched()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSceneSwitched+", \"method\": \"sceneSwitched\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSceneAdded()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSceneAdded+", \"method\": \"sceneAdded\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSceneRemoved()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSceneRemoved+", \"method\": \"sceneRemoved\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSouceAdded()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSouceAdded+", \"method\": \"sourceAdded\", \"params\": {   \"resource\": \"SourcesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSourceRemoved()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSourceRemoved+", \"method\": \"sourceRemoved\", \"params\": {   \"resource\": \"SourcesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToSourceUpdated()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToSourceUpdated+", \"method\": \"sourceUpdated\", \"params\": {   \"resource\": \"SourcesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToItemAdded()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToItemAdded+", \"method\": \"itemAdded\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}
void StreamlabsConnectionManager::subscribeToItemRemoved()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToItemRemoved+", \"method\": \"itemRemoved\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}
void StreamlabsConnectionManager::subscribeToItemUpdated()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToItemUpdated+", \"method\": \"itemUpdated\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::subscribeToStreamingStateChanged()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_subscribeToStreamingStateChanged+", \"method\": \"streamingStateChange\", \"params\": {   \"resource\": \"StreamingService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());
}
//end events

void StreamlabsConnectionManager::fetchSceneCollectionsSchema()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_fetchSceneCollectionsSchema+", \"method\": \"fetchSceneCollectionsSchema\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []} }\n";
    socket->write(str.toStdString().c_str());

}

json StreamlabsConnectionManager::formatSceneCollectionsSchema(const json &j)
{
    json resultObject;
    json dataArray;
    if( GetObjectByName(j, "result", resultObject) ){
        //std::cout<< resultObject << "\n";

        if( GetArrayByName(resultObject, "data", dataArray) ) {
            for (json::iterator it = dataArray.begin(); it != dataArray.end(); ++it) {

               json sourcesArray;
               if( GetArrayByName(*it, "sources", sourcesArray) ) {

               }
               json scenesArray;
               std::list<json> c_list;
               int mixerAudioSourceAdded = false;
               if( GetArrayByName(*it, "scenes", scenesArray) ) {
                   //std::cout<< scenesArray << "\n";
                   json sceneItemsArray;
                   for(json::iterator itScenesArr = scenesArray.begin(); itScenesArr != scenesArray.end(); ++itScenesArr) {
                        if( GetArrayByName(*itScenesArr, "sceneItems", sceneItemsArray) ) {
                            for(json::iterator itSceneItem = sceneItemsArray.begin(); itSceneItem != sceneItemsArray.end(); ++itSceneItem){
                                auto sourceId = GetStringByName(*itSceneItem, "sourceId", "");
                                if(sourcesArray.size() > 0) {
                                    for (json::iterator itSourcesArray = sourcesArray.begin(); itSourcesArray != sourcesArray.end(); ++itSourcesArray ) {
                                        auto id = GetStringByName((*itSourcesArray), "id", "");
                                        auto name = GetStringByName((*itSourcesArray), "name", "");
                                        auto type = GetStringByName((*itSourcesArray), "type", "");
                                        if(sourceId == id){
                                            (*itSceneItem)["name"] = name;
                                            (*itSceneItem)["type"] = type;
                                        }
                                        if(false == mixerAudioSourceAdded && nullptr != strstr(type.c_str(), "wasapi")) {
                                            //mixerAudioSource
                                            c_list.push_back(*itSourcesArray);
                                        }
                                    }
                                    mixerAudioSourceAdded = true;
                                }

                            }
                           (*itScenesArr)["sceneItems"] = sceneItemsArray;
                        }
                   }
               }
               json j_flist(c_list);
               (*it)["mixerAudioSources"] = j_flist;
               c_list.clear();
               (*it)["scenes"] = scenesArray;
            }
            //std::cout<<dataArray<<"\n";
        }

    }
    return dataArray;

}

void StreamlabsConnectionManager::muteMixerAudioSource(const QString & sourceId)
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_muteMixerAudioSource+", \"method\": \"setMuted\", \"params\": {   \"resource\": \"AudioSource[\\\""+ sourceId + "\\\"]\", \"args\": [true]   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::unmuteMixerAudioSource(const QString & sourceId)
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_unmuteMixerAudioSource+", \"method\": \"setMuted\", \"params\": {   \"resource\": \"AudioSource[\\\""+ sourceId + "\\\"]\", \"args\": [false]   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::hideScene(const QString& sceneId, const QString& sceneItemId, const QString& sourceId)
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_hideScene+", \"method\": \"setVisibility\", \"params\": {   \"resource\": \"SceneItem[\\\""+sceneId+"\\\",\\\""+sceneItemId+"\\\",\\\""+sourceId+"\\\"]\", \"args\": [false]   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::showScene(const QString& sceneId, const QString& sceneItemId, const QString& sourceId)
{

    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_showScene+", \"method\": \"setVisibility\", \"params\": {   \"resource\": \"SceneItem[\\\""+sceneId+"\\\",\\\""+sceneItemId+"\\\",\\\""+sourceId+"\\\"]\", \"args\": [true]   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::getScenes()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_getScenes+", \"method\": \"getScenes\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::makeSceneActive(const QString& sceneId)
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_makeSceneActive+", \"method\": \"makeSceneActive\", \"params\": {   \"resource\": \"ScenesService\", \"args\": [\"" + sceneId +"\"]   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::getActiveSceneId()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_getActiveSceneId+", \"method\": \"activeSceneId\", \"params\": {   \"resource\": \"ScenesService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::getSources()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_getSources+", \"method\": \"getSources\", \"params\": {   \"resource\": \"SourcesService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}
void StreamlabsConnectionManager::getCollections()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_getCollections+", \"method\": \"collections\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::getActiveCollection()
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_getActiveCollection+", \"method\": \"activeCollection\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": []   } }\n";
    socket->write(str.toStdString().c_str());
}

void StreamlabsConnectionManager::makeCollectionActive(const QString& collectionId)
{
    QString str = "{\"jsonrpc\": \"2.0\", \"id\": "+this->RPC_ID_makeCollectionActive+", \"method\": \"load\", \"params\": {   \"resource\": \"SceneCollectionsService\", \"args\": [\"" + collectionId +"\"]   } }\n";
    socket->write(str.toStdString().c_str());
}

