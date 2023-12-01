#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/logger.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Logger *logger = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    logger = new Logger(mainFilePath, pluginName);
}

bool OnClientConnect(Player *player)
{
    player->SendMsg(HUD_PRINTTALK, "%s s-a conectat pe server! \n", player->GetName());
    logger->Write(LOGLEVEL_COMMON, "[%s] %s s-a conectat pe server!", __DATE__, player->GetName());
    return true;
}

void OnClientDisconnect(Player *player)
{
    player->SendMsg(HUD_PRINTTALK, "%s s-a deconectat de pe server! \n", player->GetName());
    logger->Write(LOGLEVEL_COMMON, "[%s] %s s-a deconectat pe server!", __DATE__, player->GetName());
}

void OnPluginStart()
{
    logger->Write(LOGLEVEL_COMMON, "[%s] Plugin-ul a pornit", __DATE__);
}

void OnPluginStop()
{
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