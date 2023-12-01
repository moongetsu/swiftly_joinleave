#include <swiftly/swiftly.h>
#include <swiftly/server.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
}

void OnClientConnected(Player *player)
{
    print("------------------------------------------------ \n");
    print("%s s-a conectat pe server! \n", player->GetName());
    print("------------------------------------------------ \n");
}

void OnPluginStart()
{
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