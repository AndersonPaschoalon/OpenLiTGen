// parametro de entrada: tempo de geração maximo - caso não seja especificado, usar default
// deve haver uma packet queue composta de pacotes 
// carregar o modelo especificado, gerar as distribuições e listas correspondentes a esse modelo
// para cada usuario, utilizando o modelo, gerar pacotes até que o tempo seja maior ou igual ao 
//      ao tempo maximo especificado
// a lista gerada para todos os usuarios devera ser mergeada. 
// Utilizando um gerador de trafego (Tins, csv), ele devera receber um a um os pacotes modelados,
//      e enviar ao destino especificado.

#include <iostream>
#include <string>
#include <getopt.h>
#include "LitModel.h"
#include "TgEngine.h"
#include "Timer.h"

#define LITGEN_TG_VERSION "1.0"

void displayHelp();
void displayVersion();
bool litgenTg(const char* strLitModel, unsigned int maxTimeSeconds, const char* strNetInterface);

int main(int argc, char* argv[])
{
    const char* shortOptions = "m:i:t:vh";
    const struct option longOptions[] = 
    {
        {"max-time", required_argument, nullptr, 't'},
        {"model", required_argument, nullptr, 'm'},
        {"interface", required_argument, nullptr, 'i'},
        {"version", no_argument, nullptr, 'v'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };

    std::string litModel;
    std::string dstNetInterface = "eth0";
    unsigned int maxTimeSeconds = 3600;
    bool showHelp = false;
    bool showVersion = false;

    int opt;
    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, nullptr)) != -1) {
        switch (opt) {
            case 'm':
                litModel = optarg;
                break;
            case 'i':
                dstNetInterface = optarg;
                break;
            case 't':
                maxTimeSeconds = std::stoi(optarg);
                break;
            case 'v':
                showVersion = true;
                break;
            case 'h':
                showHelp = true;
                break;
            case '?':
                break;  // Unrecognized option, handled by getopt
        }
    }

    if (showHelp) 
    {
        displayHelp();
        return 0;
    }

    if (showVersion) {
        
        displayVersion();
        return 0;
    }

    if(!litgenTg(litModel.c_str(), maxTimeSeconds, dstNetInterface.c_str()))
    {
        return -1;
    }

    return 0;
}

void displayHelp()
{
    std::cout << "Usage: litgen-tg [OPTIONS]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --max-time <max-time-seconds> : (optional) max time in seconds for the traffic to be generated. Default is 3600 seconds." << std::endl;
    std::cout << "  -m, --model <lit-model>       : litgen model to be loaded and used." << std::endl;
    std::cout << "  -i, --interface <dst-net-interface> : interface where the traffic will be sent. Default is eth0." << std::endl;
    std::cout << "  -v, --version                 : print the application version." << std::endl;
    std::cout << "  -h, --help                    : print this help message." << std::endl; 
}

void displayVersion()
{
    std::cout << "litgen-tg version " << LITGEN_TG_VERSION << std::endl;
}

bool litgenTg(const char* strLitModel, unsigned int maxTimeSeconds, const char* strNetInterface)
{
    Timer timer;
    timer.init();

    LitModel* model = new LitModel();
    model->load(strLitModel);
    TgEngine* engine = nullptr;

    if (StringUtils::endsWith(strNetInterface, ".csv") == true)
    {
        engine = TgCsv(strNetInterface);
    }
    else
    {
        engine = TgTins(strNetInterface);
    }

    printf("Modelling packets using litgen models %s...\n", strLitModel);
    engine->samplePduQueue(*model, (double)maxTimeSeconds);
    printf("Elapsed time: %s seconds.\n", timer.elapsedTime().c_str());
    printf("Done\n");

    printf("Starting traffic generation at %s...\n", strNetInterface);
    engine->generate();
    printf("All Done!");
    printf("Elapsed time: %s seconds.\n", timer.elapsedTime().c_str());

    delete model;
    model = nullptr;
    delete engine;
    engine = nullptr; 
}