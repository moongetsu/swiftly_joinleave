#include <swiftly/swiftly.h>
#include <swiftly/gameevents.h>
#include <swiftly/server.h>
#include <swiftly/logger.h>
#include <swiftly/configuration.h>

Configuration *config = nullptr;
Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Logger *logger = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    logger = new Logger(mainFilePath, pluginName);
    config = new Configuration();
}

bool OnClientConnect(Player *player)    
{
    if (!player->IsFakeClient())
    {
        g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("joinleave.join.message"), player->GetName());
        logger->Write(LOGLEVEL_COMMON, "%s has connected on the server!", player->GetName());
        return true;  
    }  
}

void OnClientDisconnect(Player *player)
{
    if (!player->IsFakeClient())
    {
        g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("joinleave.leave.message"), player->GetName());
        logger->Write(LOGLEVEL_COMMON, "%s has disconnected from the server!", player->GetName());
    }
}

void OnPluginStart()
{
    logger->Write(LOGLEVEL_WARNING, "The plugin started the log session.");
}

void OnPluginStop()
{
    logger->Write(LOGLEVEL_WARNING, "The plugin has stopped.");
}

const char *GetPluginWebsite()
{
    return "";
}

const char *GetPluginAuthor()
{
    return "Moongetsu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "Join/Leave Messages";
}