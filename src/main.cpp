#include <swiftly/swiftly.h>
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
    print(FetchTranslation("joinleave.join.message"), config->Fetch<const char*>("joinleave.prefix"), player->GetName());
    logger->Write(LOGLEVEL_COMMON, "[%s] %s has connected on the server!", __DATE__, player->GetName());
    return true;
}

void OnClientDisconnect(Player *player)
{
    print(FetchTranslation("joinleave.leave.message"), config->Fetch<const char*>("joinleave.prefix"), player->GetName());
    logger->Write(LOGLEVEL_COMMON, "[%s] %s has disconnected from the server!", __DATE__, player->GetName());
}

void OnPluginStart()
{
    logger->Write(LOGLEVEL_COMMON, "[%s] The plugin started the log session.", __DATE__);
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